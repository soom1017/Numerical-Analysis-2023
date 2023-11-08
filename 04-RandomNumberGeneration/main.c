#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nr.h"

/*
Run rnbGen command: $ ./rnbGen [# of samples] | python draw_histogram.py
Make sure you have python matplot library.
*/
int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: $ %s [# of samples]\n", argv[0]);
        return 1;
    }
    long idum = time(NULL);
    printf("%ld\n", idum);
    int n_sample = atoi(argv[1]);
    printf("num samples: %d\n", n_sample);

    // uniform in [a, b] / gaussian distribution with mean=m, stddev=s
    int a = -3;
    int b = 4;
    float m = 0.5;
    float s = 1.5;

    for(int i=0;i<n_sample;i++) {
        printf("%f ", ran1(&idum) * (b - a) + a);
    }
    printf("\n");
    for(int i=0;i<n_sample;i++) {
        printf("%f ", gasdev(&idum) * s + m);
    }
}