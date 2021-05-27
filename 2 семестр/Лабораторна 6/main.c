#include <windows.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define n 11

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char ProgName[] = "Lab_4_Pashchenko_IP-04";

double **randm(int rows, int cols) {
    double **matrix = (double **) malloc(rows * sizeof(double *));

    for (int i = 0; i < rows; i++)
        matrix[i] = (double *) malloc(cols * sizeof(double));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double temp = rand() % 21;
            matrix[i][j] = temp / 10;
        }
    }
    return matrix;
}

double **mulmr(double coef, double **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = matrix[i][j] * coef;

            if (matrix[i][j] < 1.0) {
                matrix[i][j] = 0;
            } else matrix[i][j] = 1;
        }
    }
    return matrix;
}

void createTrMatrix(int Tr[][n]) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i < j) Tr[i][j] = 1;
        }
    }
}

struct node {
    int weight;
    int from;
    int to;
};

struct node nd[n * n];

int getStuctMinId() {
    int min = 10000000;
    int minId = 0;
    for (int i = 0; i < (n * n); i++) {
        int weight = nd[i].weight;
        if (weight > 0) {
            if (weight < min) {
                min = weight;
                minId = i;
            }
        }
    }
    return minId;
}

void printGrapgMatrix(int **graphMatrix) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", graphMatrix[i][j]);
        }
        printf("\n");

    }
}

int Prim(int W[][n], int startVert, int destM[][n], int waysM[n - 1][3]) {
    int startPoint = startVert - 1;
    int visited[n] = {0};
    int totalWayWeight = 0;

    int lastIdPos = 0;
    for (int j = 0; j < n; j++) {
        if (W[startPoint][j] > 0) {
            int weight = W[startPoint][j];
            nd[j].weight = weight;
            nd[j].from = startPoint;
            nd[j].to = j;
            lastIdPos += 1;
        }

    }
    visited[startPoint] = 1;

    int numberOfVisited = 0;
    while (numberOfVisited < n - 1) {
        int minId = getStuctMinId();
        int minWeight = nd[minId].weight;
        int minFrom = nd[minId].from;
        int minTo = nd[minId].to;
        if (visited[minTo] == 0) {
            visited[minTo] = 1;
            totalWayWeight += minWeight;
            destM[minFrom][minTo] = 1;

            waysM[numberOfVisited][0] = minFrom;
            waysM[numberOfVisited][1] = minTo;
            waysM[numberOfVisited][2] = minWeight;
            numberOfVisited += 1;

            for (int j = 0; j < n; j++) {
                if (W[minTo][j] > 0 && visited[j] == 0) {
                    nd[lastIdPos].weight = W[minTo][j];
                    nd[lastIdPos].from = minTo;
                    nd[lastIdPos].to = j;
                    lastIdPos += 1;
                }
            }
        } else {
            nd[minId].weight = 0;
            nd[minId].from = 0;
            nd[minId].to = 0;
        }
    }
    simMatrix(destM, destM);
    return totalWayWeight;
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine,
                   int nCmdShow) {
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w;

    w.lpszClassName = ProgName;
    w.hInstance = hInstance;
    w.lpfnWndProc = WndProc;
    w.hCursor = LoadCursor(NULL, IDC_ARROW);
    w.hIcon = 0;
    w.lpszMenuName = 0;
    w.hbrBackground = WHITE_BRUSH;
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if (!RegisterClass( & w)) return 0;

    hWnd = CreateWindow(ProgName,
                        "Lab_4_Pashchenko_IP-04",
                        WS_OVERLAPPEDWINDOW,
                        830,
                        0,
                        1100,
                        1100,
                        (HWND) NULL,
                        (HMENU) NULL,
                        (HINSTANCE) hInstance,
                        (HINSTANCE) NULL);

    ShowWindow(hWnd, nCmdShow);

    while (GetMessage(&lpMsg, hWnd, 0, 0)) {
        TranslateMessage(&lpMsg);
        DispatchMessage(&lpMsg);
    }
    return lpMsg.wParam;
}

