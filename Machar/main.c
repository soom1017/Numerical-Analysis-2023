#include <stdio.h>
#include "nr.h"

void get_eps(float *eps, int *n){
	*eps = 1.f;
	*n = 0;
	while (1 + *eps != 1) {
		*eps /= 2;
		*n += 1;
	}
	*eps *= 2;
	*n -= 1;
}

void get_eps2(double *eps, int *n) {
	*eps = 1.;
	*n = 0;
	while (1 + *eps != 1) {
		*eps /= 2;
		*n += 1;
	}
	*eps *= 2;
	*n -= 1;
}

int main(){
	int ibeta, it, irnd, ngrd, machep, negep, iexp, minexp, maxexp;
	float eps, epsneg, xmin, xmax;

	machar(&ibeta, &it, &irnd, &ngrd, &machep, &negep, &iexp, &minexp, &maxexp,
			&eps, &epsneg, &xmin, &xmax);
	printf("Machine Accuracy of float (machar): \t%0.20f\n", eps);

	double eps2, epsneg2, xmin2, xmax2;
	machar2(&ibeta, &it, &irnd, &ngrd, &machep, &negep, &iexp, &minexp, &maxexp,
			&eps2, &epsneg2, &xmin2, &xmax2);
	printf("Machine Accuracy of double (machar2): \t%0.20f\n\n", eps2);

	int n;
	get_eps(&eps, &n);
	printf("Epsilon of float (get_eps): \t%0.20f\n", eps);
	printf("Minimum n in epsilon of float (get_eps): \t%d\n\n", n);

	get_eps2(&eps2, &n);
	printf("Epsilon of double (get_eps2): \t%0.20f\n", eps2);
	printf("Minimum n in epsilon of double (get_eps2): \t%d\n", n);
	
	return 0;
}
