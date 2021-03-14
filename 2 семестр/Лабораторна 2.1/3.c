#include <stdio.h>
#include <math.h>
int N = 1;

double third(double x, double F, int n) {
    double i = -1;
    if (n == -1)
        return x;
    else {
        double t = (2 * (N - n) - 1), p = (4 * (N - n) * (N - n) + 2 * (N - n)), k = -1 * t * t / p;
        F = x * k * x * F;
        return F + third(x, F, n - 1);
    }
}

int main() {
    double S = 0, F, x;
    N = 5;
    x = 0.2;

    if (fabs(x) < 1) {
        F = x;
        S = third(x, x, N - 1);
        printf("%.10f\n", S);
    }
    else {
        printf("Module x must be less than 1\n");
    }
}

