#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

double ** randm(int rows, int cols) {
    double ** matrix = (double ** ) malloc(rows * sizeof(double * ));

    for (int i = 0; i < rows; i++)
        matrix[i] = (double * ) malloc(cols * sizeof(double));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double temp = rand() % 21;
            matrix[i][j] = temp / 10;
        }
    }
    return matrix;
}

double ** mulmr(double coef, double ** matrix, int rows, int cols) {
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

double ** mirrorMatrix(double ** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 1) {
                matrix[j][i] = 1;
            }
        }
    }

    return matrix;
}

double ** cloneMatrix(double ** matrix, double ** matrixToCopy, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = matrixToCopy[i][j];
        }
    }
    return matrix;
}

void graphPower(double ** matrix, double ** mirror_matrix, int rows, int cols) {
    int counter = 0, counterp = 0, counterm = 0; {
        printf("\n\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == 1) counterp++;
            }
            printf("Graph top is: %d , deg+ is: %d  ", i + 1, counterp);
            counterp = 0;
        }
        printf("\n\n");
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                if (matrix[j][i] == 1) counterm++;
            }
            printf("Graph top is: %d , deg- is: %d  ", i + 1, counterm);
            counterm = 0;
        }
        printf("\n\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (mirror_matrix[i][j] == 1) counter++;
            }
            if (counter == 1) {
                printf("Graph top is: %d ,and it's a hanging top, deg is: %d  ", i + 1, counter); //Визначення висячої вершини
            } else if (counter == 0) {
                printf("Graph top is: %d ,and it's an isolated top, deg is: %d  ", i + 1, counter); //Визначення ізольованої вершини
            } else {
                printf("Graph top is: %d , deg is: %d  ", i + 1, counter);
            }
            counter = 0;
        }
    }
}

void wayMatrix(double ** matrix, int rows, int cols) {
    printf_s("\n\n");
    printf_s("2-length ways\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 1) {
                for (int k = 0; k < cols; k++) {
                    if (matrix[j][k] == 1) printf("| %d->%d->%d  |", i + 1, j + 1, k + 1);
                }
            }
        }
        printf_s("\n");
    }
    printf_s("\n\n");
    printf_s("3-length ways\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 1) {
                for (int count1 = 0; count1 < cols; count1++) {
                    if (matrix[j][count1] == 1) {
                        for (int count2 = 0; count2 < cols; count2++) {
                            if (matrix[count1][count2] == 1) {
                                printf("| %d->%d->%d->%d |", i + 1, j + 1, count1 + 1, count2 + 1);
                            }
                        }
                    }
                }
            }
        }
        printf_s("\n");
    }
}

//Создаём прототип функции окна, которая будет определена ниже
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//void arrow(float fi, int px, int py);

//объявляем строку-имя программы
char ProgName[] = "Lab_4_Pashchenko_IP-04";

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine,
                   int nCmdShow) {
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w; //создаём экземпляр структуры WNDCLASS

    w.lpszClassName = ProgName; //имя программы - объявлено выше
    w.hInstance = hInstance; //идентификатор текущего приложения
    w.lpfnWndProc = WndProc; //указатель на функцию окна
    w.hCursor = LoadCursor(NULL, IDC_ARROW); //загружаем курсор
    w.hIcon = 0; //иконки у нас не будет пока
    w.lpszMenuName = 0; //и меню пока не будет
    w.hbrBackground = WHITE_BRUSH; //цвет фона окна
    w.style = CS_HREDRAW | CS_VREDRAW; //стиль - перерисовываемое по х и по у
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if (!RegisterClass( & w)) return 0;

    //HWND hWnd;
    //MSG lpMsg;

    //Создадим окно в памяти, заполнив аргументы CreateWindow
    hWnd = CreateWindow(ProgName, //Имя программы
                        "Lab_4_Pashchenko_IP-04", //Заголовок окна
                        WS_OVERLAPPEDWINDOW, //Стиль окна - перекрывающееся
                        830, //положение окна на экране по х
                        0, //положение по у
                        1100, //ширина
                        1100, //висота
                        (HWND) NULL, //идентификатор родительского окна
                        (HMENU) NULL, //идентификатор меню
                        (HINSTANCE) hInstance, //идентификатор экземпляра программы
                        (HINSTANCE) NULL); //отсутствие дополнительных параметров

    //Выводим окно из памяти на экран
    ShowWindow(hWnd, nCmdShow);

    //Обновим содержимое окна
    //UpdateWindow(hWnd);

    //Цикл одержання повідомлень
    while (GetMessage( & lpMsg, hWnd, 0, 0)) {
        //Получаем сообщение из очереди
        TranslateMessage( & lpMsg); //Преобразует сообщения клавиш в символы
        DispatchMessage( & lpMsg); //Передаёт сообщение соответствующей функции окна
    }
    return lpMsg.wParam;
}

