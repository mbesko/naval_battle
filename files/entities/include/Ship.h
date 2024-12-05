#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include "ShipPoint.h"

// Ориентация корабля
enum class Orientation {
    Horizontal,
    Vertical
};

class Ship {
private:
    int length;                          // Длина корабля
    std::vector<ShipPoint> segments;     // Сегменты корабля
    Orientation orientation;             // Ориентация корабля
    int startX;                          // Начальная координата X
    int startY;                          // Начальная координата Y

public:
    // Конструктор принимает длину и ориентацию корабля
    Ship(int len, Orientation orient);
    Ship(); // Конструктор по умолчанию
    ~Ship();

    // Получить длину корабля
    int getLength() const;

    Ship(const Ship&) = delete;
    Ship& operator=(const Ship&) = delete;

    // Получить ориентацию корабля
    Orientation getOrientation() const;
    void setOrientation(Orientation orient);

    // Получить сегмент корабля по индексу
    ShipPoint& getSegment(int index);

    // Нанести урон сегменту корабля
    void takeDamage(int segmentIndex);

    // Проверка, уничтожен ли корабль
    bool isSunk() const;


    int getStartX() const;
    int getStartY() const;
    void setStartPosition(int x, int y);
};

#endif // SHIP_H
