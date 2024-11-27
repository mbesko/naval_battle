#include "game_state.h"

Game_State::Game_State(string enemyPath, string playerPath)
    : enemyPath(enemyPath), playerPath(playerPath) {};

void Game_State::writeData(GameBoard& newPlayerBoard, GameBoard& newEnemyBoard, ShipManager& newPlayerManager, ShipManager& newEnemyManager,  AbilitiesManager& newAbilitiesManager) {
    playerBoard = newPlayerBoard.saveToFile(playerPath, false);
    enemyBoard = newEnemyBoard.saveToFile(enemyPath, false);
    playerManager = newPlayerManager.saveToFile(playerPath, false);
    enemyManager = newEnemyManager.saveToFile(enemyPath, false);
    abilitiesManager = newAbilitiesManager.saveToFile(playerPath, false);
}
void Game_State::saveData(GameBoard& playerBoard, GameBoard& enemyBoard, ShipManager& playerManager, ShipManager& enemyManager,  AbilitiesManager& abilitiesManager) {
    playerBoard.saveToFile(playerPath + "/board.txt", true);
    enemyBoard.saveToFile(enemyPath + "/board.txt", true);
    playerManager.saveToFile(playerPath + "/manager.txt", true);
    enemyManager.saveToFile(enemyPath + "/manager.txt", true);
    abilitiesManager.saveToFile(playerPath + "/ability_manager.txt", true);
}
void Game_State::loadData(GameBoard& playerBoard, GameBoard& enemyBoard, ShipManager& playerManager, ShipManager& enemyManager,  AbilitiesManager& abilitiesManager) {
    playerBoard.loadFromFile(playerPath + "/board.txt");
    enemyBoard.loadFromFile(enemyPath + "/board.txt");
    playerManager.loadFromFile(playerPath + "/manager.txt");
    enemyManager.loadFromFile(enemyPath + "/manager.txt");
    abilitiesManager.loadFromFile(playerPath + "/ability_manager.txt", enemyBoard, enemyManager);
}
// Оператор вывода в поток для сохранения состояния игры
#include <iostream>
#include <string>
#include "game_state.h"

// Оператор вывода: сериализация данных в поток
ostream& operator<<(ostream& out, const Game_State& state) {
    out << state.enemyPath << '\n'
        << state.playerPath << '\n'
        << state.playerBoard << '\n'
        << state.enemyBoard << '\n'
        << state.playerManager << '\n'
        << state.enemyManager << '\n'
        << state.abilitiesManager << '\n';
    return out;
}

// Оператор ввода: десериализация данных из потока
istream& operator>>(istream& in, Game_State& state) {
    getline(in, state.enemyPath);
    getline(in, state.playerPath);
    getline(in, state.playerBoard);
    getline(in, state.enemyBoard);
    getline(in, state.playerManager);
    getline(in, state.enemyManager);
    getline(in, state.abilitiesManager);
    return in;
}
