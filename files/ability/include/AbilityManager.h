#ifndef ABILITYMANAGER_H
#define ABILITYMANAGER_H

#include "Ability.h"
#include <queue>
#include <memory>
#include <algorithm>
#include <random>

//class GameField;

class AbilityManager {
private:
    std::queue<std::unique_ptr<Ability>> abilitiesQueue;
public:
    AbilityManager();  // Конструктор, который инициализирует способности случайным образом
    static AbilityManager& getInstance();  // Метод для получения синглтона


    std::string saveToFile(const std::string& filename, bool toSave);
    void loadFromFile(const std::string& filename, GameField& gameField, ManagerShips& managerShips);



        // Метод для раздачи способности игроку (возвращает способность)
    std::unique_ptr<Ability> getRandomAbility();
    void addRandomAbility();
    // Метод для добавления способности обратно в очередь
    void addAbility(std::unique_ptr<Ability> ability);

    // Проверка, есть ли доступные способности
    bool hasAbilities() const;

    // Методы для работы со списком способностей
    int getAbilitiesCount();

};

#endif // ABILITYMANAGER_H
