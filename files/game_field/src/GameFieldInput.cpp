//
// Created by Maxim on 07.11.2024.
//

#include "../include/GameFieldInput.h"


int GameFieldInput::handleGameFieldInput(int &cursorX, int &cursorY, int height, int width) {
    char ch = _getch();
    switch (ch) {
        case UP: // Перемещение курсора вверх
            if (cursorY > 0) cursorY--;
            return 2;
        case DOWN: // Перемещение курсора вниз
            if (cursorY < height - 1) cursorY++;
            return 2;
        case LEFT: // Перемещение курсора влево
            if (cursorX > 0) cursorX--;
            return 2;
        case RIGHT:  // Перемещение курсора вправо
            if (cursorX < width - 1) cursorX++;
            return 2;
        case 'T':
        case 't':  // Изменение ориентации корабля во время размещения
            return 10;
        case ENTER:  // Подтверждение действия (размещение корабля или выстрел)
            return 1;
        default:
            return 0;
    }
}