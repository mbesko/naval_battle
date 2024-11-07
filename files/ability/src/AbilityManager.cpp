#include "AbilityManager.h"
#include "DoubleDamage.h"
#include "Scanner.h"
#include "Bombardment.h"

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

