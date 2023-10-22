#include <stdio.h>
#include <math.h>

float linear(float x) { return 2.f*x; }
float wave(float x) { return sinf(x); }

// Calculating Riemann sum, for different functions
float RS(float (*func)(float), float begin, float end, int step){
	float stepSize = (end - begin)/(float)step;
	float result = 0.f;

	int i;
	for(i = 0; i<step; i++)
		result += stepSize*func(begin + (float)i*stepSize);

	return result;
}

int main(){

	float result0 = RS(linear, 0.f, 10.f, 100);
	printf("Result of 2x [0, 10]: %0.10f\n", result0);

	float result1 = RS(wave, 0.f, 3.141592f, 100);
	printf("Result of sin(x) [0, PI]: %0.10f\n", result1);

	float result2 = RS(wave, -3.141592f, 3.141592f, 100);
	printf("Result of sin(x) [-PI, PI]: %0.10f\n", result2);
	return 0;
}
