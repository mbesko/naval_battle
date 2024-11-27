#include "field.h"
#include "exceptions.h" // Подключаем файл с исключениями
#include <iostream>
#include <cstdlib>
#include <ctime>  
#include <memory>
#include <fstream>
#include <sstream>

// Метод для сохранения данных board в текстовый файл
string GameBoard::saveToFile(const string& filename, bool toSave) const {
    // Используем stringstream для накопления данных
    stringstream ss;

    // Сначала сохраняем размеры поля
    ss << width << " " << height << "\n";

    // Сохраняем состояние каждой клетки поля
    for (const auto& row : board) {
        for (const auto& cell : row) {
            ss << static_cast<int>(cell) << " ";  // Преобразуем состояние клетки в целое число
        }
        ss << "\n";  // Переход на новую строку для каждой строки поля
    }

    // Преобразуем stringstream в строку
    string dataToSave = ss.str();
    if (!toSave) {
        return dataToSave;
    }
    // Теперь записываем эту строку в файл
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw runtime_error("Failed to open file for saving.");
    }

    outFile << dataToSave;  // Запись данных в файл
    outFile.close();
    return dataToSave;
}
// Метод для загрузки данных board из текстового файла
void GameBoard::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open() || inFile.peek() == EOF) {
        throw runtime_error("The save file could not be opened.");
    }

    inFile >> width >> height; // Загрузка размеров поля
    board.resize(height, vector<CellStatus>(width, CellStatus::Unknown));
    int cellValue;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            inFile >> cellValue;
            board[y][x] = static_cast<CellStatus>(cellValue); // Восстановление состояния клетки
        }
    }
    inFile.close();
}
// Конструктор игрового поля
GameBoard::GameBoard(int width, int height)
    : width(width), height(height) {
    if (width < 0 || height < 0) {
        throw ObjectCreationException();
    }
    board.resize(height, vector<CellStatus>(width, CellStatus::Unknown));
}

// Конструктор копирования (глубокое копирование)
GameBoard::GameBoard(const GameBoard& other)
    : width(other.width), height(other.height), board(other.board) {}

// Оператор присваивания копированием (глубокое копирование)
GameBoard& GameBoard::operator=(const GameBoard& other) {
    if (this != &other) { // Проверка на самоприсваивание
        width = other.width;
        height = other.height;
        board = other.board;
    }
    return *this;
}

// Конструктор перемещения
GameBoard::GameBoard(const GameBoard& other)
    : width(other.width), height(other.height), board(other.board) {
    board = other.board;
}


// Оператор присваивания перемещением
GameBoard& GameBoard::operator=(GameBoard&& other){
    if (this != &other) { // Проверка на самоприсваивание
        width = other.width;
        height = other.height;
        board = other.board;

        // Очищаем перемещенный объект
        other.width = 0;
        other.height = 0;
    }
    return *this;
}


