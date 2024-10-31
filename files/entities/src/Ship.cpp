#include "Ship.h"
#include <stdexcept>


Ship::Ship(int len, Orientation orient)
        : length(len), segments(len), orientation(orient) {

}

Ship::Ship() : length(0), orientation(Orientation::Horizontal) {}


Ship::~Ship() {}

//// Конструктор перемещения
//Ship::Ship(Ship&& other) noexcept
//        : length(other.length), segments(std::move(other.segments)), orientation(other.orientation) {
//    other.length = 0;
//}
//
//// Оператор присваивания перемещения
//Ship& Ship::operator=(Ship&& other) noexcept {
//    if (this != &other) {
//        length = other.length;
//        segments = std::move(other.segments);
//        orientation = other.orientation;
//        other.length = 0;
//    }
//    return *this;
//}

int Ship::getLength() const {
    return length;
}

Orientation Ship::getOrientation() const {
    return orientation;
}

void Ship::setOrientation(Orientation orient) {
    orientation = orient;
}

ShipPoint& Ship::getSegment(int index) {
    if (index >= 0 && index < length) {
        return segments.at(index);  // Безопасный доступ через at()
    }
    throw std::out_of_range("Invalid segment index");
}

void Ship::takeDamage(int segmentIndex) {
    if (segmentIndex >= 0 && segmentIndex < length) {
        segments[segmentIndex].takeDamage();
    }
}

bool Ship::isSunk() const {
    for (const ShipPoint& segment : segments) {
        if (!segment.isDestroyed()) {
            return false;
        }
    }
    return true;
}
