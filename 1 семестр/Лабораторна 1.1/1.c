#include <stdio.h>

int main() {

    float x;
    double y;

    printf("Enter x:\n");
    scanf("%f", &x);

    if (x <= 0) {
        y = - x * x - 12;
        printf("%f\n", y);
    }
    else if (x>2) {
        if (x <= 12) {
            y = - 9 * x * x * x + 5 * x * x;
            printf("%f\n", y);
        }
        else if (x<=22) {
            printf("Function doesn't exist");
        }
        else if (x<32) {
            y = -9 * x * x * x + 5 * x * x;
            printf("%f\n", y);
        }
        else printf("Function doesn't exist");
    }
    else printf("Function doesn't exist");
    while (1){}
    return 0;
}