void paintLines(HDC hdc, int matrix[n][n], int nx[n], int ny[n], int start, int end) {
    float koef;
    int radius = 16, divine = 1, xDif, yDif;
    if (matrix[start][end] == 1) {
        xDif = nx[start] - nx[end];
        yDif = ny[start] - ny[end];
        koef = sqrt(xDif * xDif + yDif * yDif) / radius;
        if (start == end) {
            MoveToEx(hdc, nx[end], ny[end], NULL);
            if (start <= 3) {
                Arc(hdc, nx[start] + 20, ny[start] - 5, nx[start] - 40, ny[start] - 60, nx[start], ny[start], nx[start],
                    ny[start]);
            } else if (start <= 7) {
                Arc(hdc, nx[start] + 50, ny[start] + 10, nx[start], ny[start] - 40, nx[start], ny[start], nx[start],
                    ny[start]);
            } else if (start <= 9) {
                Arc(hdc, nx[start] + 35, ny[start], nx[start] - 20, ny[start] + 50, nx[start], ny[start], nx[start],
                    ny[start]);
            } else {
                Arc(hdc, nx[start] + 35, ny[start], nx[start] - 20, ny[start] + 50, nx[start], ny[start], nx[start],
                    ny[start]);
            }
        } else {
            MoveToEx(hdc, nx[start], ny[start], NULL);
            if ((ny[start] == ny[end]) && abs(nx[start] - nx[end]) > 200) {
                Arc(hdc, nx[end], ny[end] - 50, nx[start], ny[start] + 50, nx[end], ny[end], nx[start], ny[start]);
            } else if (nx[start] == nx[end] && abs(ny[start] - ny[end]) > 200) {
                if (start >= 9 || end >= 9) {
                    Arc(hdc, nx[end] - 40, ny[end], nx[start] + 40, ny[start], nx[start], ny[start], nx[end], ny[end]);
                } else if ((start >= 3 && start <= 8) && (end >= 3 && end <= 8)) {
                    if (start > end) {
                        Arc(hdc, nx[end] - 60, ny[end], nx[start] + 60, ny[start], nx[start], ny[start], nx[end],
                            ny[end]);
                    } else {
                        Arc(hdc, nx[start] - 60, ny[start], nx[end] + 60, ny[end], nx[end], ny[end], nx[start],
                            ny[start]);
                    }
                } else {
                    LineTo(hdc, nx[end], ny[end]);
                }
            } else if (yDif == 0 && abs(xDif) > 200 && end <= 3) {
                LineTo(hdc, nx[end] + xDif / 2, ny[end] - 35);
            } else if (abs(xDif) == 300 && abs(yDif) == 300 && (end == 0 || end == 3)) {
                LineTo(hdc, nx[end] + xDif / 2, ny[end] + yDif / 1);
            }
            if ((ny[start] == ny[end]) && (abs(nx[start] - nx[end]) > 200)) {

            } else {
                if ((start == 3 && end == 5) || (start == 3 && end == 6) || (start == 6 && end == 4) ||
                    (start == 4 && end == 6) || (start == 6 && end == 3)
                    || (start == 0 && end == 9) || (start == 9 && end == 0)) {

                } else {
                    LineTo(hdc, nx[end], ny[end]);

                }

            }
        }
    }
}

