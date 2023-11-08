#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nr.h"

/*
Run rnbGen command: $ ./rnbGen [# of samples]
*/
int main(int argc, char *argv[]) {
    long idum = time(NULL);
    int n_sample = atoi(argv[1]);

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
 
    // gaussian distribution with mean=m, standard deviation=s

    // Generate 1000 samples and draw a histogram (100 intervals for each distribution. a=-3, b=4, m=0.5, s=1.5)

    // Repeat the same job with varing the number of samples (eg. 100, 10000, 100000)

    // Discuss the shape of the histograms in terms of the number of samples. Ref to ch7
}