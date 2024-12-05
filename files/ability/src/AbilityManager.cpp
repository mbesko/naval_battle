#include "AbilityManager.h"
#include "DoubleDamage.h"
#include "Scanner.h"
#include "Bombardment.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

std::string AbilityManager::saveToFile(const std::string& filename, bool toSave) {
    std::stringstream ss;

    // Сохраняем количество способностей
    ss << abilitiesQueue.size() << "\n";

    // Сохраняем типы способностей
    while (!abilitiesQueue.empty()) {
        const auto& ability = abilitiesQueue.front();
        if (dynamic_cast<DoubleDamage*>(ability.get())) {
            ss << "DoubleDamage\n";
        } else if (dynamic_cast<Scanner*>(ability.get())) {
            ss << "Scanner\n";
        } else if (dynamic_cast<Bombardment*>(ability.get())) {
            ss << "Bombardment\n";
        }
        abilitiesQueue.pop();
    }

    if (!toSave) {
        return ss.str(); // Если сохранять в файл не нужно, возвращаем строку
    }

    // Сохраняем данные в файл
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw std::runtime_error("Unable to open file for saving abilities.");
    }

    outFile << ss.str();
    outFile.close();
    return ss.str();
}






void AbilityManager::loadFromFile(const std::string& filename, GameField& gameField, ManagerShips& managerShips) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open file for loading abilities.");
    }

    // Очищаем текущую очередь способностей
    while (!abilitiesQueue.empty()) {
        abilitiesQueue.pop();
    }

    // Считываем количество способностей
    size_t abilityCount;
    inFile >> abilityCount;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Пропустить оставшуюся часть строки

    // Считываем и восстанавливаем способности
    for (size_t i = 0; i < abilityCount; ++i) {
        std::string abilityType;
        std::getline(inFile, abilityType);

        if (abilityType == "DoubleDamage") {
            abilitiesQueue.push(std::make_unique<DoubleDamage>());
        } else if (abilityType == "Scanner") {
            abilitiesQueue.push(std::make_unique<Scanner>());
        } else if (abilityType == "Bombardment") {
            abilitiesQueue.push(std::make_unique<Bombardment>());
        } else {
            throw std::runtime_error("Unknown ability type in save file: " + abilityType);
        }
    }

    inFile.close();
}





AbilityManager::AbilityManager() {
    // Инициализация трех способностей в случайном порядке
    std::vector<std::unique_ptr<Ability>> abilities;
    abilities.push_back(std::make_unique<DoubleDamage>());
    abilities.push_back(std::make_unique<Scanner>());
    abilities.push_back(std::make_unique<Bombardment>());

    // Перемешиваем способности случайным образом
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(abilities.begin(), abilities.end(), g);

    // Добавляем их в очередь
    for (auto& ability : abilities) {
        abilitiesQueue.push(std::move(ability));
    }
}

std::unique_ptr<Ability> AbilityManager::getRandomAbility() {
    if (!abilitiesQueue.empty()) {
        auto ability = std::move(abilitiesQueue.front());
        abilitiesQueue.pop();
        return ability;
    }
    return nullptr;
}

void AbilityManager::addAbility(std::unique_ptr<Ability> ability) {
    abilitiesQueue.push(std::move(ability));
}

void AbilityManager::addRandomAbility() {
    // Список доступных способностей
    std::vector<std::unique_ptr<Ability>> abilities;
    abilities.push_back(std::make_unique<DoubleDamage>());
    abilities.push_back(std::make_unique<Scanner>());
    abilities.push_back(std::make_unique<Bombardment>());

    // Генерация случайного индекса
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, abilities.size() - 1);
    int randomIndex = dist(gen);

    // Перемещаем случайную способность в очередь
    abilitiesQueue.push(std::move(abilities[randomIndex]));
}


bool AbilityManager::hasAbilities() const {
    return !abilitiesQueue.empty();
}


int AbilityManager::getAbilitiesCount() {
    return abilitiesQueue.size();  // Возвращаем количество способностей
}

AbilityManager& AbilityManager::getInstance() {
    static AbilityManager instance;  // Синглтон
    return instance;
}

