#include "ManagerShips.h"
#include <iostream>
#include <memory>
#include <map>


ManagerShips::ManagerShips(int oneDeck, int twoDeck, int threeDeck, int fourDeck){
    this->addShips( oneDeck, twoDeck, threeDeck, fourDeck);
}

ManagerShips::~ManagerShips(){}


void ManagerShips::createAndPlaceShip(GameField& field, int length, int x, int y, Orientation orientation) {
    auto newShip = std::make_unique<Ship>(length, orientation);
    if (field.placeShip(*newShip, x, y)) {  // Передаем разыменованный указатель
        ships.push_back(std::move(newShip));  // Перемещаем уникальный указатель в вектор
    }

}
// Проверка, остались ли корабли в живых
bool ManagerShips::anyShipsLeft() const {
    for (const auto& shipPtr : ships) {  // Используйте auto для указателя
        if (shipPtr && !shipPtr->isSunk()) {  // Проверьте, существует ли указатель и не потоплен ли корабль
            return true;
        }
    }
    return false;
}

// Отображение статуса кораблей
void ManagerShips::displayShipsStatus() const {
    for (std::vector<std::unique_ptr<Ship>>::size_type i = 0; i < ships.size(); ++i) {
        std::cout << "Ship " << i + 1 << " is "
                  << (ships[i]->isSunk() ? "sunk" : "alive") << std::endl;  // Разыменуйте указатель
    }
}

// Добавление кораблей с разной палубностью
void ManagerShips::addShips(int oneDeck, int twoDeck, int threeDeck, int fourDeck) {
    for (int i = 0; i < oneDeck; ++i) {
        ships.push_back(std::make_unique<Ship>(1, Orientation::Horizontal));
    }
    for (int i = 0; i < twoDeck; ++i) {
        ships.push_back(std::make_unique<Ship>(2, Orientation::Horizontal));
    }
    for (int i = 0; i < threeDeck; ++i) {
        ships.push_back(std::make_unique<Ship>(3, Orientation::Horizontal));
    }
    for (int i = 0; i < fourDeck; ++i) {
        ships.push_back(std::make_unique<Ship>(4, Orientation::Horizontal));
    }
}

// Возвращение всех кораблей
std::vector<std::unique_ptr<Ship>>& ManagerShips::getShips() {
    return ships;
}

void ManagerShips::displayAliveShipsBySize(int x, int y) const {
    // Создаем карту для подсчета живых кораблей по размеру (от 1 до 4 палуб)
    std::map<int, int> aliveShipsBySize = {{1, 0}, {2, 0}, {3, 0}, {4, 0}};

    // Проходим по каждому кораблю
    for (const auto& shipPtr : ships) {
        if (shipPtr && !shipPtr->isSunk()) {
            int size = shipPtr->getLength();
            aliveShipsBySize[size]++;
        }
    }

    // Выводим графическое представление живых кораблей
    Console::GoToXY(x, y);
    for (const auto& [size, count] : aliveShipsBySize) {
        Console::GoToXY(x, ++y);
        // Выводим графическое представление корабля
        for (int j = 0; j < size; ++j) {
            std::cout << "■"; // Символ для представления палубы корабля
        }
        std::cout << " - " << count << " шт."; // Количество кораблей

    }
}


