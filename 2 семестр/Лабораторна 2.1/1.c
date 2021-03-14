#include <stdio.h>
#include <math.h>
int N = 1;

double first(double x, double F, int n, double s) {
    double i = -1;
    if (n == -1)
        i = s;
    else {
        s = s + F;
        double t = (2 * (N - n) - 1), p = (4 * (N - n) * (N - n) + 2 * (N - n)), k = -1 * t * t / p;
        F = x * k * x * F;
        i = first(x, F, n - 1, s);
    }
    return i;
}

int main() {
    double S = 0, F, x;
    N = 5;
    x = 0.2;

    if (fabs(x) < 1) {
        F = x;
        S = first(x, F, N - 1, S);
        printf("%.10f\n", S);
    }
    else {
        printf("Module x must be less than 1\n");
    }
}
