#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "nr.h"
#include "nrutil.h"

#define MAX_NOISE 1.0

// Get matrix A (n by n), vector b (n by 1) from the file (lineq*.dat) 
void read_data(FILE *fp, float ***a, float **b, float ***b_2D, int *n) {
    int i, j;

    // File open and read matrix size (n n) 
    int m;
    fscanf(fp, "%d %d", &m, n);
    assert(m == *n);

    // Memory Allocation for matrix a, vector b
    *a = (float **)malloc((*n+1) * sizeof(float *));
    for (i=1; i<=*n; i++)
        (*a)[i] = (float *)malloc((*n+1) * sizeof(float));
    
    *b = (float *)malloc((*n+1) * sizeof(float));

    // Get value of matrix a, vector b
    for (i=1; i<=*n; i++)
        for (j=1; j<=*n; j++)
            fscanf(fp, "%f", &(*a)[i][j]);
    
    for (i=1; i<=*n; i++)
        fscanf(fp, "%f", &(*b)[i]);

    // Make matrix b_2D[1...n][1...m] (m=1), from vector b[1...n]
    *b_2D = (float **)malloc((*n+1) * sizeof(float *));
    for (i=1; i<=*n; i++) {
        (*b_2D)[i] = (float *)malloc(2 * sizeof(float));
        (*b_2D)[i][1] = (*b)[i];
    }

    fclose(fp);
}

/*
Run linEq command: $ ./linEq [.dat file path] [type]
- type: "gaussj" or "ludcmp" or "svdcmp" or "inverse" or "mprove" or "det"
*/
int main(int argc, char *argv[]){
    float **a, *b, **b_2D, d;
    float wmax, wmin, *w, **v, *x;          // for svd.
    float **alud;                           // for iterative improvement (mprove).
    float **y, *col;                        // for inverse calculation.
    int n, *indx;
    int i, j;

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
        perror("File open error: no such file\n");

    read_data(fp, &a, &b, &b_2D, &n);

    printf("File '%s' read complete. =======\n", argv[1]);

    if (!strcmp(argv[2], "gaussj")) {
        gaussj(a, n, b_2D, 1);
        printf("Using Gauss-Jordan Elimination: x = [ ");
        for (i=1; i<=n; i++)
            printf("%10.5f ", b_2D[i][1]);

        printf("]^t\n");
    } else if (!strcmp(argv[2], "ludcmp")) {
        indx = (int *)malloc((n+1) * sizeof(int));
        ludcmp(a, n, indx, &d);
        lubksb(a, n, indx, b);
        printf("Using LU Decomposition: x = [ ");
        for (i=1; i<=n; i++)
            printf("%10.5f ", b[i]);

        printf("]^t\n");
        free(indx);
    } else if (!strcmp(argv[2], "svdcmp")) {
        w = (float *)malloc((n+1) * sizeof(float));
        v = (float **)malloc((n+1) * sizeof(float *));
        for (i=1; i<=n; i++)
            v[i] = (float *)malloc((n+1) * sizeof(float));
        x = (float *)malloc((n+1) * sizeof(float));

        svdcmp(a, n, n, w, v);
        wmax = 0.0;
        for (j=1; j<=n; j++)
            if(w[j] > wmax) wmax = w[j];
        wmin = wmax * 1.0e-6;
        for (j=1; j<=n; j++)
            if(w[j] < wmin) w[j] = 0.0;
        svbksb(a, w, v, n, n, b, x);

        printf("Using SVD: x = [ ");
        for (i=1; i<=n; i++)
            printf("%10.5f ", x[i]);

        printf("]^t\n");

        for (i=1; i<=n; i++)
            free(v[i]);
        free(w);
        free(x);
    } else if (!strcmp(argv[2], "mprove")) {
        // 'Numerical Analysis in C' : Unless you are starting quite far from the true solution, one call (of mprove) is generally enough.
        // Make copy of a, b
        alud = (float **)malloc((n+1) * sizeof(float *));
        for (i=1; i<=n; i++)
            alud[i] = (float *)malloc((n+1) * sizeof(float));

        for (i=1; i<=n; i++)
            for (j=1; j<=n; j++)
                alud[i][j] = a[i][j];

        x = (float *)malloc((n+1) * sizeof(float));
        for (i=1; i<=n; i++)
            x[i] = b[i];

        indx = (int *)malloc((n+1) * sizeof(int));
        ludcmp(alud, n, indx, &d);
        lubksb(alud, n, indx, x);

        printf("Using LU Decomposition: x = [ ");
        for (i=1; i<=n; i++)
            printf("%10.5f ", x[i]);

        printf("]^t\n");

        // Make noise to solution vector x
        for (i=1; i<=n; i++)
            x[i] += (float)rand()/(float)(RAND_MAX/MAX_NOISE);
        printf("Solution x, noise added: x = [ ");
        for (i=1; i<=n; i++)
            printf("%10.5f ", x[i]);

        printf("]^t\n");

        mprove(a, alud, n, indx, b, x);
        printf("After improvement: x = [ ");
        for (i=1; i<=n; i++)
            printf("%10.5f ", x[i]);

        printf("]^t\n");

        for (i=1; i<=n; i++)
            free(alud[i]);
        free(x);
        free(indx);
    } else if (!strcmp(argv[2], "inverse")) {
        indx = (int *)malloc((n+1) * sizeof(int));
        ludcmp(a, n, indx, &d);

        // Memory allocation for matrix y, vector col
        col = (float *)malloc((n+1) * sizeof(float));
        y = (float **)malloc((n+1) * sizeof(float *));
        for (i=1; i<=n; i++)
            y[i] = (float *)malloc((n+1) * sizeof(float));

        // Get value of inverse matrix
        for (j=1; j<=n; j++) {
            for (int i=1; i<=n; i++)
                col[i] = 0.0;
            col[j] = 1.0;
            lubksb(a, n, indx, col);
            for (i=1; i<=n; i++)
                y[i][j] = col[i];
        }

        printf("Using LU Decomposition: inverse of matrix is \n");
        for (i=1; i<=n; i++) {
            for (j=1; j<=n; j++)
                printf("%10.5f ", y[i][j]);

            printf("\n");
        }

        for (i=1; i<=n; i++)
            free(y[i]);
        free(col);
        free(indx);
    } else if (!strcmp(argv[2], "det")) {
        indx = (int *)malloc((n+1) * sizeof(int));
        ludcmp(a, n, indx, &d);
        for (i=1; i<=n; i++)
            d *= a[i][i];
        printf("Determinant of matrix A: %10.5f\n", d);
        free(indx);
    } else {
        fprintf(stderr, "Invalid type. Expected type value: [gaussj / ludcmp / svdcmp / inverse / mprove / det]");
    }

    for (i=1; i<=n; i++)
        free(a[i]);
    free(a);
    free(b);

    for (i=1; i<=n; i++)
        free(b_2D[i]);
    free(b_2D);

	return 0;
}