// Проверка, занята ли клетка или находится рядом с занятыми
bool GameBoard::isOccupiedOrAdjacent(int x, int y) const {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                if (board[ny][nx] == CellStatus::ShipSegmentHealthy || 
                    board[ny][nx] == CellStatus::ShipSegmentDamaged) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Размещение корабля
void GameBoard::placeShip(const Ship& ship, int x, int y, bool isHorizontal) {
    int shipLength = ship.getLength();

    if (isHorizontal) {
        if (x + shipLength - 1 >= width || y >= height || x < 0 || y < 0) {
            throw OutOfBoundsCoordinatesException();
        }
    } else {
        if (y + shipLength - 1 >= height || x >= width || x < 0 || y < 0) {
            throw OutOfBoundsCoordinatesException();
        }
    }

    for (int i = 0; i < shipLength; i++) {
        int checkX = isHorizontal ? x + i : x;
        int checkY = isHorizontal ? y : y + i;

        if (isOccupiedOrAdjacent(checkX, checkY)) {
            throw ShipPlacementException();
        }
    }

    for (int i = 0; i < shipLength; i++) {
        int shipX = isHorizontal ? x + i : x;
        int shipY = isHorizontal ? y : y + i;
        board[shipY][shipX] = CellStatus::ShipSegmentHealthy;  // У сегмента две единицы здоровья
    }
}

// Атака на клетку
void GameBoard::attackCell(int x, int y, bool isBomber) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw OutOfBoundsAttackException();
    }
    if(isBomber) {
        if (board[y][x] == CellStatus::ShipSegmentHealthy) {
            board[y][x] = CellStatus::ShipSegmentDamagedAndNotFound;
        } else if (board[y][x] == CellStatus::ShipSegmentDamagedAndNotFound) {
            board[y][x] = CellStatus::ShipSegmentDestroyedAndNotFound;
        } else if (board[y][x] == CellStatus::ShipSegmentDamaged) {
            board[y][x] = CellStatus::ShipSegmentDestroyed;
        }
    } else if (board[y][x] == CellStatus::ShipSegmentHealthy) {
        board[y][x] = CellStatus::ShipSegmentDamaged;  // Сегмент теряет одну единицу здоровья
    } else if (board[y][x] == CellStatus::ShipSegmentDamaged || board[y][x] == CellStatus::ShipSegmentDamagedAndNotFound || board[y][x] == CellStatus::ShipSegmentDestroyed) {
        board[y][x] = CellStatus::ShipSegmentDestroyed;  // Сегмент уничтожен
    } else if (board[y][x] == CellStatus::Unknown) {
        board[y][x] = CellStatus::Empty;  // Промах
    }
}

// Отрисовка игрового поля
void GameBoard::printBoard(bool isPlayer) {
    string s = "This is enemy`s field\n";
    if (isPlayer) {
        s = "This is your field\n";
    }
    cout << s;
    cout << "  ";
    for(int x = 0; x < width; x++){
        cout << x;
    }
    cout << endl << endl;
    for (int y = 0; y < height; y++) {
        cout << y << " ";
        for (int x = 0; x < width; x++) {
            if (board[y][x] == CellStatus::ShipSegmentHealthy && isPlayer){
                cout << "$";
                continue;
            }
            if (board[y][x] == CellStatus::Unknown || board[y][x] == CellStatus::ShipSegmentHealthy || board[y][x] == CellStatus::ShipSegmentDamagedAndNotFound || board[y][x] == CellStatus::ShipSegmentDestroyedAndNotFound) {
                cout << "?";
            } else if (board[y][x] == CellStatus::ShipSegmentDamaged) {
                cout << "#";
            } else if (board[y][x] == CellStatus::Empty){
                cout << "0";
            } else if (board[y][x] == CellStatus::ShipSegmentDestroyed) {
                cout << "|";
            }
        }
        cout << endl;
    }
}

// Получение статуса клетки
int GameBoard::getCellStatus(int x, int y) {
    if (y >= height || x >= width || x < 0 || y < 0) {
        throw OutOfBoundsCoordinatesException();
    }
    return int(board[y][x]);
}

Ship* GameBoard::createRandomShip(int length, int val) {
    for (int attempt = 0; attempt < 100; ++attempt) {  // Ограничение на количество попыток
        bool isHorizontal = rand() * val % 2;
        int x = (rand() + val) % width;
        int y = (rand() + val) % height;

        try {
            Ship* ship = new Ship(length, isHorizontal, x, y);
            placeShip(*ship, x, y, isHorizontal);
            return ship;  // Если корабль успешно размещён, вернуть его
        } catch (const exception&) {
            // Игнорируем ошибку и пробуем снова
        }
    }

    return nullptr;  // Если не удалось разместить корабль за 100 попыток
}

int GameBoard::getWidth() const{
    return width;
}

int GameBoard::getHeight() const{
    return height;
}

vector<vector<CellStatus>> GameBoard::getBoard() const {
    return board;
}
void GameBoard::rebuild(int nw,int nh,std::vector<std::vector<CellStatus>> nboard) {
    width = nw;
    height = nh;
    board = nboard;
}