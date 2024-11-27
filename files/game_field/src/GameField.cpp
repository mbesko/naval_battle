// GameField.cpp

#include "Player.h"
#include "../include/GameField.h"
#include <iostream>
#include "../../core/include/Console.h"
#include "../../core/include/KeyCodes.h"
#include <conio.h>
#include <windows.h>
#include "GameExceptions.h"
#include <fstream>
#include "GameSave.h"











std::string GameField::saveToFile(const std::string& filename, bool toSave, const ManagerShips& manager) const {
    std::stringstream ss;

    // Сохраняем размеры поля
    ss << width << " " << height << "\n";

    // Сохраняем состояние каждой клетки
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const Cell& cell = grid[y][x];
            if (cell.getState() == CellState::ShipPart && cell.getShipPart()) {
                bool found = false;
                for (size_t shipIndex = 0; shipIndex < manager.getShips().size() && !found; ++shipIndex) {
                    const auto& ship = manager.getShips()[shipIndex];
                    for (int segmentIndex = 0; segmentIndex < ship->getLength(); ++segmentIndex) {
                        if (&ship->getSegment(segmentIndex) == cell.getShipPart()) {
                            ss << "S " << shipIndex << " " << segmentIndex << " ";
                            found = true;
                            break; // Выход из внутреннего цикла
                        }
                    }
                }
            } else if (cell.getState() == CellState::Empty) {
                ss << "E ";
            } else {
                ss << "U ";
            }
        }
        ss << "\n";
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


void GameField::loadFromFile(const std::string& filename, ManagerShips& manager) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        throw std::runtime_error("The save file could not be opened.");
    }

    // Загружаем размеры поля
    inFile >> width >> height;
    grid.resize(height, std::vector<Cell>(width));

    // Загружаем состояние каждой клетки
    std::string cellState;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            inFile >> cellState;
            if (cellState == "S") {
                int shipIndex, segmentIndex;
                inFile >> shipIndex >> segmentIndex;

                // Проверяем корректность индексов
                if (shipIndex < 0 || shipIndex >= static_cast<int>(manager.getShips().size())) {
                    throw std::runtime_error("Invalid ship index in save file.");
                }
                auto& ship = manager.getShips()[shipIndex];
                if (segmentIndex < 0 || segmentIndex >= ship->getLength()) {
                    throw std::runtime_error("Invalid segment index in save file.");
                }

                // Устанавливаем связь с сегментом корабля
                grid[y][x].setShipPart(&ship->getSegment(segmentIndex));
                grid[y][x].setState(CellState::ShipPart);
            } else if (cellState == "E") {
                grid[y][x].setState(CellState::Empty);
            } else {
                grid[y][x].setState(CellState::Unknown);
            }
        }
    }

    inFile.close();
}


















// Реализация чисто виртуального метода display
void GameField::display() {
    // Логика отображения игрового поля
    std::cout << "Отображение игрового поля" << std::endl;
}

//// Реализация чисто виртуального метода handleInput
void GameField::handleInput() {
    // Логика обработки ввода
    std::cout << "Обработка ввода" << std::endl;
}

// Конструктор, инициализирующий поле заданного размера и курсор
GameField::GameField(int size)
:  width(size), height(size), grid(size, std::vector<Cell>(size)), cursorX(0), cursorY(0){}


void GameField::display(Ship* currentShip, int go, bool enemy, bool open) {
    gameFieldDisplay.displayGameField(currentShip, go, enemy, open, width, height, cursorX, cursorY, grid);
}

void GameField::handleInput(bool& actionConfirmed, Ship* currentShip, Player& player, Player& opponent) {
    int selectedGameField = input.handleGameFieldInput(cursorX, cursorY, height, width);
    executeAction(actionConfirmed, selectedGameField, currentShip, player, opponent);
}

