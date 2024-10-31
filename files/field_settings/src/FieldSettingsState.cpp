#include "FieldSettingsState.h"
#include "Game.h"
#include "MenuState.h"
#include "GameField.h"
#include <conio.h>
#include "KeyCodes.h"
#include <windows.h>
#include <iostream>
#include "GameLogic.h"


FieldSettingsState::FieldSettingsState() : activeFieldSettings(FieldSize), items{"Размер поля     ", "Однопалубный    ", "Двухпалубный    ", "Трехпалубный    ", "Четырехпалубный ", "Выход", "Начать игру"}, fieldSettingsSize(7) {
    fieldSettingsSize = sizeof(items) / sizeof(items[0]);
    values[FieldSize] = 10;
    values[OneDeck] = 0;
    values[TwoDeck] = 0;
    values[ThreeDeck] = 0;
    values[FourDeck] = 0;
}





//void FieldSettingsState::display()  {
//
//    Console::GoToXY(50, 10);
//    std::cout << R"(
//
//
//
//
//
//
//                                                    █▀▀ █ █▀▀ █░░ █▀▄   █▀ █▀▀ ▀█▀ ▀█▀ █ █▄░█ █▀▀ █▀
//                                                    █▀░ █ ██▄ █▄▄ █▄▀   ▄█ ██▄ ░█░ ░█░ █ █░▀█ █▄█ ▄█
//)" << std::endl;
//    for (int i = 0; i < fieldSettingsSize; i++)
//    {
//        if (i == activeFieldSettings)
//            Console::setTextAttribute(FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Выделение активного пункта
//        else
//            Console::setTextAttribute(FOREGROUND_GREEN);
//        Console::GoToXY(64, 20 + i); // Переход на строку i
//        std::cout << "| " << items[i] ;
//        if (i < 5){
//            std::cout <<"  |  "<<values[i] << std::endl;}
//        Console::setTextAttribute(7);
//
//
//    }
//
//}
// Функция для расчёта, хватает ли места для размещения кораблей
//int FieldSettingsState::checkFieldSpace(int field_size, int one_deck, int two_deck, int three_deck, int four_deck) {
//    int required_cells = one_deck * 1 + two_deck * 2 + three_deck * 3 + four_deck * 4;
//    int required_space = 0;
//
//    required_space += one_deck * (1 + 2);
//    required_space += two_deck * (2 + 2);
//    required_space += three_deck * (3 + 2);
//    required_space += four_deck * (4 + 2);
//
//    int total_cells = field_size * field_size;
//    if (required_cells <= total_cells && required_space <= total_cells) {
//        return 0; // Места хватает
//    } else {
//        return 1; // Места не хватает
//    }
//}
//void FieldSettingsState::handleInput()  {
//    char ch = _getch();
//    if (ch == -32) ch = _getch(); // Для обработки стрелок
//    switch (ch)
//    {
//        case ESC:
//            PlaySound(TEXT("sounds/exit.wav"), NULL, SND_FILENAME | SND_ASYNC);
//            Game::getInstance().setState(new MenuState());
//        case UP:
//            if (activeFieldSettings > FieldSize){
//                PlaySound(TEXT("sounds/menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
//                --activeFieldSettings;}
//            break;
//        case DOWN:
//            if (activeFieldSettings < StartGame) {
//                PlaySound(TEXT("sounds/menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
//                ++activeFieldSettings;
//            }
//            break;
//        case LEFT:
//            if (activeFieldSettings < 5){
//            if (values[activeFieldSettings]>0 && activeFieldSettings != 0 || activeFieldSettings == 0 && values[activeFieldSettings]>2){
//                --values[activeFieldSettings];
//                if (checkFieldSpace(values[FieldSize], values[OneDeck], values[TwoDeck], values[ThreeDeck], values[FourDeck]) != 0)
//                    ++values[activeFieldSettings];
//            }
//                PlaySound(TEXT("sounds/down.wav"), NULL, SND_FILENAME | SND_ASYNC);}
//            break;
//        case RIGHT:
//            if (activeFieldSettings < 5){
//            if (activeFieldSettings == 0 && values[0] < 10 || activeFieldSettings != 0){
//            ++values[activeFieldSettings];}
//            if (activeFieldSettings > 0){
//                if (checkFieldSpace(values[FieldSize], values[OneDeck], values[TwoDeck], values[ThreeDeck], values[FourDeck]) != 0)
//                    --values[activeFieldSettings];}}
//            if (activeFieldSettings < 5) PlaySound(TEXT("sounds/up.wav"), NULL, SND_FILENAME | SND_ASYNC);
//            break;
//        case ENTER:
//            PlaySound(TEXT("sounds/enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
//            switch (activeFieldSettings)
//            {
//                case Exit:  // Выход в главное меню
//                    PlaySound(TEXT("sounds/exit.wav"), NULL, SND_FILENAME | SND_ASYNC);
//                    Game::getInstance().setState(new MenuState());
//                    break;
//                case StartGame:  // Начало игры
//                    if(values[OneDeck] + values[TwoDeck] + values[ThreeDeck] + values[FourDeck] == 0){
//                        break;
//                    }
//                    PlaySound(TEXT("sounds/enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
//                    // Создаем игроков
//                    Player player1("Игрок 1", values[FieldSize], values[OneDeck], values[TwoDeck], values[ThreeDeck], values[FourDeck]);
//                    Player player2("Игрок 2", values[FieldSize],values[OneDeck], values[TwoDeck], values[ThreeDeck], values[FourDeck]);
//
//                    Sleep(1000);
//                    // Передаем данные о кораблях для каждого игрока
////                    player1.initShips(values[OneDeck], values[TwoDeck], values[ThreeDeck], values[FourDeck]);
////                    player2.initShips(values[OneDeck], values[TwoDeck], values[ThreeDeck], values[FourDeck]);
//                    // Запуск игрового процесса
//                    std::unique_ptr<GameLogic> gameLogic = std::make_unique<GameLogic>(std::move(player1), std::move(player2));
//                    gameLogic->startGame();
////                    Game::getInstance().setState(new GameLogic(std::move(player1), std::move(player2)));
////
//                    break;
//            }
//            break;
//    }
//}

void FieldSettingsState::display() {
    fieldDisplay.displayScreen(items, values, fieldSettingsSize, activeFieldSettings);
}

void FieldSettingsState::handleInput() {
    int selectedMenuFieldSettings = input.handleInput(activeFieldSettings, values, fieldSettingsSize);
    if (selectedMenuFieldSettings != activeFieldSettings && selectedMenuFieldSettings != -1 && selectedMenuFieldSettings != 10) {
        activeFieldSettings = selectedMenuFieldSettings;
    }
    else if (activeFieldSettings == Exit && selectedMenuFieldSettings == 10) {
        PlaySound(TEXT("sounds/exit.wav"), NULL, SND_FILENAME | SND_ASYNC);
        Game::getInstance().setState(new MenuState());
    } else if (selectedMenuFieldSettings == 10 && activeFieldSettings == StartGame && values[OneDeck] + values[TwoDeck] + values[ThreeDeck] + values[FourDeck] > 0) {
        PlaySound(TEXT("sounds/enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
        Player player1("Игрок 1", values[FieldSize], values[OneDeck], values[TwoDeck], values[ThreeDeck], values[FourDeck]);
        Player player2("Игрок 2", values[FieldSize], values[OneDeck], values[TwoDeck], values[ThreeDeck], values[FourDeck]);
        Sleep(1000);
        std::unique_ptr<GameLogic> gameLogic = std::make_unique<GameLogic>(std::move(player1), std::move(player2));
        gameLogic->startGame();
    }
}