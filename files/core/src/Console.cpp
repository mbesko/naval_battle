#include "Console.h"
#include <iostream>

HANDLE Console::hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void Console::clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Console::GoToXY(short x, short y) {
    SetConsoleCursorPosition(hStdOut, {x, y});
}

void Console::setCursorVisible(bool show, short size) {
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = show;
    structCursorInfo.dwSize = size;
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

void Console::setTextAttribute(int color) {
    SetConsoleTextAttribute(hStdOut, color);
}
