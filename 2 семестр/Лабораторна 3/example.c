#include<windows.h>
#include<math.h>
//������ �������� ������� ����, ������� ����� ���������� ����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//void arrow(float fi, int px,int py);

//��������� ������-��� ���������
char ProgName[]="����������� ������ 3";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w; //������ ��������� ��������� WNDCLASS

    w.lpszClassName=ProgName; //��� ��������� - ��������� ����
    w.hInstance=hInstance; //������������� �������� ����������
    w.lpfnWndProc=WndProc; //��������� �� ������� ����
    w.hCursor=LoadCursor(NULL, IDC_ARROW); //��������� ������
    w.hIcon=0; //������ � ��� �� ����� ����
    w.lpszMenuName=0; //� ���� ���� �� �����
    w.hbrBackground = LTGRAY_BRUSH; //WHITE_BRUSH;// ���� ���� ����
    w.style=CS_HREDRAW|CS_VREDRAW; //����� - ���������������� �� � � �� �
    w.cbClsExtra=0;
    w.cbWndExtra=0;

    if(!RegisterClass(&w))
        return 0;

   // HWND hWnd;
    //MSG lpMsg;

//�������� ���� � ������, �������� ��������� CreateWindow
    hWnd=CreateWindow(ProgName, //��� ���������
        "����������� ������ 3. ������� �.�.���㳺���", //��������� ����
        WS_OVERLAPPEDWINDOW, //����� ���� - ���������������
        100, //��������� ���� �� ������ �� �
        100, //��������� �� �
        360, //������
        250, //������
        (HWND)NULL, //������������� ������������� ����
        (HMENU)NULL, //������������� ����
        (HINSTANCE)hInstance, //������������� ���������� ���������
        (HINSTANCE)NULL); //���������� �������������� ����������

//������� ���� �� ������ �� �����
    ShowWindow(hWnd, nCmdShow);
//������� ���������� ����
 //   UpdateWindow(hWnd);

//���� ��������� ����������

    while(GetMessage(&lpMsg, hWnd, 0, 0)) { //�������� ��������� �� �������
            TranslateMessage(&lpMsg); //����������� ��������� ������ � �������
            DispatchMessage(&lpMsg); //������� ��������� ��������������� ������� ����
        }
    return(lpMsg.wParam);
    }

//������� ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
                        WPARAM wParam, LPARAM lParam)
    {
    HDC hdc; //������ �������� ����������
    PAINTSTRUCT ps; //������ ��������� ��������� ������������ ������

    void arrow(float fi, int px,int py){
            fi = 3.1416*(180.0 - fi)/180.0;
            int lx,ly,rx,ry; //px,py,
           // px=150; py=60;
            lx = px+15*cos(fi+0.3);
            rx = px+15*cos(fi-0.3);
            ly = py+15*sin(fi+0.3);
            ry = py+15*sin(fi-0.3);
            MoveToEx(hdc, lx, ly, NULL);
            LineTo(hdc, px, py);
            LineTo(hdc, rx, ry);
         //  return 0;
      }

//���� ��������� ���������
    switch(messg){
    //��������� ���������
        case WM_PAINT :


            hdc=BeginPaint(hWnd, &ps);
            char *nn[3] = {"1", "2", "3"};
            int nx[3] = {100,200,300};
            int ny[3] = {70,70,70};
            int dx = 16, dy = 16, dtx = 5;
            int i;
            HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
            HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

            SelectObject(hdc, KPen);
            MoveToEx(hdc, nx[0], ny[0], NULL); //������� �������� ���������� x1, y1
            LineTo(hdc, nx[1], ny[1]);

             arrow(0,nx[1]-dx,ny[1]);

    //  BOOL Arc(HDC hdc, int xLeft, int yTop, int xRight, int yBottom,
   //int xStart, int yStart, int xEnd, int yEnd);

            Arc(hdc, nx[0], ny[0]-40, nx[2], ny[2]+40,    nx[2], ny[2], nx[0], ny[0]);
             arrow(-45.0,nx[2]-dx*0.5,ny[2]-dy*0.8);

            SelectObject(hdc, BPen);
            for(i=0;i<=2;i++){
              Ellipse(hdc, nx[i]-dx,ny[i]-dy,nx[i]+dx,ny[i]+dy);
              TextOut(hdc, nx[i]-dtx,ny[i]-dy/2,  nn[i],1);
            }



            EndPaint(hWnd, &ps);//��������� ��������
            break;

//��������� ������ - ���������� ����
        case WM_DESTROY:
            PostQuitMessage(0); //�������� ��������� ������ � ����� 0 - ���������� ����������
            break;

        default:
            return(DefWindowProc(hWnd, messg, wParam, lParam)); //����������� ������� ���������� �� �������������
    }
    return 0;
}
