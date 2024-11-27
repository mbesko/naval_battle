#include "manager.h"
#include "exceptions.h" // Подключаем файл с исключениями
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <fstream>
using namespace std;

ShipManager::ShipManager(int numShips, vector<Ship> usedShips)
        : ships(numShips) { // Перемещаем временный объект в ships
        if (numShips != ships.size()) {
            throw ObjectCreationException(); 
        }
        for (int i = 0; i < numShips; i++) {
            ships[i] = usedShips[i];
        }
}

string ShipManager::saveToFile(const string& filename, bool toSave) const {
    // Создаем строковый поток для накопления данных
    stringstream ss;

    // Записываем количество кораблей
    ss << ships.size() << endl;

    // Записываем информацию о каждом корабле
    for (const auto& ship : ships) {
        ss << ship.getLength() << " "  // Длина
           << (ship.isHorizontalOrientation() ? 1 : 0) << " "  // Ориентация (1 - горизонтальная, 0 - вертикальная)
           << ship.getX() << " "  // Координаты начала
           << ship.getY() << " ";

        // Записываем состояние сегментов
        for (int i = 0; i < ship.getLength(); ++i) {
            ss << static_cast<int>(ship.getSegmentState(i)) << " ";  // Состояние сегмента
        }
        ss << endl;
    }

    // Открываем файл для записи
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw runtime_error("Failed to open file for saving.");
    }
    if (!toSave) {
        return ss.str(); 
    }
    // Записываем все данные из stringstream в файл
    outFile << ss.str();
    outFile.close();  // Закрываем файл
    return ss.str();
}
void ShipManager::loadFromFile(const string& filename) {
    // Открываем файл для чтения
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        throw runtime_error("Failed to open file for loading.");
    }

    // Читаем количество кораблей
    int numShips;
    inFile >> numShips;
    inFile.ignore();  // Игнорируем символ новой строки

    ships.clear();  // Очищаем текущий список кораблей

    // Читаем информацию о каждом корабле
    for (int i = 0; i < numShips; ++i) {
        int length, isHorizontal, x, y;
        inFile >> length >> isHorizontal >> x >> y;

        // Создаем новый корабль
        auto ship = Ship(length, isHorizontal == 1, x, y);

        // Читаем состояние сегментов корабля
        for (int j = 0; j < length; ++j) {
            int segmentState;
            inFile >> segmentState;
            ship.takeDamage(j);  // Наносим урон, восстанавливая состояние сегмента
        }

        // Добавляем корабль в менеджер
        ships.push_back(ship);

        inFile.ignore();  // Игнорируем символ новой строки
    }

    inFile.close();  // Закрываем файл
}
int ShipManager::getNumAliveShips() {
    int k = 0;
    for (int i = 0; i < ships.size(); ++i) {
        bool isDead = true;
        for (int j = 0; j < ships[i].getLength(); j++) {
            SegmentState status = ships[i].getSegmentState(j);
            if (status == SegmentState::Intact || status == SegmentState::Damaged) {
                isDead = false;
                break;  // Если сегмент неповрежден, можно выйти из внутреннего цикла
            }
        }
        if (isDead) {
            ships.erase(ships.begin() + i);
            --i;  // Уменьшаем индекс, чтобы учесть сдвиг элементов
        } else {
            ++k;  // Считаем корабль живым
        }
    }
    return k;
}



int ShipManager::getShipInd(int x, int y) const {
    for (int i = 0; i < ships.size(); i++) {
        int shipX = ships[i].getX();
        int shipY = ships[i].getY();
        int len = ships[i].getLength();
        bool isHorizontal = ships[i].isHorizontalOrientation();

        // Проверка вертикальной ориентации
        if (!isHorizontal && shipX == x && y >= shipY && y <= shipY + len - 1) {
            return i;
        }
        // Проверка горизонтальной ориентации
        else if (isHorizontal && shipY == y && x >= shipX && x <= shipX + len - 1) {
            return i;
        }
    }
    return -1;  // Корабль не найден
}

void ShipManager::takeDamageByIndex(int indOfShip, int x, int y) {
    int segmentIndex = ships[indOfShip].getSegmentIndex(x, y);
    ships[indOfShip].takeDamage(segmentIndex);
}

Ship ShipManager::getShipByIndex(int ind) {
    return ships[ind];  // Возвращаем обычный указатель на объект
}

void ShipManager::printAllShipsCoordinates() {
    for(int i = 0; i < ships.size(); i++) {
        cout << "Ship " << i + 1 << " coordinates: (x, y) " << ships[i].getX() << " " << ships[i].getY() << endl;
        cout << "Ship " << i + 1 << " is horizontal: " << ships[i].isHorizontalOrientation() << endl;
    }
}