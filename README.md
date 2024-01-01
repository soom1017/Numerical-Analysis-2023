# Numerical Analysis 2023
Homeworks in Numerical Analysis class, 2023 Fall (MAT3008)

Using library in "[Numerical Recipes in C](https://github.com/zhufengGNSS/Numerical-Recipes-1/blob/master/Numerical%20Recipes%20in%20C%20-%20The%20Art%20of%20Scientific%20Computing%20-%202nd%20Edition.pdf)", I implemented various numerical analysis methods below.

## 1. [Machar](https://github.com/soom1017/Numerical-Analysis-2023/tree/main/01-Machar) (Machine Accuracy)
Obtain the machine accuracy of float and double of my computer in two ways.

> Results: [screenshot image](https://github.com/soom1017/Numerical-Analysis-2023/blob/main/01-Machar/result_screenshot.png)

## 2. [RootFinding](https://github.com/soom1017/Numerical-Analysis-2023/tree/main/02-RootFinding)
Find the roots of the Bessel function $J_0$ in the interval [1.0, 10.0] using methods [Bisection, Linear interpolation, Secant, Newton-Raphson, Newton with bracketing].

> Results: [report.pdf](https://github.com/soom1017/Numerical-Analysis-2023/blob/main/02-RootFinding/convergence%20speed.pdf)

## 3. [LinearEquation](https://github.com/soom1017/Numerical-Analysis-2023/tree/main/03-LinearEquation)
Solve the equation $A_i x_i = b_i  (i=1,2,3)$ using [Gauss-Jordan Elimination, LU decomposition, SVD].

> Results: [report.pdf](https://github.com/soom1017/Numerical-Analysis-2023/blob/main/03-LinearEquation/report.pdf)

## 4. [RandomNumberGeneration](https://github.com/soom1017/Numerical-Analysis-2023/blob/main/04-RandomNumberGeneration)
Generate random number of [uniform distribution in [a, b] / Gaussian distribution with mean=m, std=s].

> Results: [report.pdf](https://github.com/soom1017/Numerical-Analysis-2023/blob/main/04-RandomNumberGeneration/report.pdf)

## 5. [LinearInterpolation](https://github.com/soom1017/Numerical-Analysis-2023/tree/main/05-LinearInterpolation)
Read an image file and resample it to a speicified resolution.

> Results: [report.pdf](https://github.com/soom1017/Numerical-Analysis-2023/blob/main/05-LinearInterpolation/report.pdf)

## 6. [Datafitting](https://github.com/soom1017/Numerical-Analysis-2023/blob/main/06-DataFitting)
Given N observations ($x_i, y_i, x_i', y_i', i=1,2,...,N$) and a linear mapping model below, find the best (in the "least-square" sense) set of parameters **a** that fits the given data.

> $x'=a_1 x + a_2 y + a_3$
> 
> $y'=a_4 x + a_5 y + a_6$

> Results: [screenshot image](https://github.com/soom1017/Numerical-Analysis-2023/blob/main/06-DataFitting/result.png)
