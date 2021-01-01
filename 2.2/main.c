#include <stdio.h>

int main() {
    double matrix[8][8] = {
            { 0, 98, 97, 0, 95, 94, 93, 92 },
            { 0, 0, 88, 0, 85, 84, 81, 79 },
            { 0, 74, 10, 0, 68, 67, 62, 61 },
            { 0, 56, 54, 14, 49, 46, 43, 40 },
            { 0, 37, 35, 0, 25, 29, 28, 27 },
            { 0, 23, 20, 0, 15, 30, 12, 10 },
            { 0, 37, 35, 0, 30, 29, 70, 27 },
            { 0, 23, 20, 0, 15, 14, 12, 89 },
    };

    printf("Sorted matrix is: \n");
    for (int i = 1; i < 8; i++) {
        int B = matrix[i][i];
        int j = i;
        while (j > 0 && B < matrix[j - 1][j - 1]) {
            matrix[j][j] = matrix[j - 1][j - 1];
            j -= 1;
        }
        matrix[j][j] = B;
    }

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            printf("%.1f ", matrix[x][y]);
        }
        printf("\n");
    }

}
