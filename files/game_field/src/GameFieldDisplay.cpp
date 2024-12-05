#include "../include/GameFieldDisplay.h"
#include "Console.h"
#include <iostream>

void GameFieldDisplay::displayGameField(Ship* currentShip, int go, bool enemy, bool open, int width, int height, int cursorX, int cursorY, std::vector<std::vector<Cell>> grid) const  {
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
    }
    Console::GoToXY(go, height * 2 + 1);
    printHorizontalDivider(height);
    Console::GoToXY(go, height * 2 + 2);
    printTopBottomBorder(height);
}



void GameFieldDisplay::printTopBottomBorder(int size) const{
    std::cout << "   "; // Отступ для нумерации строк
    for (char c = 'A'; c < 'A' + size; ++c) {
        std::cout << "   " << c << "  "; // Расширение клеток по горизонтали
    }
    std::cout << "\n";
}

// Функция для вывода горизонтальной линии
void GameFieldDisplay::printHorizontalDivider(int size) const{
    std::cout << "  "; // Отступ для нумерации строк
    std::cout << " +-----";
    for (int i = 0; i < size-1; ++i) {
        std::cout << "+-----"; // Расширение клеток по горизонтали
    }
    std::cout << "+\n";
}

void GameFieldDisplay::keyboardLayout(){
    std::cout << R"(

   ╔═══════════╗                            ╔═══════╗                              ╔═══════╗
   ║     ↑     ║                            ║   R   ║ - Использовать способность   ║   N   ║ - Сохранить игру
   ╠═══╦═══╦═══╣                            ╚═══════╝                              ╚═══════╝
   ║ ← ║ ↓ ║ → ║ - Перемещение курсора      ╔═══════╗                              ╔═══════╗
   ╚═══╩═══╩═══╝                            ║   T   ║ - Изменение ориентации       ║   J   ║ - Загрузить игру
   ╔═══════╗                                ╚═══════╝                              ╚═══════╝
   ║ ENTER ║ - Выполнить действие (выстрел, размещение)
   ╚═══════╝
)";

}


// Анимация выстрела по клетке
void GameFieldDisplay::animateShot(int fromX, int fromY, int toX, int toY) {
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
void GameFieldDisplay::animateHit(int x, int y) {
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
