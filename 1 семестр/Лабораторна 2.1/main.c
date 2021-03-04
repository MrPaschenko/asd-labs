#include <stdio.h>

int main() {
    double matrix[7][8] = {
            { 99, 98, 97, 96, 95, 94, 93, 92 },
            { 90, 89, 88, 86, 85, 84, 81, 79 },
            { 77, 74, 70, 69, 68, 67, 62, 61 },
            { 59, 56, 54, 53, 49, 46, 43, 40 },
            { 44, 37, 35, 33, 30, 29, 28, 5 },
            { 25, 23, 20, 17, 15, 14, 12, 10 },
            { 7, 6, 5, 4, 3, 2, 1, 0 }
    };

    int top = 0;
    int bottom = 6;
    int medium = (top + bottom) / 2;

    for (int i = 0; i < 7; i++) {
        for(int j=0; j < 8; j++) {
            printf("%g ", matrix[i][j]);
        }
        printf("\n");
    }

    int x = 5;

    if(x != 0 && x != 1 && x != 2 && x != 3 && x != 4 && x != 5) {
        printf("X must be from 0 to 5");
    } else {
        for (int column = 0; column <= 7; column++) {
            while ((top != bottom) && (matrix[medium][column] != x)) {
                if (matrix[medium][column] > x) { top = medium + 1; }
                if (matrix[medium][column] < x) { bottom = medium; }
                medium = (top + bottom) / 2;
            }
            if (matrix[medium][column] == x) {
                printf("\n%d position is:(%d; %d)\n", x, ++medium, ++column);
            }
        }
    }
}
