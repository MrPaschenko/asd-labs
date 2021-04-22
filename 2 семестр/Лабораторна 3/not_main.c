#include <windows.h>
#include <math.h>

double ** randm(int rows, int cols) {
    double ** matrix = (double ** ) malloc(rows * sizeof(double * ));

    for (int i = 0; i < rows; i++) {
        matrix[i] = (double * ) malloc(cols * sizeof(double));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double temp = rand() % 21;
            matrix[i][j] = temp / 10;
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

double ** mulmr(double coef, double ** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = matrix[i][j] * coef;

            if (matrix[i][j] < 1.0) matrix[i][j] = 0;
            else matrix[i][j] = 1;
        }
    }
    return matrix;
}

//Создаём прототип функции окна, которая будет определена ниже
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//void arrow(float fi, int px, int py);

//объявляем строку-имя программы
char ProgName[] = "Lab_3_Pashchenko_IP-04";

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
    w.hbrBackground = WHITE_BRUSH; // цвет фона окна
    w.style = CS_HREDRAW | CS_VREDRAW; //стиль - перерисовываемое по х и по у
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if (!RegisterClass( & w)) return 0;

    //HWND hWnd;
    //MSG lpMsg;

    //Создадим окно в памяти, заполнив аргументы CreateWindow
    hWnd = CreateWindow(ProgName, //Имя программы
                        "Lab_3_Pashchenko_IP-04", //Заголовок окна
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
            /*  int radius = 200;
              int centreX = 400;
              int centreY = 300;
              for (int i = 0; i <= 10; i++){
                  nx[i] = centreX + radius * cos(0.571*i);
                  ny[i] = centreY + radius * sin(0.571*i);
              }
              nx[10]= centreX;
              ny[10]= centreY; */
            HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
            HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

            srand(419);
            double ** T = randm(11, 11);
            double coefficient = 1.0 - 1 * 0.02 - 3 * 0.005 - 0.25;
            double ** A_temp = mulmr(coefficient, T, 11, 11);
            double ** A = mirrorMatrix(A_temp, 11, 11);
            for (int i = 0; i < 11; i++) {
                for (int j = 0; j < 11; j++) {
                    printf("%g ", A[i][j]);
                }
                printf("\n");

            }

            SelectObject(hdc, KPen);

            for (int i = 0; i < 11; i++) {
                for (int j = 0; j < 11; j++) {
                    if (A[i][j] == 1) {
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

            ///////////////////////// Æåïà çàêîí÷èëàñü (íåò) \\\\\\\\\\\\\\\\\\\\\\\\\
    SelectObject(hdc, BPen);
            for (i = 0; i < 11; i++) {
                Ellipse(hdc, nx[i] - dx, ny[i] - dy, nx[i] + dx, ny[i] + dy);
                if (i < 10) {
                    TextOut(hdc, nx[i] - dtx, ny[i] - dy / 2, nn[i], 2);
                } else TextOut(hdc, nx[i] - dtx, ny[i] - dy / 2, nn[i], 2);
            }

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