#include <stdio.h>
#include <windows.h>
void PrintCharAtCursorPosition(int XPos, int YPos, char c[])
{
    COORD coord;
    coord.X = XPos;
    coord.Y = YPos;
    SetConsoleCursorPosition ( GetStdHandle (STD_OUTPUT_HANDLE), coord );
    printf ("%s", c);
    Sleep(3);
}

int main()
{
    int x = 12;
    int y = 12;

    int BottomLimY = 13;
    int UpperLimY = 12;
    int LeftLimX = 11;
    int RightLimX = 66;

    for (int i = 1; i <= 13; i++){
        while (x < RightLimX){
            PrintCharAtCursorPosition(x, UpperLimY, "*");
            x++;
        }
        UpperLimY--;
        while (y < BottomLimY){
            PrintCharAtCursorPosition(RightLimX, y, "*");
            y++;
        }
        RightLimX++;
        while (x > LeftLimX){
            PrintCharAtCursorPosition(x, BottomLimY, "*");
            x--;
        }
        BottomLimY++;
        if (i != 13){
            while (y > UpperLimY){
                PrintCharAtCursorPosition(LeftLimX, y, "*");
                y--;
            }
            LeftLimX--;
        }
    }
    while(1){}
}
