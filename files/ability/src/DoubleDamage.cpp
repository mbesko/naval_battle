#include "DoubleDamage.h"

DoubleDamage::DoubleDamage() : isActive(false) {}

void DoubleDamage::use(ManagerShips& managerShips, GameField& field, int cursorX, int cursorY) {
    field.attack(cursorX,cursorY);
    Sleep(1000);
    field.attack(cursorX,cursorY);
}

bool DoubleDamage::applyDoubleDamage() {
    if (isActive) {
        isActive = false;
        return true;
    }
    return false;
}

std::string DoubleDamage::getName() const {
    return "Двойной урон";
}
