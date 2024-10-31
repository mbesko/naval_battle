#ifndef CELL_H
#define CELL_H

#include "ShipPoint.h"

// Возможные состояния клетки
enum class CellState {
    Unknown,  // Клетка неизвестна (например, изначально или для вражеского поля)
    Empty,    // Клетка пустая
    ShipPart  // В клетке есть часть корабля
};

// Класс, представляющий клетку на игровом поле
class Cell {
private:
    CellState state;          // Текущее состояние клетки
    ShipPoint* shipSegment;   // Указатель на сегмент корабля (если есть)

public:
    // Конструктор по умолчанию
    Cell();

    // Получить текущее состояние клетки
    CellState getState() const;

    // Установить состояние клетки
    void setState(CellState newState);


    // Установить сегмент корабля в клетке
    void setShipPart(ShipPoint* segment);

    void attack();  // Атаковать клетку

    // Получить сегмент корабля
    ShipPoint* getShipPart() const;

    // Проверить, пустая ли клетка
    bool isEmpty() const;
};

#endif // CELL_H
