
#include "ShipPoint.h"
#include <iostream>

// Конструктор сегмента (по умолчанию — целый)
ShipPoint::ShipPoint() : state(ShipSegmentState::Intact) {
   // std::cout << "ShipPoint created with default state: Intact" << std::endl;
}

//ShipPoint::ShipPoint(const ShipPoint& other) {
//    state = other.state;
//    std::cout << "ShipPoint copied" << std::endl;
//}

// Получить состояние сегмента
void ShipPoint::setState()  {
    state = ShipSegmentState::Intact;
}

ShipSegmentState ShipPoint::getState() const {
    return state;
}
// Нанести урон сегменту
void ShipPoint::takeDamage() {
    if (state == ShipSegmentState::Intact) {
        state = ShipSegmentState::Damaged;
    } else if (state == ShipSegmentState::Damaged) {
        state = ShipSegmentState::Destroyed;
    }
}
// Проверка, уничтожен ли сегмент
bool ShipPoint::isDestroyed() const {
    return state == ShipSegmentState::Destroyed;
}