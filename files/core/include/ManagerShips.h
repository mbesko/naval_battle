#ifndef MANAGERSHIPS_H
#define MANAGERSHIPS_H

#include <vector>
#include "Ship.h"
#include "../../game_field/include/GameField.h"
#include "Console.h"
#include <memory>

// Класс для управления кораблями
class ManagerShips {
private:
    //std::vector<Ship> ships;  // Список кораблей
    std::vector<std::unique_ptr<Ship>> ships;

public:
    ManagerShips(int oneDeck, int twoDeck, int threeDeck, int fourDeck);
    ~ManagerShips();
// Удаляем конструктор копирования и оператор присваивания копированием
    ManagerShips(const ManagerShips&) = delete;
    ManagerShips& operator=(const ManagerShips&) = delete;

    // Разрешаем перемещение
    ManagerShips(ManagerShips&&) = default;
    ManagerShips& operator=(ManagerShips&&) = default;

    // Добавление и размещение корабля
    void createAndPlaceShip(GameField& field, int length, int x, int y, Orientation orientation);
    void createAndPlaceShip1(GameField& field, Ship& newShip, int x, int y);

    //void attackShip(int shipIndex, int segmentIndex);

    // Проверка, остались ли корабли в живых
    bool anyShipsLeft() const;

    // Отображение статуса кораблей
    void displayShipsStatus() const;

    // Метод для добавления кораблей
    void addShips(int oneDeck, int twoDeck, int threeDeck, int fourDeck);

    // Метод для получения всех кораблей
    std::vector<std::unique_ptr<Ship>>& getShips();

    void displayAliveShipsBySize(int x, int y) const;
};

#endif // MANAGERSHIPS_H
