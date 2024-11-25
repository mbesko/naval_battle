#ifndef PLAYER_H
#define PLAYER_H

#include "AbilityManager.h"
#include "ManagerShips.h"
#include "../../game_field/include/GameField.h"
#include "Console.h"
#include <string>
#include <cstdlib>
#include <ctime>

// Класс игрока, управляющий его полем и кораблями
class Player {
private:
    GameField field;  // Игровое поле игрока
    AbilityManager abilityManager;
    ManagerShips managerShips;  // Менеджер для управления кораблями
    std::string name;  // Имя игрока

public:
    Player(const std::string& name, int fieldSize, int oneDeck, int twoDeck, int threeDeck, int fourDeck);  // Конструктор, создающий поле нужного размера
    void placeShips();  // Размещение кораблей игроком
    void placeShipsRandomly();
    void randomAttack(Player& opponent);
    void cleanField();
    Player(Player&& other) noexcept;
    Player& operator=(Player&& other) noexcept;

    ManagerShips& getManagerShips();
    AbilityManager& getAbilityManager();
    bool takeTurn(Player& opponent, Player& currentPlayer);  // Ход игрока: выполнение выстрела
    GameField& getField();  // Получение игрового поля игрока
    std::string getName() const;  // Получение имени игрока
    void initShips(int oneDeck, int twoDeck, int threeDeck, int fourDeck);  // Инициализация кораблей
};

#endif