void GameField::executeAction(bool& actionConfirmed, int selectedGameField, Ship* currentShip, Player& player, Player& opponent){
    try{
    switch (selectedGameField) {
        case 2:
            break;
        case 10:
            if (currentShip != nullptr) {
                if (currentShip->getOrientation() == Orientation::Horizontal) {
                    currentShip->setOrientation(Orientation::Vertical);
                } else {
                    currentShip->setOrientation(Orientation::Horizontal);
                }
            }
            break;
        case 20:
            if (ability == nullptr  and currentShip == nullptr and player.getAbilityManager().hasAbilities()) {
                // Получаем способность из AbilityManager
                ability = player.getAbilityManager().getRandomAbility();
                if (ability) {
                    std::cout << "Вы выбрали способность: " << ability->getName() << std::endl;
                    Sleep(1000);
                } else {
                    throw AbilityAcquisitionException();
                }
            } else if (currentShip == nullptr){
                throw AbilityNotAvailableException();
            }
            break;
        case 30:
            if (currentShip == nullptr) {
                gameSave.save(player, opponent);
            }
            break;
        case 40:
            if (currentShip == nullptr) {
                gameSave.load(player, opponent);
            }
            break;
        case 1:
            if (ability){
                ability->use(opponent.getManagerShips(), *this, cursorX, cursorY);
                Sleep(1000);
                actionConfirmed = true;
                ability = nullptr;
            }
            else if (currentShip != nullptr) {
                // Попытка разместить корабль на текущей позиции
                if (!placeShip(*currentShip, cursorX, cursorY)) {
                    throw ShipPlacementException();
                    PlaySound(TEXT("sounds/errorplace.wav"), NULL, SND_FILENAME | SND_ASYNC);
                } else {
                    actionConfirmed = false;  // Корабль успешно размещён
                }
            } else {
                // Выполняем выстрел по текущей клетке
                attack(cursorX, cursorY);
                actionConfirmed = true;  // Выстрел произведён
            }
            break;

    }
    }
    catch (const GameException& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            Sleep(1000);
        }
}


// Проверка, находится ли какая-либо часть корабля в соседних клетках
bool GameField::isNearShip(int x, int y) {
    // Определяем диапазон соседних клеток
    int startX = std::max(0, x - 1);
    int endX = std::min(width - 1, x + 1);
    int startY = std::max(0, y - 1);
    int endY = std::min(height - 1, y + 1);

    // Проверяем все клетки вокруг (и саму клетку)
    for (int i = startY; i <= endY; ++i) {
        for (int j = startX; j <= endX; ++j) {
            if (!grid[i][j].isEmpty()) {
                return true;  // Если хоть одна клетка не пуста, корабль нельзя разместить
            }
        }
    }

    return false;  // Все соседние клетки пусты
}

// Разсещение корабля на поле
bool GameField::placeShip(Ship& ship, int x, int y) {
    int len = ship.getLength();
    Orientation orientation = ship.getOrientation();

    // Проверка на выход за границы поля
    if (orientation == Orientation::Horizontal) {
        if (x + len > width) return false;
        // Проверка клеток под корабль и вокруг них
        for (int i = 0; i < len; ++i) {
            if (!grid[y][x + i].isEmpty() || isNearShip(x + i, y)) {
                return false;  // Клетка занята или рядом есть другой корабль
            }
        }
        // Устанавливаем сегменты корабля
        for (int i = 0; i < len; ++i) {
            grid[y][x + i].setShipPart(&ship.getSegment(i));
        }
    } else {  // Вертикальная ориентация
        if (y + len > height) return false;
        // Проверка клеток под корабль и вокруг них
        for (int i = 0; i < len; ++i) {
            if (!grid[y + i][x].isEmpty() || isNearShip(x, y + i)) {
                return false;  // Клетка занята или рядом есть другой корабль
            }
        }
        // Устанавливаем сегменты корабля
        for (int i = 0; i < len; ++i) {
            grid[y + i][x].setShipPart(&ship.getSegment(i));
        }
    }

    ship.setStartPosition(x,y);
    return true;  // Корабль успешно размещен
}

