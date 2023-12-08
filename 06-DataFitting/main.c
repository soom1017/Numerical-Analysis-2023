#include <stdio.h>
#include <stdlib.h>
#include "nr.h"
#include "nrutil.h"

#define DIM_C 3

typedef struct {
    float x;
    float y;
    float x_;
    float y_;
} DataPoint;

// Get x, y, x', y' from the file (fitdata*.dat) 
void read_data(FILE *fp, int *n, DataPoint **data) {
    // Count n
    *n = 0;
    char c;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n')
            (*n)++;
    }
    fseek(fp, 0, SEEK_SET);

    // Get value of x, y, x', y'
    *data = (DataPoint *)malloc((*n+1) * sizeof(DataPoint));
    for (int i=1; i<=*n; i++) {
        fscanf(fp, "%f %f %f %f", &((*data)[i].x), &((*data)[i].y), &((*data)[i].x_), &((*data)[i].y_));
    }
    
    fclose(fp);
}

int main(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
        perror("File open error: no such file\n");

    int n, i, j, k;
    DataPoint *data;
    read_data(fp, &n, &data);

    // Make JT matrix, which is transpose of J [[x1, y1, 1], [x2, y2, 1], ...]
    float **JT = (float **)malloc((DIM_C+1) * sizeof(float *));
    for (i=1; i<=DIM_C; i++) {
        JT[i] = (float *)malloc((n+1) * sizeof(float));
    }
    for (i=1; i<=n; i++) {
        JT[1][i] = data[i].x;
        JT[2][i] = data[i].y;
        JT[3][i] = 1.0;
    }

    float **JTy_2D = (float **)malloc((DIM_C+1) * sizeof(float *));
    for (i=1; i<=DIM_C; i++) {
        JTy_2D[i] = (float *)malloc(3 * sizeof(float));
        JTy_2D[i][1] = 0.0;
        for (j=1; j<=n; j++)
            JTy_2D[i][1] += JT[i][j] * data[j].x_;
        JTy_2D[i][2] = 0.0;
        for (j=1; j<=n; j++)
            JTy_2D[i][2] += JT[i][j] * data[j].y_;
    }

    float **JTJ = (float **)malloc((DIM_C+1) * sizeof(float *));
    for (i=1; i<=DIM_C; i++) {
        JTJ[i] = (float *)malloc((DIM_C+1) * sizeof(float));
        for (j=1; j<=DIM_C; j++) {
            JTJ[i][j] = 0.0;
            for (k=1; k<=n; k++) {
                JTJ[i][j] += JT[i][k] * JT[j][k];
            }
        }
    }

    // Calculate JTJc = JTx' and JTJc = JTy', so get c (a1, a2, a3 / a4, a5, a6).
    gaussj(JTJ, DIM_C, JTy_2D, 2);

    for (i=1; i<=DIM_C; i++)
        printf("%f ", JTy_2D[i][1]);
    for (i=1; i<=DIM_C; i++)
        printf("%f ", JTy_2D[i][2]);
    printf("\n");

    for (int i=1; i<=DIM_C; i++) {
        free(JT[i]);
        free(JTJ[i]);
        free(JTy_2D[i]);
    }
    free(JT);
    free(JTJ);
    free(JTy_2D);
    free(data);

    return 0;
}