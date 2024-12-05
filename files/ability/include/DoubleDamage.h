#ifndef DOUBLEDAMAGE_H
#define DOUBLEDAMAGE_H

class GameField;
#include "Ability.h"
#include "GameField.h"
#include "ManagerShips.h"
#include <iostream>
#include <windows.h>


class DoubleDamage : public Ability {
private:
    bool isActive;  // Флаг, активирована ли способность

public:
    DoubleDamage();  // Конструктор
    void use(ManagerShips& managerShips, GameField& field,int cursorX, int cursorY) override;  // Переопределение метода
    bool applyDoubleDamage();  // Метод для применения двойного урона
    std::string getName() const override;
};

#endif // DOUBLEDAMAGE_H
