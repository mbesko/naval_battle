#ifndef SHIPPOINT_H
#define SHIPPOINT_H

// Состояние сегмента корабля
enum class ShipSegmentState {
    Intact,    // Целый
    Damaged,   // Поврежден
    Destroyed  // Уничтожен
};

// Класс, представляющий сегмент корабля
class ShipPoint {
private:
    ShipSegmentState state;  // Состояние сегмента

public:
    // Конструктор сегмента (по умолчанию — целый)
    ShipPoint();



    // Получить состояние сегмента
    ShipSegmentState getState() const;
    void setState() ;
    // Нанести урон сегменту
    void takeDamage();

    // Проверка, уничтожен ли сегмент
    bool isDestroyed() const;
};

#endif // SHIPPOINT_H
