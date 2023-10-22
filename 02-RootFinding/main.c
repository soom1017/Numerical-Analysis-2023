#include <stdio.h>
#include <time.h>
#include "nr.h"
#include "nrutil.h"
#include "muller.h"
#include "nonlinear_func.h"

#define MAX_NBRAK 1e4
#define MAX_NROOT 50
#define XACC 1e-6

// Finding roots of the function
void findRoot1(float (*func)(float), float (*method)(float (*func_)(float), float, float, float), 
                float *xb1, float *xb2, int nb) {

    float rt, cpu_time_used;
    clock_t start, end;     // For convergence speed
    
    cpu_time_used = 0.f;
    for (int i=0; i<nb; i++) {
        start = clock();
        rt = method(func, xb1[i+1], xb2[i+1], XACC);
        end = clock();

        cpu_time_used += (float)(end - start) / CLOCKS_PER_SEC;
        printf("%0.10f / ", rt);
    }
    printf("Average cpu time used: %.10f sec", cpu_time_used / nb);
	printf("\n========================================================\n");
}

// Finding roots of the function, with Newton methods
void findRoot2(void (*funcd)(float, float *, float *), float (*method)(void (*funcd_)(float, float *, float *), float, float, float), 
                float *xb1, float *xb2, int nb) {

    float rt, cpu_time_used;
    clock_t start, end;     // For convergence speed
    
    cpu_time_used = 0.f;
    for (int i=0; i<nb; i++) {
        start = clock();
        rt = method(funcd, xb1[i+1], xb2[i+1], XACC);
        end = clock();

        cpu_time_used += (float)(end - start) / CLOCKS_PER_SEC;
        printf("%0.10f / ", rt);
    }
    printf("Average cpu time used: %.10f sec", cpu_time_used / nb);
	printf("\n========================================================\n");
}

void bessj0_derivative(float x, float *y, float *dy) {
    *y = bessj0(x);
    *dy = -1 * bessj1(x);
}



int main(){

    int nb = MAX_NROOT;
    float xb1[MAX_NROOT], xb2[MAX_NROOT];
    
    // Step1. Use bracketing routine
    zbrak(bessj0, 1.f, 10.f, MAX_NBRAK, xb1, xb2, &nb);
    printf("========================================================\n");
    printf("Rough initial solutions for Bessel function J0 (bessj0) in [1.0, 10.0] are following brackets (zbrak): \n");
    for (int i=0; i<nb; i++) {
        printf("[%0.10f, %0.10f] / ", xb1[i+1], xb2[i+1]);
    }
    printf("\n========================================================\n\n");

    // Step2. Call proper routines in NR in C
    printf("Exact solutions (rtbis): \n");
    findRoot1(bessj0, rtbis, xb1, xb2, nb);
    printf("Exact solutions (rtflsp): \n");
    findRoot1(bessj0, rtflsp, xb1, xb2, nb);
    printf("Exact solutions (rtsec): \n");
    findRoot1(bessj0, rtsec, xb1, xb2, nb);
    printf("Exact solutions (rtnewt): \n");
    findRoot2(bessj0_derivative, rtnewt, xb1, xb2, nb);
    printf("Exact solutions (rtsafe): \n");
    findRoot2(bessj0_derivative, rtsafe, xb1, xb2, nb);
    printf("Exact solutions (muller): \n");
    findRoot1(bessj0, muller, xb1, xb2, nb);    // muller.c and muller.h are in default directory. (RootFinding/)

    // Solve one interesting nonlinear equation I want to solve
    zbrak(nonlinear_func, 1.f, 5.f, MAX_NBRAK, xb1, xb2, &nb);
    printf("\nRough initial solutions for custom non-linear function (nonlinear_f) in [1.0, 5.0] are following brackets (zbrak): \n");
    for (int i=0; i<nb; i++) {
        printf("[%0.10f, %0.10f] / ", xb1[i+1], xb2[i+1]);
    }
    printf("\n========================================================\n\n");
    printf("Exact solutions (rtsafe): \n");
    findRoot2(nonlinear_func_derivative, rtsafe, xb1, xb2, nb);

	return 0;
}