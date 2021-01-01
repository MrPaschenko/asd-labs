#include <stdio.h>
#include <math.h>

int main() {
    int i, j, n;
    double result = 0, numerator = 1, tempNumerator = sin(1), denominator = cos(j) + 1;

    printf("Enter n: \n");
    scanf("%d", &n);

    for( i = 1; i <= n; i++ ) {
        for( j=1; j <= n - 1; j++ ) {
            numerator *= tempNumerator;
            tempNumerator += sin(j+1);
            denominator *= cos(j+1) + 1;
        }
        result = numerator / denominator;
    }
    printf("%f", result);
    return 0;
}