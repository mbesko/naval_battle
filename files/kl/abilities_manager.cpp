#include "abilities_manager.h"
#include "double_damage.h"
#include "scanner.h"
#include "bombing.h"
#include "exceptions.h"
#include <algorithm> 
#include <random> 
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

AbilitiesManager::AbilitiesManager(GameBoard& gameBoard, ShipManager& manager)
    : gameBoard(gameBoard), manager(manager) {
    vector<int> elements = {0, 1, 2};

    // Генератор случайных чисел
    random_device rd;
    mt19937 g(rd());
    shuffle(elements.begin(), elements.end(), g);

    for (int elem : elements) {
        pushAbilityByIndex(elem);
    }
}

void AbilitiesManager::popAndUse() {
    if(abilitiesQueue.size() == 0) {
        throw NoAbilityException();
    }
    abilitiesQueue[0]->useAbility();
    abilitiesQueue.erase(abilitiesQueue.begin());
}

void AbilitiesManager::pushAbilityByIndex(int ind) {
    switch (ind) {
        case 0: abilitiesQueue.push_back(make_unique<DoubleDamage>(gameBoard, manager)); break;
        case 1: abilitiesQueue.push_back(make_unique<Scanner>(gameBoard, manager)); break;
        case 2: abilitiesQueue.push_back(make_unique<Bombing>(gameBoard, manager)); break;
        default: break;
    }
}
int AbilitiesManager::getRandomIndex() {
    srand(time(nullptr));
    return rand() % 3;
}
string AbilitiesManager::saveToFile(const string& filename, bool toSave) const {
    stringstream ss;

    // Сохраняем количество способностей
    ss << abilitiesQueue.size() << "\n";

    // Записываем тип каждой способности
    for (const auto& ability : abilitiesQueue) {
        ss << ability->save() << "\n";
    }

    // Сохраняем данные из ss в файл
    ofstream outFile(filename);
    if (!outFile) {
        throw runtime_error("Unable to open file for saving abilities.");
    }
    if (!toSave) {
        return ss.str();
    }
    outFile << ss.str();
    outFile.close();
    return ss.str();
}

// Метод для загрузки очереди способностей из файла
void AbilitiesManager::loadFromFile(const string& filename, GameBoard& newGameBoard, ShipManager& newManager) {
    ifstream inFile(filename);
    if (!inFile) {
        throw runtime_error("Unable to open file for loading abilities.");
    }

    abilitiesQueue.clear();
    size_t abilityCount;
    inFile >> abilityCount;
    inFile.ignore(numeric_limits<streamsize>::max(), '\n'); // Пропустить оставшуюся часть строки

    for (size_t i = 0; i < abilityCount; ++i) {
        string abilityType;
        getline(inFile, abilityType);

        if (abilityType == "DoubleDamage") {
            abilitiesQueue.push_back(make_unique<DoubleDamage>(gameBoard, manager));
        } else if (abilityType == "Scanner") {
            abilitiesQueue.push_back(make_unique<Scanner>(gameBoard, manager));
        } else if (abilityType == "Bombing") {
            abilitiesQueue.push_back(make_unique<Bombing>(gameBoard, manager));
        }
    }
    manager = newManager;
    gameBoard = newGameBoard;
    inFile.close();
}
void AbilitiesManager::update(GameBoard& newGameBoard, ShipManager& newManager) {
    gameBoard = newGameBoard;
    manager = newManager;
}