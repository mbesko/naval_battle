// MenuInput.cpp
#include "MenuInput.h"
#include <conio.h>
#include <cstdlib>
#include <windows.h>

int MenuInput::handleMenuInput(int currentMenu, int menuSize) {
    char ch = _getch();
    if (ch == -32) ch = _getch(); // Обработка стрелок

    switch (ch) {
        case ESC:
            exit(0);
        case UP:
            if (currentMenu > 0) {
                PlaySound(TEXT("sounds/menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
                --currentMenu;
                return currentMenu;
            }
            break;
        case DOWN:
            if (currentMenu < menuSize - 1) {
                PlaySound(TEXT("sounds/menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
                ++currentMenu;
                return currentMenu;
            }
            break;
        case ENTER:
            PlaySound(TEXT("sounds/enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
            return currentMenu; // Возвращает выбранный пункт меню
    }
    return -1;
}
