#include "GameSave.h"
#include "Player.h"
#include <stdexcept>
#include <fstream>
#include <sstream>

class Player;

GameSave::GameSave(const std::string& filePath)
        : filePath(filePath) {}

GameSave::GameSave(){}

void GameSave::save(Player& player1, Player& player2)  {
    // Сохраняем данные первого игрока
    std::string player1Prefix = "saves/Player1";
    player1.getField().saveToFile(player1Prefix + "/field.txt", true, player1.getManagerShips());
    player1.getManagerShips().saveToFile(player1Prefix + "/ships.txt", true);
    player1.getAbilityManager().saveToFile(player1Prefix + "/abilities.txt", true);
    player1.getAbilityManager().loadFromFile(player1Prefix + "/abilities.txt", player1.getField(), player1.getManagerShips());

    // Сохраняем данные второго игрока
    std::string player2Prefix = "saves/Player2";
    player2.getField().saveToFile(player2Prefix + "/field.txt", true, player2.getManagerShips());
    player2.getManagerShips().saveToFile(player2Prefix + "/ships.txt", true);
}

void GameSave::load(Player& player1, Player& player2)  {
    player1.cleanField();
    player2.cleanField();

    // Загружаем данные первого игрока
    std::string player1Prefix =  "saves/Player1";
    player1.getManagerShips().loadFromFile(player1Prefix + "/ships.txt", player1.getField());
    player1.getField().loadFromFile(player1Prefix + "/field.txt", player1.getManagerShips());
    player1.getAbilityManager().loadFromFile(player1Prefix + "/abilities.txt", player1.getField(), player1.getManagerShips());

    // Загружаем данные второго игрока
    std::string player2Prefix = "saves/Player2";
    player2.getManagerShips().loadFromFile(player2Prefix + "/ships.txt", player2.getField());
    player2.getField().loadFromFile(player2Prefix + "/field.txt", player2.getManagerShips());
}