void GameField::setStateUnknown(){
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            grid[i][j].setState(CellState::Unknown);
        }
    }
}
// Выстрел по клетке
void GameField::attack(int x, int y, bool enemy) {

    int startX = rand() % (width + 20) + width * 6+10;
    int startY = rand() % ((height+1) - 2 + 1) + 2;

    // Анимация движения снаряда от точки старта до точки цели
    PlaySound(TEXT("sounds/attackeee.wav"), NULL, SND_FILENAME | SND_ASYNC);

    if (!enemy){
        gameFieldDisplay.animateShot(startX, startY, (x+1)*6, (y+1)*2);}
    else gameFieldDisplay.animateShot((x+1)*6, (y+1)*2, (x+1)*6+17, (y+1)*2);
    //PlaySound(TEXT("sounds/bomb.wav"), NULL, SND_FILENAME | SND_ASYNC);

    // После анимации выполняем выстрел
    if (grid[y][x].getState() == CellState::ShipPart || grid[y][x].getShipPart() != nullptr) {
        grid[y][x].attack();  // Атакуем часть корабля
        std::cout << "Попадание!" << std::endl;
        PlaySound(TEXT("sounds/attack.wav"), NULL, SND_FILENAME | SND_ASYNC);

        if (!enemy){
        gameFieldDisplay.animateHit((x+1)*6, (y+1)*2); }
        else gameFieldDisplay.animateHit((x+1)*6+17, (y+1)*2);

        Console::setTextAttribute(7);
        if(grid[y][x].getState() == CellState::Unknown){
            grid[y][x].setState(CellState::ShipPart);
        }
    } else{
        grid[y][x].setState(CellState::Empty);  // Промах
        std::cout << "Мимо!" << std::endl;
        PlaySound(TEXT("sounds/water.wav"), NULL, SND_FILENAME | SND_ASYNC);
        Sleep(1000);
    }
}
// Проверка, потоплены ли все корабли на поле
bool GameField::areAllShipsSunk() const {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell.getState() == CellState::ShipPart || cell.getShipPart() != nullptr) {
                ShipPoint* segment = cell.getShipPart();
                if (segment && !segment->isDestroyed()) {
                    return false;
                }
            }
        }
    }
    return true;
}

void GameField::setZeroCursor(){
    cursorX = 0;
    cursorY = 0;
}

int GameField::getSize(){
    return width;
}

Cell& GameField::getCell(int x, int y) {
    return grid[y][x];  // Возвращаем ячейку из двумерного массива
}

void GameField::clean(){
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j){
            grid[i][j].cleanShipPart();
            grid[i][j].setState(CellState::Empty);
//            ShipPoint* segment = grid[i][j].getShipPart();
//            segment->setState();
        }
    }
}

GameField::GameField(const GameField& other)
        : width(other.width), height(other.height), grid(other.grid), cursorX(other.cursorX), cursorY(other.cursorY) {

}
GameField::GameField(GameField&& other) noexcept
: width(other.width), height(other.height), grid(std::move(other.grid)), cursorX(other.cursorX), cursorY(other.cursorY) {


other.width = 0;
other.height = 0;
other.cursorX = 0;
other.cursorY = 0;
}


GameField& GameField::operator=(const GameField& other) {
    if (this == &other) {
        return *this;  // Защита от самоприсваивания
    }

    width = other.width;
    height = other.height;
    grid = other.grid;
    cursorX = other.cursorX;
    cursorY = other.cursorY;


    return *this;
}

GameField& GameField::operator=(GameField&& other) noexcept {
if (this == &other) {
return *this;  // Защита от самоприсваивания
}

width = other.width;
height = other.height;
grid = std::move(other.grid);
cursorX = other.cursorX;
cursorY = other.cursorY;



other.width = 0;
other.height = 0;
other.cursorX = 0;
other.cursorY = 0;

return *this;
}

//GameField::~GameField() {
//}
