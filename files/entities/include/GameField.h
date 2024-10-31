// GameField.h
#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "Ship.h"
#include "GameState.h"
#include <vector>
#include "Cell.h"
#include <iomanip>


class GameField /*: public GameState*/ {
private:
    int size;

    int width, height;  // Размеры поля
    std::vector<std::vector<Cell>> grid;  // Игровое поле
    int cursorX; int cursorY; // Позиция курсора


    // Анимация для выстрела
    void animateShot(int fromX, int fromY, int toX, int toY);

    // Анимация для попадания
    void animateHit(int x, int y);


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
    bool placeShip(Ship& ship, int x, int y);  // Размещение корабля на поле

    void setStateUnknown();
    void attack(int x, int y);  // Выстрел по клетке
    bool areAllShipsSunk() const;  // Проверка, все ли корабли уничтожены

//    // Реализация чисто виртуальных методов
//    void display() override;  // Для вызова без параметров
//    void handleInput() override;  // Для вызова без параметров


    void printTopBottomBorder(int size); //  для вывода верхней и нижней границы с буквами
    void printHorizontalDivider(int size); // Функция для вывода горизонтальной линии


    bool isNearShip(int x, int y);
    int getSize();
//    int getShipPoint();
};

#endif
