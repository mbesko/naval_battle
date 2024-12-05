#ifndef FIELDSETTINGSSTATE_H
#define FIELDSETTINGSSTATE_H

#include "GameState.h"
#include "Console.h"
#include "FieldSettingsDisplay.h"
#include "FieldSettingsInput.h"
#include <string>

// Класс состояния настройки поля перед началом игры
class FieldSettingsState : public GameState {
private:
    enum FieldSettingsItems {
        FieldSize = 0,
        OneDeck,
        TwoDeck,
        ThreeDeck,
        FourDeck,
        Exit,
        StartGame
    };

    std::string items[7]; // Элементы меню настроек
    int values[5]; // Значения параметров (размер поля, количество кораблей)
    int activeFieldSettings; // Текущий выбранный пункт меню
    int fieldSettingsSize;  // Количество пунктов меню

    FieldSettingsDisplay fieldDisplay;
    FieldSettingsInput input;

public:
    FieldSettingsState(); // Конструктор состояния
    void display() override; // Отображение экрана настроек
    void handleInput() override;  // Обработка ввода пользователя
    //int checkFieldSpace(int field_size, int one_deck, int two_deck, int three_deck, int four_deck); // Проверка допустимости количества кораблей
};

#endif
