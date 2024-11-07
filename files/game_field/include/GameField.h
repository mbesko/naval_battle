// GameField.h
#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "../../entities/include/Ship.h"
#include "../../core/include/GameState.h"
#include <vector>
#include "../../entities/include/Cell.h"
#include "GameFieldDisplay.h"
#include "GameField.h"
#include "GameFieldInput.h"
#include <iomanip>


class GameField : public GameState {
private:
    int size;

    int width, height;  // Размеры поля
    std::vector<std::vector<Cell>> grid;  // Игровое поле
    int cursorX; int cursorY; // Позиция курсора

    GameFieldDisplay gameFieldDisplay;
    GameFieldInput input;


public:

    // Конструкторы копирования и перемещения
    GameField(const GameField& other);  // Конструктор копирования
    GameField(GameField&& other) noexcept;  // Конструктор перемещения

// Операторы присваивания
    GameField& operator=(const GameField& other);  // Оператор копирующего присваивания
    GameField& operator=(GameField&& other) noexcept;  // Оператор перемещающего присваивания
//    ~GameField();

    void setZeroCursor();
    GameField(int size); // Конструктор игрового поля
    void display(Ship* currentShip = nullptr, int go = 0, bool enemy = true, bool open = false); //override; // Отображение игрового поля
    void handleInput(bool& actionConfirmed, Ship* currentShip); //override;  // Обработка перемещения и действий (размещение/выстрел)

    void executeAction(bool& actionConfirmed, int selectedGameField, Ship* currentShip);



    bool placeShip(Ship& ship, int x, int y);  // Размещение корабля на поле

    void setStateUnknown();
    void attack(int x, int y);  // Выстрел по клетке
    bool areAllShipsSunk() const;  // Проверка, все ли корабли уничтожены

//    void display();

//    // Реализация чисто виртуальных методов
    void display() override;  // Для вызова без параметров
    void handleInput() override;  // Для вызова без параметров
    void clean();



    bool isNearShip(int x, int y);
    int getSize();
//    int getShipPoint();
};

#endif
