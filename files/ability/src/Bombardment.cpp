#include "Bombardment.h"


void Bombardment::use(ManagerShips& managerShips, GameField& field, int cursorX, int cursorY) {
    auto& ships = managerShips.getShips();

    if (!ships.empty()) {
        // Выбираем случайный корабль
        int randomShipIndex = rand() % ships.size();
        Ship& ship = *ships[randomShipIndex];

        // Выбираем случайный сегмент
        int randomSegmentIndex = rand() % ship.getLength();
        ship.takeDamage(randomSegmentIndex);

        std::cout << "\n\n\nПроизведен обстрел! Сегмент корабля поврежден." << std::endl;
    } else {
        std::cout << "\n\n\nУ противника нет кораблей для обстрела." << std::endl;
    }
}

std::string Bombardment::getName() const {
    return "Обстрел";
}