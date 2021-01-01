#include <stdio.h>
#include <math.h>
int n, i, counter;
double sum, numerator, denominator;
int main() {
    counter = 0;
    sum = 0;
    numerator = 1;
    printf("Enter n:");
    scanf("%d", &n);
    for (i = 1; i <= n; i++){
        denominator = 3*i*log(i+1);
        numerator *= 2*i+1;
        sum += numerator/denominator;
        counter += 9;
    }
    printf("Result is %.7f\n", sum);
    printf("Counter is %d", counter);
    return 0;
}