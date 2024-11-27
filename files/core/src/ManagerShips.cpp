#include "ManagerShips.h"
#include <iostream>
#include <memory>
#include <map>
#include <fstream>



std::string ManagerShips::saveToFile(const std::string& filename, bool toSave) const {
    std::stringstream ss;

    // Сохраняем количество кораблей
    ss << ships.size() << "\n";

    // Сохраняем информацию о каждом корабле
    for (const auto& shipPtr : ships) {
        if (shipPtr) {
            ss << shipPtr->getLength() << " "
               << (shipPtr->getOrientation() == Orientation::Horizontal ? 1 : 0) << " ";

            // Координаты корабля, если они заданы
            ss << shipPtr->getStartX() << " " << shipPtr->getStartY() << " ";

            // Состояния сегментов
            for (int i = 0; i < shipPtr->getLength(); ++i) {
                ss << static_cast<int>(shipPtr->getSegment(i).getState()) << " ";
            }
            ss << "\n";
        }
    }

    if (!toSave) {
        return ss.str();
    }

    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw std::runtime_error("Failed to open file for saving.");
    }

    outFile << ss.str();
    outFile.close();
    return ss.str();
}


void ManagerShips::loadFromFile(const std::string& filename, GameField& field) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        throw std::runtime_error("Failed to open file for loading.");
    }

    // Читаем количество кораблей
    int numShips;
    inFile >> numShips;

    ships.clear(); // Очищаем текущий список кораблей

    // Читаем информацию о каждом корабле
    for (int i = 0; i < numShips; ++i) {
        int length, orientation, x, y;
        inFile >> length >> orientation >> x >> y;

        if (length <= 0 || (orientation != 0 && orientation != 1)) {
            throw std::runtime_error("Invalid ship data in save file.");
        }

        // Создаём корабль
        auto newShip = std::make_unique<Ship>(
                length, orientation == 1 ? Orientation::Horizontal : Orientation::Vertical);

        // Состояния сегментов
        for (int j = 0; j < length; ++j) {
            int segmentState;
            inFile >> segmentState;

            if (segmentState == static_cast<int>(ShipSegmentState::Damaged)) {
                newShip->takeDamage(j);
            } else if (segmentState == static_cast<int>(ShipSegmentState::Destroyed)) {
                newShip->takeDamage(j);
                newShip->takeDamage(j);
            }
        }

        // Попытка разместить корабль на игровом поле
        if (!field.placeShip(*newShip, x, y)) {
            // Вывод отладочной информации перед выбросом исключения
            std::cerr << "Failed to place ship during loading. Details:\n";
            std::cerr << "  Ship length: " << length << "\n";
            std::cerr << "  Orientation: " << (orientation == 1 ? "Horizontal" : "Vertical") << "\n";
            std::cerr << "  Coordinates: (" << x << ", " << y << ")\n";
            throw std::runtime_error("Failed to place ship on the field during loading.");
        }

        ships.push_back(std::move(newShip)); // Добавляем корабль в менеджер
    }

    inFile.close();
}





ManagerShips::ManagerShips(int oneDeck, int twoDeck, int threeDeck, int fourDeck){
    this->addShips( oneDeck, twoDeck, threeDeck, fourDeck);
}

ManagerShips::~ManagerShips(){}


void ManagerShips::createAndPlaceShip(GameField& field, int length, int x, int y, Orientation orientation) {
    auto newShip = std::make_unique<Ship>(length, orientation);
    if (field.placeShip(*newShip, x, y)) {  // Передаем разыменованный указатель
        ships.push_back(std::move(newShip));  // Перемещаем уникальный указатель в вектор
    }

}
// Проверка, остались ли корабли в живых
bool ManagerShips::anyShipsLeft() const {
    for (const auto& shipPtr : ships) {  // Используйте auto для указателя
        if (shipPtr && !shipPtr->isSunk()) {  // Проверьте, существует ли указатель и не потоплен ли корабль
            return true;
        }
    }
    return false;
}

// Отображение статуса кораблей
void ManagerShips::displayShipsStatus() const {
    for (std::vector<std::unique_ptr<Ship>>::size_type i = 0; i < ships.size(); ++i) {
        std::cout << "Ship " << i + 1 << " is "
                  << (ships[i]->isSunk() ? "sunk" : "alive") << std::endl;  // Разыменуйте указатель
    }
}

// Добавление кораблей с разной палубностью
void ManagerShips::addShips(int oneDeck, int twoDeck, int threeDeck, int fourDeck) {
    for (int i = 0; i < oneDeck; ++i) {
        ships.push_back(std::make_unique<Ship>(1, Orientation::Horizontal));
    }
    for (int i = 0; i < twoDeck; ++i) {
        ships.push_back(std::make_unique<Ship>(2, Orientation::Horizontal));
    }
    for (int i = 0; i < threeDeck; ++i) {
        ships.push_back(std::make_unique<Ship>(3, Orientation::Horizontal));
    }
    for (int i = 0; i < fourDeck; ++i) {
        ships.push_back(std::make_unique<Ship>(4, Orientation::Horizontal));
    }
}

// Возвращение всех кораблей
std::vector<std::unique_ptr<Ship>>& ManagerShips::getShips() {
    return ships;
}

const std::vector<std::unique_ptr<Ship>>& ManagerShips::getShips() const {
    return ships;
}


void ManagerShips::displayAliveShipsBySize(int x, int y) const {
    // Создаем карту для подсчета живых кораблей по размеру (от 1 до 4 палуб)
    std::map<int, int> aliveShipsBySize = {{1, 0}, {2, 0}, {3, 0}, {4, 0}};

    // Подсчёт кораблей
    for (const auto& shipPtr : ships) {
        if (shipPtr && !shipPtr->isSunk()) {
            int size = shipPtr->getLength();
            aliveShipsBySize[size]++;
        }
    }

    // Выводим верхнюю рамку
    Console::GoToXY(x, y);
    std::cout << "╔════════════════════╗";
    Console::GoToXY(x, ++y);
    std::cout << "║   Живые корабли    ║";
    Console::GoToXY(x, ++y);
    std::cout << "╠════════════════════╣";

    // Выводим информацию о кораблях
    for (const auto& [size, count] : aliveShipsBySize) {
        Console::GoToXY(x, ++y);
        std::cout << "║ ";

        // Отрисовка графики корабля
        for (int j = 0; j < size; ++j) {
            std::cout << "■";
        }

        // Дополнение текста: количество кораблей
        std::cout << " - " << count << " шт.";

        // Рассчитываем количество пробелов для выравнивания строки
        int totalWidth = 20; // Ширина строки в рамках
        int usedWidth = size + 6 + std::to_string(count).size(); // Занятое место: корабли, текст и пробелы
        for (int j = 0; j < totalWidth - usedWidth - 2; ++j) { // Учитываем рамки ║
            std::cout << " ";
        }
        std::cout << "║"; // Завершаем строку
    }

    // Закрывающая рамка
    Console::GoToXY(x, ++y);
    std::cout << "╚════════════════════╝";
}




int ManagerShips::countAliveShips() const {
    int aliveCount = 0;
    for (const auto& shipPtr : ships) {
        if (shipPtr && !shipPtr->isSunk()) {
            aliveCount++;
        }
    }
    return aliveCount;
}