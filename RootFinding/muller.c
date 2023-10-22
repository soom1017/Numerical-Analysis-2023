#include <stdio.h>
#include <math.h>

#define MAXIT 30

float muller(float (*func)(float), float x0, float x2, float xacc)
{
    int j;
    float x1 = (x0 + x2) / 2;
    float h0, h1, d0, d1, a, b, c, D, dx, x3;

    for (j = 1; j <= MAXIT; j++) {
        h0 = x1 - x0;
        h1 = x2 - x1;
        d0 = ((*func)(x1) - (*func)(x0)) / h0;
        d1 = ((*func)(x2) - (*func)(x1)) / h1;

        a = (d1 - d0) / (h1 + h0);
        b = a * h1 + d1;
        c = (*func)(x2);

        D = sqrt(b * b - 4 * a * c);
        if (fabs(b + D) > fabs(b - D)) {
            dx = -2 * c / (b + D);
        } else {
            dx = -2 * c / (b - D);
        }

        x3 = x2 + dx;

        if (fabs(dx) < xacc || (*func)(x3) == 0.0) {
            return x3;
        }

        x0 = x1;
        x1 = x2;
        x2 = x3;
    }

    return 0.0;
}

#undef MAXIT
