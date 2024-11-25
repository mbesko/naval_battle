#include "Player.h"
#include <iostream>
#include <windows.h>



Player::Player(const std::string& name, int fieldSize, int oneDeck, int twoDeck, int threeDeck, int fourDeck) : name(name), field(fieldSize), managerShips(oneDeck, twoDeck, threeDeck, fourDeck){}

// Инициализация кораблей с заданным количеством палуб
void Player::initShips(int oneDeck, int twoDeck, int threeDeck, int fourDeck) {
    managerShips.addShips(oneDeck, twoDeck, threeDeck, fourDeck);
}

void Player::cleanField() {
    // 1. Очистить игровое поле
    field.clean();

    // 2. Сбросить состояние всех кораблей
    for (auto& ship : managerShips.getShips()) {
        if (ship) { // Проверяем, что указатель валиден
            int length = ship->getLength();
            for (int i = 0; i < length; ++i) {
                ShipPoint& segment = ship->getSegment(i);
                segment.setState(); // Вызываем метод без аргументов
            }
        }
    }
}

// Размещение кораблей игроком
void Player::placeShips() {
    for (auto& ship : managerShips.getShips()) {
        bool isPlacingShip = true;  // Пока корабль не размещён, игрок выбирает позицию

        while (isPlacingShip) {
            Console::clear();
            field.display(ship.get());  // Отображаем поле и область размещения корабля
            field.handleInput(isPlacingShip, ship.get(), *this, *this);  // Обработка перемещения и размещения

            if (!isPlacingShip) {
                std::cout << "Корабль успешно размещен!" << std::endl;
                PlaySound(TEXT("sounds/shipplacement.wav"), NULL, SND_FILENAME | SND_ASYNC);

            }
        }
    }
    field.setStateUnknown();
    field.setZeroCursor();
}


void Player::placeShipsRandomly() {
    // Инициализация генератора случайных чисел
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (auto& ship : managerShips.getShips()) {
        bool placed = false;
        while (!placed) {
            // Генерация случайных координат и ориентации
            int x = std::rand() % field.getSize();
            int y = std::rand() % field.getSize();
            Orientation orientation = (std::rand() % 2 == 0)
                                      ? Orientation::Horizontal
                                      : Orientation::Vertical;
            ship->setOrientation(orientation);

            // Пытаемся разместить корабль на поле
            if (field.placeShip(*ship, x, y)) {
                placed = true; // Корабль успешно размещён
            }
        }
    }
    //field.setStateUnknown();
    field.setZeroCursor();
}

// Ход игрока: выбор цели и выполнение выстрела
bool Player::takeTurn(Player& opponent, Player& currentPlayer) {
    bool shotMade = false;  // Пока выстрел не сделан
    int fieldSize = field.getSize();
    while (!shotMade) {
        int countShip = opponent.managerShips.countAliveShips();
        Console::clear();
        Console::GoToXY(0, 0);
        opponent.getField().display(nullptr);  // Отображаем поле противника
        opponent.managerShips.displayAliveShipsBySize(0, fieldSize*2+5);

        currentPlayer.getField().display(nullptr,field.getSize() * 6+5, false, true);
        currentPlayer.managerShips.displayAliveShipsBySize(fieldSize * 6+10, fieldSize*2+5);
        opponent.getField().handleInput(shotMade, nullptr, *this, opponent);  // Обрабатываем выбор цели и выстрел

        if (countShip - opponent.managerShips.countAliveShips() != 0){
            currentPlayer.abilityManager.addRandomAbility();
        }

      if (shotMade) {
          opponent.getField().display(nullptr);  // Отображаем поле противника
          opponent.managerShips.displayAliveShipsBySize(0, fieldSize*2+5);

          currentPlayer.getField().display(nullptr,field.getSize() * 6+5, false, true);
          currentPlayer.managerShips.displayAliveShipsBySize(fieldSize * 6+10, fieldSize*2+5);
          Sleep(1000);

          }


    }
    return true;
}

void Player::randomAttack(Player& opponent) {
    // Инициализация генератора случайных чисел (если не была сделана ранее)
    static bool randomSeedInitialized = false;
    if (!randomSeedInitialized) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        randomSeedInitialized = true;
    }

    int fieldSize = opponent.getField().getSize();
    bool attackSuccessful = false;

    while (!attackSuccessful) {
        // Генерация случайных координат
        int x = std::rand() % fieldSize;
        int y = std::rand() % fieldSize;

        // Проверяем состояние клетки перед атакой
        Cell& cell = opponent.getField().getCell(x, y);
        CellState cellState = cell.getState();

        if (cellState == CellState::Unknown) {
            // Если клетка ещё неизвестна, выполняем атаку
            opponent.getField().attack(x, y, true);
            attackSuccessful = true; // Выстрел успешно произведён
        } else if (cellState == CellState::ShipPart){
            ShipPoint* shipPart = cell.getShipPart();
            if(shipPart != nullptr && shipPart->getState() == ShipSegmentState::Damaged){
                opponent.getField().attack(x, y, true);
                attackSuccessful = true; // Выстрел успешно произведён
            }}
    }
}

GameField& Player::getField() {
    return field;
}



AbilityManager& Player::getAbilityManager() {
    return abilityManager;
}


std::string Player::getName() const {
    return name;
}

ManagerShips& Player::getManagerShips() {
    return managerShips;
}

// Конструктор перемещения
Player::Player(Player&& other) noexcept
        : field(std::move(other.field)),
          managerShips(std::move(other.managerShips)),
          name(std::move(other.name)) {}

// Оператор присваивания перемещением
Player& Player::operator=(Player&& other) noexcept {
    if (this != &other) {
        field = std::move(other.field);
        managerShips = std::move(other.managerShips);
        name = std::move(other.name);
    }
    return *this;
}