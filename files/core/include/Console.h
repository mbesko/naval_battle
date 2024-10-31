#ifndef CONSOLE_H
#define CONSOLE_H

#include <windows.h>

class Console {
public:
    static HANDLE hStdOut;

    static void clear();
    static void GoToXY(short x, short y);
    static void setCursorVisible(bool show, short size);
    static void setTextAttribute(int color);
};

#endif