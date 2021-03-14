#include <stdio.h>
#include <math.h>
int N = 1;
double S = 0;

double second(double x, int n) {
    double i;
    if (n == 1) {
        i = x;
        S = S + i;
    }
    else {
        double t = (2 * (n - 1) - 1), p = (4 * (n - 1) * (n - 1) + 2 * (n - 1)), k = -1 * t * t / p;
        i = x * k * x * second(x, n - 1);
        S = S + i;
    }
    return i;
}

int main() {
    double F, x;
    S = 0;
    N = 5;
    x = 0.2;

    if (fabs(x) < 1) {
        F = x;
        x = second(x, N);
        printf("%.10f\n", S);
    }
    else {
        printf("Module x must be less than 1\n");
    }
}
