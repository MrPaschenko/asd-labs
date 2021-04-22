#include <stdio.h>
#include <math.h>

int main() {
    int N;
    double S = 0, x, F;
    N = 5;
    x = 0.2;

    if (fabs(x) < 1) {
        for (unsigned int i = 1; i <= N; i++) {
            if (i == 1) {
                F = x;
                S += F;
            } else {
                F *= (-1) * x * x * (2 * (i-1) - 1) * (2 * (i-1) - 1) / (4 * (i-1) * (i-1) + 2 * (i-1));
                S += F;
            }
        }
        printf("%.10f\n", S);
    }
    else {
        printf("Module x must be less than 1\n");
    }
}