void paintWeight(HDC hdc, int matrix[n][n], int nx[n], int ny[n], int start, int end) {
    float koef;
    char text[5];
    sprintf_s(text, sizeof(text) + 2, "%d", matrix[start][end]);
    int radius = 16, divine = 1, xDif, yDif;
    if (matrix[start][end] > 0) {
        xDif = nx[start] - nx[end];
        yDif = ny[start] - ny[end];
        koef = sqrt(xDif * xDif + yDif * yDif) / radius;
        if (start == end) {
            MoveToEx(hdc, nx[end], ny[end], NULL);
            if (start <= 3) {
                TextOutA(hdc, nx[end] - 15, ny[end] - 40, text, matrix[start][end] < 100 ? 2 : 3);
            } else if (start <= 7) {
                TextOutA(hdc, nx[end] + 20, ny[end] - 10, text, matrix[start][end] < 100 ? 2 : 3);
            } else if (start <= 9) {
                TextOutA(hdc, nx[end] - 10, ny[end] + 20, text, matrix[start][end] < 100 ? 2 : 3);
            } else {
                TextOutA(hdc, nx[end] - 10, ny[end] + 20, text, matrix[start][end] < 100 ? 2 : 3);
            }
        } else {
            MoveToEx(hdc, nx[start], ny[start], NULL);
            if ((ny[start] == ny[end]) && abs(nx[start] - nx[end]) > 200) {
                if (ny[start] > 350) {
                    TextOutA(hdc, ((nx[end] + nx[start]) / 2) - 15, ny[end] + 40, text,
                             matrix[start][end] < 100 ? 2 : 3);
                } else {
                    TextOutA(hdc, ((nx[end] + nx[start]) / 2) + 15, ny[end] - 60, text,
                             matrix[start][end] < 100 ? 2 : 3);
                }
            } else if (nx[start] == nx[end] && abs(ny[start] - ny[end]) > 200) {
                if (start >= 9 || end >= 9) {
                    TextOutA(hdc, nx[end] - 50, (ny[end] + ny[start]) / 2, text, matrix[start][end] < 100 ? 2 : 3);
                } else if ((start >= 3 && start <= 8) && (end >= 3 && end <= 8)) {
                    if (start > end) {
                        // Arc(hdc, nx[end]-60, ny[end], nx[start]+60, ny[start], nx[start], ny[start], nx[end], ny[end]);
                        TextOutA(hdc, ((nx[end] + nx[start]) / 2) + 15, ny[end] - 60, text,
                                 matrix[start][end] < 100 ? 2 : 3);
                    } else {
                        TextOutA(hdc, nx[end] + 50, (ny[end] + ny[start]) / 2, text, matrix[start][end] < 100 ? 2 : 3);
                    }
                } else {
                    TextOutA(hdc, nx[end] - 10, (ny[end] + ny[start]) / 2, text, matrix[start][end] < 100 ? 2 : 3);
                }
            } else if (yDif == 0 && abs(xDif) > 200 && end <= 3) {
            } else if (abs(xDif) == 300 && abs(yDif) == 300 && (end == 0 || end == 3)) {
            }
            if ((ny[start] == ny[end]) && (abs(nx[start] - nx[end]) > 200)) {
            } else {
                if ((start == 3 && end == 5) || (start == 3 && end == 6) || (start == 6 && end == 4) ||
                    (start == 4 && end == 6) || (start == 6 && end == 3)
                    || (start == 0 && end == 9) || (start == 9 && end == 0)) {
                } else {
                    if (matrix[start][end] < 10) {
                        TextOutA(hdc, ((nx[end] + nx[start]) / 2) - 10, ((ny[end] + ny[start]) / 2) - 10, text, 1);
                    } else {
                        if (start == 1 && end == 9) {
                            TextOutA(hdc, ((nx[end] + nx[start]) / 2) - 20, ((ny[end] + ny[start]) / 2) + 20, text,
                                     matrix[start][end] < 100 ? 2 : 3);
                        } else if (start == 0 && end == 7) {
                            TextOutA(hdc, ((nx[end] + nx[start]) / 2) - 20, ((ny[end] + ny[start]) / 2) - 30, text,
                                     matrix[start][end] < 100 ? 2 : 3);
                        } else if (start == 0 && end == 6) {
                            TextOutA(hdc, ((nx[end] + nx[start]) / 2) - 20, ((ny[end] + ny[start]) / 2) - 30, text,
                                     matrix[start][end] < 100 ? 2 : 3);
                        } else if (start == 2 && end == 8) {
                            TextOutA(hdc, ((nx[end] + nx[start]) / 2), ((ny[end] + ny[start]) / 2) - 40, text,
                                     matrix[start][end] < 100 ? 2 : 3);
                        } else if (start == 3 && end == 7) {
                            TextOutA(hdc, ((nx[end] + nx[start]) / 2) + 5, ((ny[end] + ny[start]) / 2) - 50, text,
                                     matrix[start][end] < 100 ? 2 : 3);
                        } else if (start == 1 && end == 6) {
                            TextOutA(hdc, ((nx[end] + nx[start]) / 2) + 5, ((ny[end] + ny[start]) / 2) + 20, text,
                                     matrix[start][end] < 100 ? 2 : 3);
                        } else if ((start == 2 && end == 7) || (start == 7 && end == 2)) {
                            TextOutA(hdc, ((nx[end] + nx[start]) / 2) - 15, ((ny[end] + ny[start]) / 2) - 40, text,
                                     matrix[start][end] < 100 ? 2 : 3);
                        } else {
                            TextOutA(hdc, ((nx[end] + nx[start]) / 2) - 10, ((ny[end] + ny[start]) / 2) - 10, text,
                                     matrix[start][end] < 100 ? 2 : 3);
                        }
                    }
                }
            }
        }
    }
}

void paintVertex(HDC hdc, int xPos[n], int yPos[n], char *nn[n], int i) {
    int dtx = 5, radius = 16;
    Ellipse(hdc, xPos[i] - radius, yPos[i] - radius, xPos[i] + radius, yPos[i] + radius);
    if (i < 9) {
        TextOut(hdc, xPos[i] - dtx, yPos[i] - 8, nn[i], 1);
    } else {
        TextOut(hdc, xPos[i] - dtx, yPos[i] - 8, nn[i], 2);
    }
}

void printMatrix(HDC hdc, int A[n][n], int xPos) {
    char text[11];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sprintf_s(text, sizeof(text), "%d", A[i][j]);
            TextOutA(hdc, xPos + 30 * j, 700 + 20 * i, text, A[i][j] < 100 ? 2 : 3);
        }
    }
}

