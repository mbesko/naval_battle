#ifndef PLAYER_H
#define PLAYER_H

#include "ManagerShips.h"
#include "GameField.h"
#include "Console.h"
#include <string>

// Класс игрока, управляющий его полем и кораблями
class Player {
private:
    GameField field;  // Игровое поле игрока
    ManagerShips managerShips;  // Менеджер для управления кораблями
    std::string name;  // Имя игрока

public:
    Player(const std::string& name, int fieldSize, int oneDeck, int twoDeck, int threeDeck, int fourDeck);  // Конструктор, создающий поле нужного размера
    void placeShips();  // Размещение кораблей игроком
    Player(Player&& other) noexcept;
    Player& operator=(Player&& other) noexcept;


    bool takeTurn(Player& opponent, Player& currentPlayer);  // Ход игрока: выполнение выстрела
    GameField& getField();  // Получение игрового поля игрока
    std::string getName() const;  // Получение имени игрока
    void initShips(int oneDeck, int twoDeck, int threeDeck, int fourDeck);  // Инициализация кораблей
};

#endif

