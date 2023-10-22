#include <stdio.h>
#include <math.h>

float nonlinear_func(float x) {
    float ans;
    ans = sin(x) * cos(x);

    return ans;
}

void nonlinear_func_derivative(float x, float *y, float *dy) {
    *y = nonlinear_func(x);
    *dy = cos(2 * x);
}