#include "../../entities/include/Ship.h"
#include "../../core/include/GameState.h"
#include <vector>
#include "../../entities/include/Cell.h"
#include <iomanip>

#ifndef NAVAL_BATTLE_GAMEFIELDDISPLAY_H
#define NAVAL_BATTLE_GAMEFIELDDISPLAY_H


class GameFieldDisplay {
public:
    void displayGameField(Ship* currentShip, int go, bool enemy, bool open, int width, int height, int cursorX, int cursorY, std::vector<std::vector<Cell>> grid) const;
    void printTopBottomBorder(int size) const; //  для вывода верхней и нижней границы с буквами
    void printHorizontalDivider(int size) const; // Функция для вывода горизонтальной линии

    // Анимация для выстрела
    void animateShot(int fromX, int fromY, int toX, int toY);
    static void keyboardLayout();




    // Анимация для попадания
    void animateHit(int x, int y);

};


#endif //NAVAL_BATTLE_GAMEFIELDDISPLAY_H
