#include "GameLogic.h"
#include <iostream>
#include <windows.h>


//// Конструктор логики игры
//GameLogic::GameLogic(Player&& p1, Player&& p2)
//        : player1(std::move(p1)), player2(std::move(p2)), isPlayer1Turn(true) {}

GameLogic::GameLogic(int fieldSize, int oneDeck, int twoDeck, int threeDeck, int fourDeck)
        : player1("Игрок 1",fieldSize, oneDeck, twoDeck, threeDeck,  fourDeck), player2("Игрок 2",fieldSize,  oneDeck, twoDeck, threeDeck,  fourDeck), isPlayer1Turn(true) {}

// Основной цикл игры
void GameLogic::startGame(bool save) {
    // Этап размещения кораблей перед началом игры
    if (save){
        GameSave save("saves");
        save.load(player1,player2);
    }
    bool isGame = true;
    while (true) {
        if (!isGame) break;
        if(!save){
        player1.placeShips();  // Игрок 1 размещает корабли
        Sleep(1000);}
        while (isGame){
            if(!save){
            player2.placeShipsRandomly();  // Игрок 2 размещает корабли
            Sleep(1000);}
        // Основной игровой цикл
        save = false;
        while (!isGameOver()) {

            Player &currentPlayer = player1;  // Получаем текущего игрока
            Player &opponent = player2;  // Получаем соперника

            currentPlayer.takeTurn(opponent, currentPlayer);

            if (opponent.getField().areAllShipsSunk()) {
                pressEnter(currentPlayer.getName(), " победил!", 70, 20);
                break;  // Игра окончена, все корабли соперника потоплены
            }
            opponent.randomAttack(currentPlayer);

            if (currentPlayer.getField().areAllShipsSunk()) {
                isGame = false;
                pressEnter(opponent.getName(), " победил!", 70, 20);
                break;  // Игра окончена, все корабли соперника потоплены
            }

        }
        if (isGame) {
            std::string choice;
            std::cout << "Хотите начать новую игру? (y/n): ";
            std::cin >> choice;
            if (choice != "y" && choice != "Y") {
                isGame = false;
                break;  // Выход из внешнего цикла, если игрок не хочет играть снова
            }
            player2.cleanField();
        }
    }
    }
}
void GameLogic::pressEnter(std::string player, std::string text, int x, int y) {
    Console::clear();
    Console::GoToXY(x,y);
    std::cout << player << text;
    Console::GoToXY(x+10,y+1);
    std::cout << "(enter)";
    Console::GoToXY(x+50,y+1);
    std::cout << R"(




                                                                                     .
                                                                   .                 |
                                                                   +                 |
                                                          .        |                *+W+-*
                                             .           +y        +W+              . H                 .
                                          .  +y            |I.   y  |               ! H= .           .  ^
                                          !   \     .     |H '. /   |  ___.        .! H  !   +--.--y !  V
                                          !    \     \  +=|H|=='.=+ | |====\   _  '_H_H__H_. H_/=  J !  !
                                        . !     \'    VVV_HHH_/__'._H |  E  \_|=|_|========|_|==|____H. ! _______.
                                        I-H_I=I=HH_==_|I_IIIII_I_I_=HH|======.I-I-I-=======-I=I=I=I_=H|=H'===I=I/
                                        \                                                                      ,
                                         |                                                                    /
                                 ~~~~ ~ ~.___________________________________________________________________'~~ ~ ~ ~ ~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
)" << std::endl;
    while (_getch() != 13) {
    }

}

// Смена хода между игроками
void GameLogic::switchTurn() {
    isPlayer1Turn = !isPlayer1Turn;
}

// Проверка окончания игры (если все корабли соперника потоплены)
bool GameLogic::isGameOver() {
    return player1.getField().areAllShipsSunk() || player2.getField().areAllShipsSunk();
}

// Получение текущего игрока (в зависимости от хода)
Player& GameLogic::getCurrentPlayer() {
    return isPlayer1Turn ? player1 : player2;
}

// Получение соперника (противник текущего игрока)
Player& GameLogic::getOpponent() {
    return isPlayer1Turn ? player2 : player1;
}

//// Пустая реализация чисто виртуального метода display
//void GameLogic::display() {
//    // Можно оставить пустым или добавить логику позже
//}
//
//// Пустая реализация чисто виртуального метода handleInput
//void GameLogic::handleInput() {
//    // Можно оставить пустым или добавить логику позже
//}

