#include "Player.h"
#include <iostream>
#include <windows.h>



Player::Player(const std::string& name, int fieldSize, int oneDeck, int twoDeck, int threeDeck, int fourDeck) : name(name), field(fieldSize), managerShips(oneDeck, twoDeck, threeDeck, fourDeck){}

// Инициализация кораблей с заданным количеством палуб
void Player::initShips(int oneDeck, int twoDeck, int threeDeck, int fourDeck) {
    managerShips.addShips(oneDeck, twoDeck, threeDeck, fourDeck);
}

void Player::cleanField(){
    field.clean();
}

// Размещение кораблей игроком
void Player::placeShips() {
    for (auto& ship : managerShips.getShips()) {
        bool isPlacingShip = true;  // Пока корабль не размещён, игрок выбирает позицию

        while (isPlacingShip) {
            Console::clear();
            field.display(ship.get());  // Отображаем поле и область размещения корабля
            field.handleInput(isPlacingShip, ship.get());  // Обработка перемещения и размещения

            if (!isPlacingShip) {
                std::cout << "Корабль успешно размещен!" << std::endl;
                PlaySound(TEXT("sounds/shipplacement.wav"), NULL, SND_FILENAME | SND_ASYNC);

            }
        }
    }
    field.setStateUnknown();
    field.setZeroCursor();
}

// Ход игрока: выбор цели и выполнение выстрела
bool Player::takeTurn(Player& opponent, Player& currentPlayer) {
    bool shotMade = false;  // Пока выстрел не сделан
    int fieldSize = field.getSize();
    while (!shotMade) {
        Console::clear();
        Console::GoToXY(0, 0);
        opponent.getField().display(nullptr);  // Отображаем поле противника
        opponent.managerShips.displayAliveShipsBySize(0, fieldSize*2+5);

        currentPlayer.getField().display(nullptr,field.getSize() * 6+5, false, true);
        currentPlayer.managerShips.displayAliveShipsBySize(fieldSize * 6+10, fieldSize*2+5);
        opponent.getField().handleInput(shotMade, nullptr);  // Обрабатываем выбор цели и выстрел



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

GameField& Player::getField() {
    return field;
}

std::string Player::getName() const {
    return name;
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