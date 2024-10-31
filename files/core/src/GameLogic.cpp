#include "GameLogic.h"
#include <iostream>
#include <windows.h>


// Конструктор логики игры
GameLogic::GameLogic(Player&& p1, Player&& p2)
        : player1(std::move(p1)), player2(std::move(p2)), isPlayer1Turn(true) {}

// Основной цикл игры
void GameLogic::startGame() {
    // Этап размещения кораблей перед началом игры

    pressEnter(player1.getName(), " размещает свои корабли", 64, 20);
    player1.placeShips();  // Игрок 1 размещает корабли
    Sleep(1000);
    pressEnter(player2.getName(), " размещает свои корабли", 64, 20);
    player2.placeShips();  // Игрок 2 размещает корабли
    Sleep(1000);

    // Основной игровой цикл
    while (!isGameOver()) {
        Player& currentPlayer = getCurrentPlayer();  // Получаем текущего игрока
        Player& opponent = getOpponent();  // Получаем соперника

        pressEnter(currentPlayer.getName(), " выполняет выстрел", 70, 20);
        currentPlayer.takeTurn(opponent, currentPlayer);


        if (opponent.getField().areAllShipsSunk()) {
            pressEnter(currentPlayer.getName(), " победил!", 70, 20);
            break;  // Игра окончена, все корабли соперника потоплены
        }
        switchTurn();  // Меняем ход на следующего игрока
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