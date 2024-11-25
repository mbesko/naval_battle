#ifndef BOMBARDMENT_H
#define BOMBARDMENT_H


class GameField;
#include "Ability.h"
#include "Player.h"
#include "ManagerShips.h"
#include "Ship.h"
#include "GameField.h"

#include <iostream>
#include <cstdlib>

class Bombardment : public Ability {
public:
    void use(ManagerShips& managerShips, GameField& field,int cursorX, int cursorY) override;  // Переопределение метода
    std::string getName() const override;

};

#endif // BOMBARDMENT_H