//Функция окна
LRESULT CALLBACK WndProc(HWND hWnd,
                         UINT messg,
                         WPARAM wParam,
                         LPARAM lParam) {
    HDC hdc; //создаём контекст устройства
    PAINTSTRUCT ps; //создаём экземпляр структуры графического вывода

    void arrow(float fi, int px, int py) {
        fi = 3.1416 * (180.0 - fi) / 180.0;
        int lx, ly, rx, ry; //px, py,
        //px=150;
        //py=60;
        lx = px + 15 * cos(fi + 0.3);
        rx = px + 15 * cos(fi - 0.3);
        ly = py + 15 * sin(fi + 0.3);
        ry = py + 15 * sin(fi - 0.3);
        MoveToEx(hdc, lx, ly, NULL);
        LineTo(hdc, px, py);
        LineTo(hdc, rx, ry);
        //return 0;
    }

    //Цикл обработки сообщений
    switch (messg) {
        //сообщение рисования
        case WM_PAINT:
            hdc = BeginPaint(hWnd, & ps);
            int n = 11;
            char * nn[11] = {
                    "1",
                    "2",
                    "3",
                    "4",
                    "5",
                    "6",
                    "7",
                    "8",
                    "9",
                    "10",
                    "11"
            };
            int nx[11] = {};
            int ny[11] = {};
            int num = 200;
            for (int i = 0; i < n; i++) {
                if (i == 0) {
                    nx[i] = num;
                    ny[i] = num;
                } else if (i < 4) {
                    nx[i] = nx[i - 1] + num;
                    ny[i] = ny[i - 1];
                } else if (i < 6) {
                    nx[i] = nx[i - 1];
                    ny[i] = ny[i - 1] + num;
                } else if (i < 9) {
                    nx[i] = nx[i - 1] - num;
                    ny[i] = ny[i - 1];
                } else if (i < 10) {
                    nx[i] = nx[i - 1];
                    ny[i] = ny[i - 1] - num;
                } else {
                    nx[i] = nx[i - 1] + 3 * num / 2;
                    ny[i] = ny[i - 1] + 2;
                }
            }
            int dx = 20, dy = 20, dtx = 5;
            int i;
            HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
            HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

            srand(419);
            //cтворення напрямленного графу
            double ** T = randm(11, 11);

            //double coefficient = 1.0 -  * 0.01 - 3 * 0.01 - 0.3;
            //double** A = mulmr(coefficient, T, 11, 11);
            //друга частина
            double coefficient2 = 1.0 - 1 * 0.005 - 3 * 0.005 - 0.27;
            double ** A = mulmr(coefficient2, T, n, n);
            //Створення ненапрямленного графу
            double ** B_temp = randm(n, n);
            double ** B_temp2 = cloneMatrix(B_temp, A, n, n);
            double ** B = mirrorMatrix(B_temp2, n, n);

            void printGrapgMatrix(double ** graphMatrix) {

                for (int i = 0; i < 11; i++) {
                    for (int j = 0; j < 11; j++) {
                        printf("%g ", graphMatrix[i][j]);
                    }
                    printf("\n");

                }
            }

            SelectObject(hdc, KPen);

            void drawGraphDir(double ** graphMatrix) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (graphMatrix[i][j] == 1) {
                            MoveToEx(hdc, nx[i], ny[i], NULL);

                            if (i == j) {
                                if (i < n * 0.25) {
                                    Arc(hdc, nx[j], ny[j], nx[j] - 50, ny[j] - 50, nx[j], ny[j], nx[j], ny[j]);
                                    arrow((-90 * 3.1416) / 180, nx[j], ny[j] - dy);
                                } else if (i < n * 0.5) {
                                    Arc(hdc, nx[j], ny[j], nx[j] + 50, ny[j] - 50, nx[j], ny[j], nx[j], ny[j]);
                                    arrow((0 * 3.1416) / 180, nx[j] + dx, ny[j]);
                                } else if (i < n * 0.75) {
                                    Arc(hdc, nx[j], ny[j], nx[j] + 50, ny[j] + 50, nx[j], ny[j], nx[j], ny[j]);
                                    arrow((90 * 3.1416) / 180, nx[j], ny[j] + dy);
                                } else {
                                    Arc(hdc, nx[j], ny[j], nx[j] - 50, ny[j] + 50, nx[j], ny[j], nx[j], ny[j]);
                                    arrow((180 * 3.1416) / 180, nx[j] - dx, ny[j]);
                                }
                            }
                            if ((ny[i] == ny[j]) && (nx[j] != nx[i] + num) && (nx[j] != nx[i] - num)) {
                                if (i <= 4) {
                                    if (nx[i] < nx[j]) {
                                        if (nx[i] + 3 * num == nx[j]) {
                                            Arc(hdc, nx[i], ny[i] - 70, nx[j], ny[j] + 70, nx[j], ny[j], nx[i], ny[i]);
                                            arrow((-140 * 3.1416) / 180, nx[j] - 16 * cos(-45), ny[j] + 16 * sin(-45) - 3); //1-4
                                        } else {
                                            Arc(hdc, nx[i], ny[i] - 50, nx[j], ny[j] + 50, nx[j], ny[j], nx[i], ny[i]);
                                            arrow((-145 * 3.1416) / 180, nx[j] - 16 * cos(-45) - 2, ny[j] + 16 * sin(-45) - 2); //1-3
                                        }
                                    } else if (nx[i] > nx[j]) {
                                        if (nx[i] == nx[j] + 3 * num) {
                                            Arc(hdc, nx[i], ny[i] - 70, nx[j], ny[j] + 70, nx[j], ny[j], nx[i], ny[i]);
                                            arrow((40 * 3.1416) / 180, nx[j] + dx * cos(-145) - 7, ny[j] + dy * sin(-145) + 27); //4-1
                                        } else {
                                            Arc(hdc, nx[i], ny[i] - 50, nx[j], ny[j] + 50, nx[j], ny[j], nx[i], ny[i]);
                                            arrow((25 * 3.1416) / 180, nx[j] + dx * cos(-145) - 7, ny[j] + dy * sin(-145) + 25); //3-1
                                        }
                                    }
                                } else if (i >= n * 0.5 && i <= 10) {
                                    if (nx[i] < nx[j]) {
                                        if ((nx[i] + 3 * num == nx[j]) || (nx[i] == nx[j] + 3 * num)) {
                                            Arc(hdc, nx[i], ny[i] - 70, nx[j], ny[j] + 70, nx[j], ny[j], nx[i], ny[i]); //10-7
                                            arrow((-140 * 3.1416) / 180, nx[j] + dx * cos(-145) - 28, ny[j] + dy * sin(-145) - 8);
                                        } else {

                                            Arc(hdc, nx[i], ny[i] - 30, nx[j], ny[j] + 30, nx[j], ny[j], nx[i], ny[i]);
                                            arrow((-160 * 3.1416) / 180, nx[j] + dx * cos(-145) - 34, ny[j] + dy * sin(-145) - 2);
                                        }
                                    } else if (nx[i] > nx[j]) {
                                        Arc(hdc, nx[i], ny[i] - 40, nx[j], ny[j] + 40, nx[j], ny[j], nx[i], ny[i]);
                                        if ((nx[i] + 3 * num == nx[j]) || (nx[i] == nx[j] + 3 * num)) {
                                            arrow((20 * 3.1416) / 180, nx[j] + dx * cos(-145) - 2, ny[j] + dy * sin(-145) + 22); //7-10
                                        } else {
                                            arrow((25 * 3.1416) / 180, nx[j] + dx * cos(-145) - 2, ny[j] + dy * sin(-145) + 24);
                                        }
                                    }
                                }
                            } else if (((nx[i] == nx[j]) && (ny[j] != ny[i] + num) && (ny[j] != ny[i] - num) && (nx[i] == num || nx[i] == num * 4)) &&
                                       ((nx[i] == nx[j]) && (ny[j] != ny[i] + num * 1.5) && (ny[j] != ny[i] - num * 1.5))) {
                                if (i >= n * 0.25 && i <= 7) {
                                    if (ny[i] < ny[j]) {
                                        Arc(hdc, nx[i] - 40, ny[i], nx[j] + 40, ny[j], nx[j], ny[j], nx[i], ny[i]);
                                        if (ny[i] + 2 * num == ny[j]) {
                                            arrow((-70 * 3.1416) / 180, nx[j] + dx * cos(-145) - 2, ny[j] + dy * sin(-145) - 5); //4-6
                                        } else {
                                            arrow((-70 * 3.1416) / 180, nx[j] + dx * cos(-145) - 4, ny[j] + dy * sin(-145) - 7); //4-7
                                        }
                                    } else if (ny[i] > ny[j]) {
                                        Arc(hdc, nx[j] - 100, ny[j], nx[i] + 100, ny[i], nx[i], ny[i], nx[j], ny[j]);
                                        if (ny[i] == ny[j] + 2 * num) {
                                            arrow((30 * 3.1416) / 180, nx[j] + dx * cos(-145) + 1, ny[j] + dy * sin(-145) + 13); //6-4
                                        } else {
                                            arrow((40 * 3.1416) / 180, nx[j] + dx * cos(-145) + 2, ny[j] + dy * sin(-145) + 15); //7-4
                                        }
                                    }
                                } else if ((i >= 9) || (j >= 9)) {
                                    if (ny[i] < ny[j]) {
                                        Arc(hdc, nx[j] - 80, ny[j], nx[i] + 80, ny[i], nx[i], ny[i], nx[j], ny[j]);
                                        arrow((-130 * 3.1416) / 180, nx[j] + dx * cos(-145) - 36, ny[j] + dy * sin(-145) + 2); //
                                    } else if (ny[i] > ny[j]) {
                                        Arc(hdc, nx[i] - 40, ny[i], nx[j] + 40, ny[j], nx[j], ny[j], nx[i], ny[i]);
                                        arrow((110 * 3.1416) / 180, nx[j] + dx * cos(-145) - 30, ny[j] + dy * sin(-145) + 27);
                                    }
                                }
                            } else {
                                double fi = 3.141 + acos((nx[j] - nx[i]) / (sqrt((nx[j] - nx[i]) * (nx[j] - nx[i]) + (ny[j] - ny[i]) * (ny[j] - ny[i]))));
                                if (ny[j] < ny[i]) fi *= -1;

                                if (graphMatrix[i][j] == graphMatrix[j][i] && i < j) {
                                    if ((ny[i] + 3 * num == ny[j]) || (ny[i] == ny[j] + 3 * num)) {
                                        MoveToEx(hdc, nx[i] + 5, ny[i] + 5, NULL);
                                        LineTo(hdc, nx[j] + 5, ny[j] + 5);
                                        if (nx[i] == nx[j] + 3 * num) {
                                            arrow(fi, nx[j] + dx * cos(fi) + 5, ny[j] + dy * sin(fi) + 7); //4-10
                                        } else {
                                            if (nx[i] == nx[j]) {
                                                arrow(fi, nx[j] + dx * cos(fi) + 7, ny[j] + dy * sin(fi)); //2-9 3-8
                                            } else {
                                                if (nx[i] < nx[j]) {
                                                    arrow(fi, nx[j] + dx * cos(fi) + 2, ny[j] + dy * sin(fi)); //1-8
                                                } else {
                                                    arrow(fi, nx[j] + dx * cos(fi) + 6, ny[j] + dy * sin(fi) + 3); //2-10
                                                }
                                            }
                                        }
                                    } else {
                                        MoveToEx(hdc, nx[i] + 10, ny[i] + 5, NULL);
                                        LineTo(hdc, nx[j] + 15, ny[j] + 5);
                                        if (ny[i] + num == ny[j]) {
                                            arrow(fi + 0.1, nx[j] + dx * cos(fi) + 5, ny[j] + 15 + dy * sin(fi)); //6-8
                                        } else if ((ny[i] == ny[j] + num * 1.5) || (ny[i] + num * 1.5 == ny[j])) {
                                            if (nx[i] == nx[j]) {
                                                arrow(fi, nx[j] + dx * cos(fi) + 7, ny[j] + 5 + dy * sin(fi) - 4); //1-11
                                            } else {
                                                if (nx[i] == nx[j] + 3 * num) {
                                                    arrow(fi, nx[j] + dx * cos(fi) + 2, ny[j] + dy * sin(fi) + 12); //4-11
                                                } else {
                                                    arrow(fi, nx[j] + dx * cos(fi) - 2, ny[j] + dy * sin(fi) + 2); //8-11
                                                }
                                            }
                                        } else {
                                            if ((nx[i] == nx[j] + num) || (nx[i] + num == nx[j])) {
                                                arrow(fi, nx[j] + dx * cos(fi), ny[j] + 5 + dy * sin(fi));
                                            } else {
                                                if (ny[i] + 2 * num == ny[j]) {
                                                    arrow(fi, nx[j] + dx * cos(fi) + 3, ny[j] + dy * sin(fi) + 14); //5-10
                                                } else {
                                                    arrow(fi, nx[j] + dx * cos(fi), ny[j] + 3 + dy * sin(fi)); //6-11
                                                }
                                            }
                                        }
                                    }
                                } else if (graphMatrix[i][j] == graphMatrix[j][i] && i > j) {
                                    if ((ny[i] + 3 * num == ny[j]) || (ny[i] == ny[j] + 3 * num)) {
                                        MoveToEx(hdc, nx[i] - 10, ny[i] - 5, NULL);
                                        LineTo(hdc, nx[j] - 15, ny[j] - 5);
                                        if (nx[i] + 3 * num == nx[j]) {
                                            arrow(fi, nx[j] + dx * cos(fi) - 7, ny[j] - 5 + dy * sin(fi) - 7); //10-4
                                        } else {
                                            if (nx[i] == nx[j]) {
                                                arrow(fi, nx[j] + dx * cos(fi) - 14, ny[j] - 5 + dy * sin(fi)); //9-2 8-3
                                            } else {
                                                if (nx[i] > nx[j]) {
                                                    arrow(fi, nx[j] + dx * cos(fi) - 10, ny[j] - 5 + dy * sin(fi) + 7); //8-1
                                                } else {
                                                    arrow(fi, nx[j] + dx * cos(fi) - 12, ny[j] - 5 + dy * sin(fi) - 3); //10-2
                                                }
                                            }
                                        }
                                    } else {
                                        MoveToEx(hdc, nx[i] - 10, ny[i] - 5, NULL);
                                        LineTo(hdc, nx[j] - 15, ny[j] - 5);
                                        if (ny[i] == ny[j] + num) {
                                            arrow(fi - 0.1, nx[j] + dx * cos(fi) - 5, ny[j] + dy * sin(fi) - 15); //8-6
                                        } else if ((ny[i] == ny[j] + num * 1.5) || (ny[i] + num * 1.5 == ny[j])) {
                                            if (nx[i] == nx[j]) {
                                                arrow(fi, nx[j] + dx * cos(fi) - 4, ny[j] - 5 + dy * sin(fi) + 5); //11-1
                                            } else {
                                                if (nx[i] + 3 * num == nx[j]) {
                                                    arrow(fi, nx[j] + dx * cos(fi) - 4, ny[j] + dy * sin(fi) - 10); //11-4
                                                } else {
                                                    arrow(fi, nx[j] + dx * cos(fi) + 1, ny[j] - 5 + dy * sin(fi) + 2); //11-8
                                                }
                                            }
                                        } else {
                                            if ((nx[i] == nx[j] + num) || (nx[i] + num == nx[j])) {
                                                arrow(fi, nx[j] + dx * cos(fi), ny[j] - 5 + dy * sin(fi));
                                            } else {
                                                if (ny[i] == ny[j] + 2 * num) {
                                                    arrow(fi, nx[j] + dx * cos(fi) - 2, ny[j] + dy * sin(fi) - 13); //10-5
                                                } else {
                                                    arrow(fi, nx[j] + dx * cos(fi), ny[j] - 2 + dy * sin(fi)); //11-6
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    LineTo(hdc, nx[j], ny[j]);
                                    arrow(fi, nx[j] + dx * cos(fi) + 1, ny[j] + dy * sin(fi)); //
                                }
                            }
                        }
                    }
                }

                SelectObject(hdc, BPen);
                for (i = 0; i < n; i++) {
                    Ellipse(hdc, nx[i] - dx, ny[i] - dy, nx[i] + dx, ny[i] + dy);
                    if (i < 9) {
                        TextOut(hdc, nx[i] - dtx, ny[i] - dy / 2, nn[i], 1);
                    } else TextOut(hdc, nx[i] - dtx, ny[i] - dy / 2, nn[i], 2);
                }

            }

            void drawGraphUndir(double ** graphMatrix) {
                SelectObject(hdc, KPen);

                for (int i = 0; i < 11; i++) {
                    for (int j = 0; j < 11; j++) {
                        if (graphMatrix[i][j] == 1) {
                            MoveToEx(hdc, nx[i], ny[i], NULL);

                            if ((ny[i] == ny[j]) && (nx[j] != nx[i] + num) && (nx[j] != nx[i] - num)) {

                                if (i < 4) {
                                    if (nx[i] < nx[j]) {
                                        Arc(hdc, nx[i], ny[i] - 50, nx[j], ny[j] + 50, nx[j], ny[j], nx[i], ny[i]);
                                    } else if (nx[i] > nx[j]) {
                                        Arc(hdc, nx[j], ny[j] - 40, nx[i], ny[i] + 40, nx[i], ny[i], nx[j], ny[j]);
                                    }
                                } else if (i > 5 && i < 10) {
                                    if (nx[i] < nx[j]) {
                                        Arc(hdc, nx[j], ny[j] - 50, nx[i], ny[i] + 50, nx[i], ny[i], nx[j], ny[j]);
                                    } else if (nx[i] > nx[j]) {
                                        Arc(hdc, nx[i], ny[i] - 40, nx[j], ny[j] + 40, nx[j], ny[j], nx[i], ny[i]);
                                    }
                                }
                            } else if (((nx[i] == nx[j]) && (ny[j] != ny[i] + num) && (ny[j] != ny[i] - num) && (nx[i] == num || nx[i] == num * 4)) &&
                                       ((nx[i] == nx[j]) && (ny[j] != ny[i] + num * 1.5) && (ny[j] != ny[i] - num * 1.5))) {

                                if (i > 2 && i < 7) {
                                    if (ny[i] < ny[j]) {
                                        Arc(hdc, nx[i] - 40, ny[i], nx[j] + 40, ny[j], nx[j], ny[j], nx[i], ny[i]);
                                    } else if (ny[i] > ny[j]) {
                                        Arc(hdc, nx[j] - 50, ny[j], nx[i] + 50, ny[i], nx[i], ny[i], nx[j], ny[j]);
                                    }
                                } else if (i > 8) {
                                    if (ny[i] < ny[j]) {
                                        Arc(hdc, nx[j] - 40, ny[j], nx[i] + 40, ny[i], nx[i], ny[i], nx[j], ny[j]);
                                    } else if (ny[i] > ny[j]) {
                                        Arc(hdc, nx[i] - 40, ny[i], nx[j] + 40, ny[j], nx[j], ny[j], nx[i], ny[i]);
                                    }
                                }
                            } else {
                                LineTo(hdc, nx[j], ny[j]);
                            }
                        }
                    }
                }

                /////////////////////////Æåïà çàêîí÷èëàñü (íåò) \\\\\\\\\\\\\\\\\\\\\\\\\
      SelectObject(hdc, BPen);
                for (i = 0; i < 11; i++) {
                    Ellipse(hdc, nx[i] - dx, ny[i] - dy, nx[i] + dx, ny[i] + dy);
                    if (i < 10) {
                        TextOut(hdc, nx[i] - dtx, ny[i] - dy / 2, nn[i], 2);
                    } else TextOut(hdc, nx[i] - dtx, ny[i] - dy / 2, nn[i], 2);
                }
            }

            double ** reach_connectivity_Matrix(double ** matrix, int rows, int cols) {
                printf("\n\nThe reach matrix is:\n");
                int reach[rows][cols];
                int transitiveMatrix[rows][cols];
                int connectivityMatrix[rows][cols];

                for (int i = 0; i < rows; i++)
                    for (int j = 0; j < cols; j++)
                        reach[i][j] = matrix[i][j];

                for (int k = 0; k < rows; k++) {
                    for (int i = 0; i < cols; i++) {
                        for (int j = 0; j < cols; j++) {
                            reach[i][j] = reach[i][j] ||
                                          (reach[i][k] && reach[k][j]);
                        }
                    }
                }
                for (int i = 0; i < rows; i++) //Вивід матриці досяжності
                {
                    for (int j = 0; j < cols; j++) {
                        printf("%d ", reach[i][j]);
                    }
                    printf("\n");

                }
                for (int i = 0; i < 11; i++) {
                    for (int j = 0; j < 11; j++) {
                        transitiveMatrix[i][j] = reach[j][i];
                    }
                } {

                    int counter = 1;
                    int countery = 1;
                    double ** used_verticles = (double * ) malloc(n * sizeof(double * ));
                    for (int i = 0; i < n; i++)
                        used_verticles[i] = (double * ) malloc(n * sizeof(double));
                    double ** components = (double * ) malloc(n * sizeof(double * ));
                    for (int i = 0; i < n; i++)
                        components[i] = (double * ) malloc(n * sizeof(double));
                    double powered[n][n];
                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < n; j++) {
                            powered[i][j] = 0;
                            for (int k = 0; k < n; k++)
                                powered[i][j] += reach[i][k] * reach[k][i];
                        }
                    }
                    for (int count = 0; count < rows; count++) {
                        counter = 1;
                        for (int i = 0; i < cols; i++) {
                            if (used_verticles[i] == 1) continue;
                            for (int j = 0; j < rows; j++) {
                                if (powered[count][j] != powered[i][j]) break;
                                if (j == rows - 1) {
                                    used_verticles[i] = 1;
                                    components[countery][i] = 1;
                                    printf("Komponent %d\n", countery);
                                    counter++;
                                }
                            }
                        }
                        if (components[countery][0] || components[countery][1] || components[countery][2] ||
                            components[countery][3] || components[countery][4] || components[countery][5] ||
                            components[countery][6] || components[countery][7] || components[countery][8] ||
                            components[countery][9] || components[countery][10]) countery++;
                    }

                    for (int i = 0; i < 11; i++) {
                        for (int j = 0; j < 11; j++) {
                            if (reach[i][j] == 1 && transitiveMatrix[i][j] == 1) {
                                connectivityMatrix[i][j] = 1;
                            } else {
                                connectivityMatrix[i][j] = 0;
                            }
                        }
                    }
                    printf("\n");
                    printf("Connectivity matrix is: \n");
                    for (int i = 0; i < 11; i++) //Вивід матриці зв'язності
                    {
                        for (int j = 0; j < 11; j++) {
                            printf("%d ", connectivityMatrix[i][j]);
                        }
                        printf("\n");
                    }
                }

                /*  {
                      bool condensationStatus =true;
                        for (int i = 0; i < 11; i++)
                  {
                      for (int j = 0; j < 11; j++)
                      {
                          if (connectivityMatrix[i][j]==0) condensationStatus =false;
                      }
                      }
                                  if (condensationStatus == true){
                          printf("\n\nThe graph is strongly connected");
                          Ellipse(hdc, 600, 600, 380, 380);
                          TextOut(hdc, 385, 475, "Strongly connected graph",25 );
                  }else{
                  }
                  } */

            }

            printf("Directed graph:\n");
            printGrapgMatrix(A);
            printf("Undirected graph:\n");
            printGrapgMatrix(B);

            drawGraphDir(A); //напрямленний граф
            drawGraphUndir(B); //ненапрямленний граф
            graphPower(A, B, n, n); //степені вершин та відображення висячих та ізольованих вершин
            wayMatrix(A, n, n); //шляхи довжиною 2 та 3
            reach_connectivity_Matrix(A, n, n); //матриця досяжності, матриця зв’язності , компоненти сильної зв'язності та граф конденсації

            EndPaint(hWnd, & ps); //малювання закінчене
            break;

            //сообщение выхода - разрушение окна
        case WM_DESTROY:
            PostQuitMessage(0); //Посылаем сообщение выхода с кодом 0 - нормальное завершение
            break;

        default:
            return (DefWindowProc(hWnd, messg, wParam, lParam)); //освобождаем очередь приложения от нераспознаных
    }
    return 0;
}