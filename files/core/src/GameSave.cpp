#include "GameSave.h"
#include "Player.h"
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <filesystem>

class Player;

GameSave::GameSave(const std::string& filePath)
        : filePath(filePath) {
    if (!std::filesystem::exists(filePath)){
        std::filesystem::create_directory(filePath);}

    // Проверяем доступность пути
    std::ofstream testFile(filePath + "/test.txt");
    if (!testFile.is_open()) {
        throw std::runtime_error("Unable to access save directory: " + filePath);
    }
    testFile.close();
    std::remove((filePath + "/test.txt").c_str()); // Удаляем тестовый файл
}

GameSave::GameSave() : filePath("saves"){
    // Проверяем доступность пути
    if (!std::filesystem::exists(filePath)){
    std::filesystem::create_directory(filePath);}

    std::ofstream testFile(filePath + "/test.txt");
    if (!testFile.is_open()) {
        throw std::runtime_error("Unable to access save directory: " + filePath);
    }
    testFile.close();
    std::remove((filePath + "/test.txt").c_str()); // Удаляем тестовый файл
}

void GameSave::save(Player& player1, Player& player2)  {

    std::ofstream out(filePath + "/game_state.txt");
    if (!out.is_open()) {
        throw std::runtime_error("Unable to open file for saving game state.");
    }

    out << *this; // Сохраняем общий путь
    out << player1.getName() << "\n"; // Имя первого игрока
    out << player2.getName() << "\n"; // Имя второго игрока
    out.close();

    // Создаём директории для игроков
    std::string player1Prefix = filePath + "/Player1";
    std::string player2Prefix = filePath + "/Player2";
    std::filesystem::create_directories(player1Prefix);
    std::filesystem::create_directories(player2Prefix);

    // Сохраняем данные первого игрока
    player1.getField().saveToFile(player1Prefix + "/field.txt", true, player1.getManagerShips());
    player1.getManagerShips().saveToFile(player1Prefix + "/ships.txt", true);
    player1.getAbilityManager().saveToFile(player1Prefix + "/abilities.txt", true);
    player1.getAbilityManager().loadFromFile(player1Prefix + "/abilities.txt", player1.getField(), player1.getManagerShips());

    // Сохраняем данные второго игрока
    player2.getField().saveToFile(player2Prefix + "/field.txt", true, player2.getManagerShips());
    player2.getManagerShips().saveToFile(player2Prefix + "/ships.txt", true);
}

void GameSave::load(Player& player1, Player& player2)  {

    std::ifstream in(filePath + "/game_state.txt");
    if (!in.is_open()) {
        throw std::runtime_error("Unable to open file for loading game state.");
    }

    in >> *this; // Загружаем общий путь

    std::string player1Name, player2Name;
    if (!std::getline(in, player1Name) || !std::getline(in, player2Name)) {
        throw std::runtime_error("Corrupted save file: Missing player names.");
    }
    in.close();


    std::string player1Prefix = filePath + "/Player1";
    std::string player2Prefix = filePath + "/Player2";

    // Проверяем наличие всех файлов
    if (!std::filesystem::exists(player1Prefix + "/field.txt") ||
        !std::filesystem::exists(player1Prefix + "/ships.txt") ||
        !std::filesystem::exists(player1Prefix + "/abilities.txt") ||
        !std::filesystem::exists(player2Prefix + "/field.txt") ||
        !std::filesystem::exists(player2Prefix + "/ships.txt")) {}
    else {
    try {
        tmpsave(player1, player2);

        player1.cleanField();
        player2.cleanField();

        // Загружаем данные первого игрока
        player1.getManagerShips().loadFromFile(player1Prefix + "/ships.txt", player1.getField());
        player1.getField().loadFromFile(player1Prefix + "/field.txt", player1.getManagerShips());
        player1.getAbilityManager().loadFromFile(player1Prefix + "/abilities.txt", player1.getField(),
                                                 player1.getManagerShips());
        // Загружаем данные второго игрока
        player2.getManagerShips().loadFromFile(player2Prefix + "/ships.txt", player2.getField());
        player2.getField().loadFromFile(player2Prefix + "/field.txt", player2.getManagerShips());
    }
    catch(...) {
        tmpload(player1, player2);
    }
    tmpdel();
    }
}

void GameSave::tmpsave(Player& player1, Player& player2){

    std::string player1Prefix = filePath + "/Player1";
    std::string player2Prefix = filePath + "/Player2";
    player1.getField().saveToFile(player1Prefix + "/fieldtmp.txt", true, player1.getManagerShips());
    player1.getManagerShips().saveToFile(player1Prefix + "/shipstmp.txt", true);
    player1.getAbilityManager().saveToFile(player1Prefix + "/abilitiestmp.txt", true);
    player2.getField().saveToFile(player2Prefix + "/fieldtmp.txt", true, player2.getManagerShips());
    player2.getManagerShips().saveToFile(player2Prefix + "/shipstmp.txt", true);
}
void GameSave::tmpload(Player &player1, Player &player2) {

    std::string player1Prefix = filePath + "/Player1";
    std::string player2Prefix = filePath + "/Player2";


    player1.cleanField();
    player2.cleanField();

    player1.getManagerShips().loadFromFile(player1Prefix + "/shipstmp.txt", player1.getField());
    player1.getField().loadFromFile(player1Prefix + "/fieldtmp.txt", player1.getManagerShips());
    player1.getAbilityManager().loadFromFile(player1Prefix + "/abilitiestmp.txt", player1.getField(),
                                             player1.getManagerShips());
    player2.getManagerShips().loadFromFile(player2Prefix + "/shipstmp.txt", player2.getField());
    player2.getField().loadFromFile(player2Prefix + "/fieldtmp.txt", player2.getManagerShips());
}

void GameSave::tmpdel() {

    std::string player1Prefix = filePath + "/Player1";
    std::string player2Prefix = filePath + "/Player2";

    std::remove((player1Prefix + "/shipstmp.txt").c_str());
    std::remove((player1Prefix + "/fieldtmp.txt").c_str());
    std::remove((player1Prefix + "/abilitiestmp.txt").c_str());
    std::remove((player2Prefix + "/shipstmp.txt").c_str());
    std::remove((player2Prefix + "/fieldtmp.txt").c_str());
}

// Перегрузка оператора вывода (сериализация)
std::ostream& operator<<(std::ostream& out, const GameSave& save) {
    out << save.filePath << "\n"; // Сохраняем путь для сохранения
    return out;
}

// Перегрузка оператора ввода (десериализация)
std::istream& operator>>(std::istream& in, GameSave& save) {
    std::getline(in, save.filePath); // Загружаем путь для сохранения
    return in;
}