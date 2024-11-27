#ifndef SCANNER_H
#define SCANNER_H

//class GameField;
#include "Ability.h"
#include "Player.h"
#include "GameField.h"
#include "ManagerShips.h"
#include "Cell.h"
#include "Ship.h"

#include <iostream>

class Scanner : public Ability {
public:
    void use(ManagerShips& managerShips, GameField& field,int cursorX, int cursorY) override;  // Переопределение метода
    std::string getName() const override;

};

#endif // SCANNER_H
