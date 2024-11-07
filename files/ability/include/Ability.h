#ifndef ABILITY_H
#define ABILITY_H

class GameField;
class ManagerShips;
//#include "ManagerShips.h"
#include <iostream>



class Ability {
public:
    virtual ~Ability() = default;

    // Чисто виртуальный метод, который каждая способность должна реализовать
    virtual void use(ManagerShips& managerShips, GameField& field, int cursorX, int cursorY) = 0;
    // Новый метод для получения имени способности
    virtual std::string getName() const = 0;
};

#endif // ABILITY_H
