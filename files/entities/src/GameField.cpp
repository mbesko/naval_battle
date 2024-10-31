// GameField.cpp
#include "GameField.h"
#include <iostream>
#include "Console.h"
#include "KeyCodes.h"
#include <conio.h>
#include <windows.h>


// Реализация чисто виртуального метода display
//void GameField::display() {
//    // Логика отображения игрового поля
//    std::cout << "Отображение игрового поля" << std::endl;
//}
//
//// Реализация чисто виртуального метода handleInput
//void GameField::handleInput() {
//    // Логика обработки ввода
//    std::cout << "Обработка ввода" << std::endl;
//}

// Конструктор, инициализирующий поле заданного размера и курсор
GameField::GameField(int size)
:  width(size), height(size), grid(size, std::vector<Cell>(size)), cursorX(0), cursorY(0){}

// Отображение поля с возможным выделением места для размещения корабля
void GameField::display(Ship* currentShip, int go, bool enemy, bool open) {
//    //Console::clear();  // Очищаем экран перед отрисовкой
    if (!enemy) Console::GoToXY(go, 0);
    printTopBottomBorder(height);
    for (int i = 0; i < height; ++i) {
        Console::GoToXY(go, i * 2 + 1);
        printHorizontalDivider(height);
        Console::GoToXY(go, i * 2 + 2);
        std::cout << std::setw(2) << i + 1 << "-";
        for (int j = 0; j < width; ++j) {
            bool isCursorArea = false;
            Console::setTextAttribute(7);
            std::cout << "|  ";
            // Если корабль передаётся в метод display, выделяем клетки под корабль для размещения
            if (currentShip != nullptr) {
                int shipLength = currentShip->getLength();
                Orientation shipOrientation = currentShip->getOrientation();

                // Горизонтальная ориентация
                if (shipOrientation == Orientation::Horizontal) {
                    if (i == cursorY && j >= cursorX && j < cursorX + shipLength && cursorX + shipLength <= width) {
                        isCursorArea = true;
                    }
                }
                    // Вертикальная ориентация
                else if (shipOrientation == Orientation::Vertical) {
                    if (j == cursorX && i >= cursorY && i < cursorY + shipLength && cursorY + shipLength <= height) {
                        isCursorArea = true;
                    }
                }
            }
            else if (i == cursorY && j == cursorX && currentShip == nullptr) {
                isCursorArea = true;
            }
            // Если курсор находится в этой области, выделяем её
            if (isCursorArea and enemy) {
                Console::setTextAttribute(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }

            // Отображаем состояние клетки
            CellState state = grid[i][j].getState();
            ShipPoint* shipPart = grid[i][j].getShipPart();
            if (state == CellState::Unknown and !open) {
                std::cout << "•";
            } else if (state == CellState::Empty || open and !shipPart) {
                std::cout << "~";
            } else if (state == CellState::ShipPart || open) {
                if (shipPart) {
                    ShipSegmentState segmentState = shipPart->getState();
                    if (segmentState == ShipSegmentState::Intact) {
                        std::cout << "#";
                    } else if (segmentState == ShipSegmentState::Damaged) {
                        std::cout << "*";
                    } else if (segmentState == ShipSegmentState::Destroyed) {
                        std::cout << "+";
                    }
                }
            }
            std::cout  << "  ";

            if (isCursorArea) {
                Console::setTextAttribute(7);
            }
        }
        std::cout << "|";
        //std::cout << std::endl;
    }
    Console::GoToXY(go, height * 2 + 1);
    printHorizontalDivider(height);
    Console::GoToXY(go, height * 2 + 2);
    printTopBottomBorder(height);
}

// Анимация выстрела по клетке
void GameField::animateShot(int fromX, int fromY, int toX, int toY) {
    int dx = (toX > fromX) ? 1 : -1;  // Направление движения по X
    int dy = (toY > fromY) ? 1 : -1;  // Направление движения по Y

    int currentX = fromX;
    int currentY = fromY;
    //PlaySound(TEXT("sounds/attack2.wav"), NULL, SND_FILENAME | SND_ASYNC);
    while (currentX != toX || currentY != toY) {

        Console::GoToXY(currentX, currentY);
        std::cout << " ";


        if (currentX != toX) currentX += dx;
        if (currentY != toY) currentY += dy;


        Console::GoToXY(currentX, currentY);
        std::cout << "*";

        Sleep(30);
    }


    Console::GoToXY(currentX, currentY);
    std::cout << " ";
}

// Анимация попадания в корабль
void GameField::animateHit(int x, int y) {
    for (int i = 0; i < 5; ++i) {  // Цикл для мигания
        Console::GoToXY(x, y);
        Console::setTextAttribute(FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cout << "*";

        Sleep(100);

        Console::GoToXY(x, y);
        Console::setTextAttribute(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        std::cout << " ";

        Sleep(100);
    }
}

void GameField::handleInput(bool& actionConfirmed, Ship* currentShip) {
    char ch = _getch();
    switch (ch) {
        case UP: // Перемещение курсора вверх
            if (cursorY > 0) cursorY--;
            break;
        case DOWN: // Перемещение курсора вниз
            if (cursorY < height - 1) cursorY++;
            break;
        case LEFT: // Перемещение курсора влево
            if (cursorX > 0) cursorX--;
            break;
        case RIGHT:  // Перемещение курсора вправо
            if (cursorX < width - 1) cursorX++;
            break;
        case 'T':
        case 't':  // Изменение ориентации корабля во время размещения
            if (currentShip != nullptr) {
                if (currentShip->getOrientation() == Orientation::Horizontal) {
                    currentShip->setOrientation(Orientation::Vertical);
                } else {
                    currentShip->setOrientation(Orientation::Horizontal);
                }
            }
            break;
        case ENTER:  // Подтверждение действия (размещение корабля или выстрел)
            if (currentShip != nullptr) {
                // Попытка разместить корабль на текущей позиции
                if (!placeShip(*currentShip, cursorX, cursorY)) {
                    std::cout << "Невозможно разместить корабль. Попробуйте другую позицию." << std::endl;
                    PlaySound(TEXT("sounds/errorplace.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    Sleep(1000);
                } else {
                    actionConfirmed = false;  // Корабль успешно размещён
                }
            } else {
                // Выполняем выстрел по текущей клетке
                attack(cursorX, cursorY);
                actionConfirmed = true;  // Выстрел произведён
            }
            break;
        default:
            break;
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
void GameField::attack(int x, int y) {

    //int start = 10;
    //int end = 20;
    int startX = rand() % (width + 20) + width * 6+10;
    int startY = rand() % ((height+1) - 2 + 1) + 2;

    //int startX = 6;  // Можете изменить, чтобы старт был из определённой точки (например, с корабля)
    //int startY = 2;

    // Анимация движения снаряда от точки старта до точки цели
    //PlaySound(TEXT("sounds/attack2.wav"), NULL, SND_FILENAME | SND_ASYNC);
    PlaySound(TEXT("sounds/attackeee.wav"), NULL, SND_FILENAME | SND_ASYNC);

    animateShot(startX, startY, (x+1)*6, (y+1)*2);
    //PlaySound(TEXT("sounds/bomb.wav"), NULL, SND_FILENAME | SND_ASYNC);

    // После анимации выполняем выстрел
    if (grid[y][x].getState() == CellState::ShipPart || grid[y][x].getShipPart() != nullptr) {
        grid[y][x].attack();  // Атакуем часть корабля
        std::cout << "Попадание!" << std::endl;
        PlaySound(TEXT("sounds/attack.wav"), NULL, SND_FILENAME | SND_ASYNC);

        animateHit((x+1)*6, (y+1)*2);  // Анимация попадания
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


void GameField::printTopBottomBorder(int size) {
    std::cout << "   "; // Отступ для нумерации строк
    for (char c = 'A'; c < 'A' + size; ++c) {
        std::cout << "   " << c << "  "; // Расширение клеток по горизонтали
    }
    std::cout << "\n";
}

// Функция для вывода горизонтальной линии
void GameField::printHorizontalDivider(int size) {
    std::cout << "  "; // Отступ для нумерации строк
    std::cout << " +-----";
    for (int i = 0; i < size-1; ++i) {
        std::cout << "+-----"; // Расширение клеток по горизонтали
    }
    std::cout << "+\n";
}

void GameField::setZeroCursor(){
    cursorX = 0;
    cursorY = 0;
}

int GameField::getSize(){
    return width;
}

//int GameField::getShipPoint(int){
//    for (int i = 0; i < height; ++i) {
//        for (int j = 0; j < width; ++j){
//                CellState state = grid[i][j].getState();
//                ShipPoint* shipPart = grid[i][j].getShipPart();
//                if(state == CellState::ShipPart && shipPart->getState() != ShipSegmentState::Destroyed)
//
//        }
//
//    }
//
//};



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
