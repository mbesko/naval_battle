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
        case 'R':  // Выбор случайной способности и её использование
        case 'r':
            return 20;
        case 'T':
        case 't':  // Изменение ориентации корабля во время размещения
            return 10;
        case 'J':
        case 'j':  // Изменение ориентации корабля во время размещения
            return 40;
        case 'N':
        case 'n':  // Изменение ориентации корабля во время размещения
            return 30;
        case ENTER:  // Подтверждение действия (размещение корабля или выстрел)
            return 1;
        default:
            return 0;
    }
}