#include <stdio.h>
#include <math.h>
int n, i, j, counter;
double sum, numerator, denominator;
int main() {
    counter = 0;
    sum = 0;
    printf("Enter n:");
    scanf("%d", &n);
    for (i = 1; i <= n; i++){
        numerator = 1;
        denominator = 3*i*log(i+1);
        counter += 4;
        for (j = 1; j <= i; j++){
            numerator *= 2*j+1;
            counter += 3;
        }
        sum += numerator/denominator;
        counter += 2;
    }
    printf("Result is %.7f\n", sum);
    printf("Counter is %d", counter);
    return 0;
}