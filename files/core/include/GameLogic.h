#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Player.h"
#include "Console.h"
#include <conio.h>

// Класс, управляющий ходами игры и логикой
class GameLogic /*: public GameState*/ {
private:
    Player player1;  // Первый игрок
    Player player2;  // Второй игрок
    bool isPlayer1Turn;  // Чей сейчас ход

public:
    GameLogic(Player&& p1, Player&& p2);  // Конструктор с передачей игроков
    void startGame();  // Начало игры и основной игровой цикл
    void pressEnter(std::string player, std::string text, int x, int y);
    void switchTurn();  // Смена хода
    bool isGameOver();  // Проверка, окончена ли игра
    Player& getCurrentPlayer();  // Получение текущего игрока
    Player& getOpponent();  // Получение соперника

//
//    // Реализация чисто виртуальных методов
//    void display() override;  // Для вызова без параметров
//    void handleInput() override;  // Для вызова без параметров
};

#endif