void simMatrix(int A[n][n], int *B[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j]) {
                B[j][i] = A[i][j];
                B[i][j] = A[i][j];
            } else if (!A[i][j] && !A[j][i]) {
                B[i][j] = 0;
                B[j][i] = 0;
            }

        }
    }
}

void generateMatrix(int *matrix[n][n], double k) {
    int element;
    double temp;
    double num;
    srand(419);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp = rand() % 21;
            temp = temp / 10;
            num = temp * k;
            if (num < 1) element = 0;
            else element = 1;
            matrix[i][j] = element;
        }
    }
}

void weightMatrix(HDC hdc, int A[n][n], int *W[n][n]) {
    int num;
    int Wt[n][n];
    int B[n][n];
    int C[n][n];
    int D[n][n];
    int Tr[n][n] = {0};
    createTrMatrix(Tr);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            num = roundf((rand() / (float) RAND_MAX * 2) * 100) * A[i][j];
            Wt[i][j] = num;
            if (num == 0) B[i][j] = 0;
            else B[i][j] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (B[i][j] != B[j][i]) C[i][j] = 1;
            else C[i][j] = 0;

            if (B[i][j] == B[j][i] && B[i][j] == 1 && j <= i) D[i][j] = 1;
            else D[i][j] = 0;

            Wt[i][j] = (C[i][j] + (D[i][j] * Tr[i][j])) * Wt[i][j];
        }
    }
    simMatrix(Wt, W);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;

    switch (messg) {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            int A[n][n];
            int W[n][n];
            int totalWeight = 0;
            int treeMatrix[n][n] = {0};
            int ways[n - 1][3] = {0};
            double B[n][n] = {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
            };
            char *nn[11] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};
            int nx[n + 1] = {350}, ny[n + 1] = {100};

            HPEN BlackPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
            HPEN RedPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
            HPEN GreenPen = CreatePen(PS_SOLID, 2, RGB(39, 222, 11));

            SelectObject(hdc, BlackPen);

            generateMatrix(A, (1.0 - 1 * 0.01 - 3 * 0.005 - 0.05));
            simMatrix(A, B);
            weightMatrix(hdc, A, W);
            TextOutA(hdc, 30, 670, "Weight matrix:", 14);
            printMatrix(hdc, W, 20);

            int num = 110;
            for (int i = 0; i < 11; i++) {
                if (i == 0) {
                    nx[i] = 200;
                    ny[i] = 200;
                } else if (i < 4) {
                    nx[i] = nx[i - 1] + 200;
                    ny[i] = ny[i - 1];
                } else if (i < 6) {
                    nx[i] = nx[i - 1];
                    ny[i] = ny[i - 1] + 200;
                } else if (i < 9) {
                    nx[i] = nx[i - 1] - 200;
                    ny[i] = ny[i - 1];
                } else if (i < 10) {
                    nx[i] = nx[i - 1];
                    ny[i] = ny[i - 1] - 200;
                } else {
                    nx[i] = nx[i - 1] + 3 * 200 / 2;
                    ny[i] = ny[i - 1] + 2;
                }
            }

            for (int start = 0; start < n; start++) {
                for (int end = start; end < n; end++) {
                    SelectObject(hdc, BlackPen);
                    paintLines(hdc, B, nx, ny, start, end);
                    paintWeight(hdc, W, nx, ny, start, end);
                }
            }

            SelectObject(hdc, RedPen);
            for (int i = 0; i < n; i++) paintVertex(hdc, nx, ny, nn, i);
            char text[10];

            void startPrim() {
                totalWeight = Prim(W, 1, treeMatrix, ways);
                for (int i = 0; i < n - 1; i++) {
                    int start = ways[i][0];
                    int end = ways[i][1];
                    int weight = ways[i][2];
                    // system("pause");
                    // system("cls");
                    Sleep(50);
                    sprintf_s(text, 10, "%d", weight);
                    SelectObject(hdc, GreenPen);
                    paintLines(hdc, B, nx, ny, start, end);
                    paintVertex(hdc, nx, ny, nn, start);
                    paintVertex(hdc, nx, ny, nn, end);
                    printf("%d -> %d, weight = %d \n", start + 1, end + 1, weight);
                }
                TextOutA(hdc, 475, 570, "Tree matrix:", 12);
                printMatrix(hdc, treeMatrix, 450);
                sprintf_s(text, sizeof(text), "%d", totalWeight);
                TextOutA(hdc, 450, 40, "Total weight of minimal spanning tree of the graph:", 51);
                TextOutA(hdc, 600, 70, text, 3);
            }

            startPrim();

            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return (DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return 0;
}
