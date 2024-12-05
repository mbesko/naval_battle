#include "Scanner.h"

void Scanner::use(ManagerShips& managerShips, GameField& field,int cursorX, int cursorY) {
    int x = cursorX;
    int y = cursorY;

    bool shipFound = false;

    for (int i = y; i < y + 2 && i < field.getSize(); ++i) {
        for (int j = x; j < x + 2 && j < field.getSize(); ++j) {
            if (field.getCell(j, i).getShipPart() != nullptr) {
                shipFound = true;
                break;
            }
        }
    }

    if (shipFound) {
        std::cout << "Корабль найден в этом районе!" << std::endl;
    } else {
        std::cout << "Кораблей в этом районе нет." << std::endl;
    }
}

std::string Scanner::getName() const  {
    return "Сканер";
}