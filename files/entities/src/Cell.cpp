#include "Cell.h"
#include "ShipPoint.h"
#include <iostream>

// Конструктор по умолчанию: клетка неизвестна и пуста
Cell::Cell() : state(CellState::Empty), shipSegment(nullptr) {}

// Получить текущее состояние клетки
CellState Cell::getState() const {
    return state;
}

// Установить состояние клетки
void Cell::setState(CellState newState) {
    state = newState;
}
// Установить сегмент корабля в клетке
void Cell::setShipPart(ShipPoint* segment) {
    shipSegment = segment;
    if (segment) {
        state = CellState::ShipPart;  // Если сегмент корабля установлен, меняем состояние
    }
    if (segment == nullptr) {
        std::cerr << "Error: nullptr segment!" << std::endl;
    }

}

void Cell::attack() {
    if (shipSegment != nullptr) {
        state = CellState::ShipPart;
        shipSegment->takeDamage();
    }
}

ShipPoint* Cell::getShipPart() const {
    return shipSegment;
}

bool Cell::isEmpty() const {
    return state == CellState::Empty;
}
