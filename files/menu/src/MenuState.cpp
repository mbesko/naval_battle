#include "MenuState.h"
#include "Game.h"
#include "FieldSettingsState.h"
#include <conio.h>
#include <windows.h>
#include "KeyCodes.h"
#include <iostream>

MenuState::MenuState() : activeMenu(NewGame), items{"Новая игра", "Загрузить", "Настройки", "Выход"}, menuSize(4) {}

//
//void MenuState::display() {
//    printWelcomeScreen();
//    for (int i = 0; i < menuSize; i++) {
//        if (i == activeMenu)
//            Console::setTextAttribute(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
//        else
//            Console::setTextAttribute(FOREGROUND_GREEN);
//
//        Console::GoToXY(70, 23 + i);
//        std::cout << items[i] << std::endl;
//        Console::setTextAttribute(7);
//    }
//}
//
//void MenuState::handleInput() {
//        char ch = _getch();
//        if (ch == -32) ch = _getch(); // Для обработки стрелок
//        switch (ch) {
//            case ESC:
//                exit(0);
//            case UP:
//                if (activeMenu > NewGame) {
//                    PlaySound(TEXT("sounds/menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
//                    --activeMenu;
//                }
//            break;
//            case DOWN:
//                if (activeMenu < Exit) {
//                    PlaySound(TEXT("sounds/menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
//                    ++activeMenu;
//                }
//            break;
//            case ENTER:
//                PlaySound(TEXT("sounds/enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
//            executeAction();
//            break;
//        }
//}
//
//void MenuState::executeAction() {
//    switch (activeMenu) {
//        case NewGame:
//            Game::getInstance().setState(new FieldSettingsState());
//            break;
//        case LoadGame:
//        case Settings:
//            Console::clear();
//            Console::GoToXY(50, 12);
//            Console::setTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
//            std::cout << "в разработке";
//            Console::setTextAttribute(7);
//            _getch();
//            PlaySound(TEXT("sounds/exit.wav"), NULL, SND_FILENAME | SND_ASYNC);
//            Console::clear();
//            break;
//        case Exit:
//            exit(0);
//    }
//}

void MenuState::display() {
    menuDisplay.displayMenu(items, menuSize, activeMenu);
}

void MenuState::handleInput() {

    int selectedMenu = input.handleMenuInput(activeMenu, menuSize);
    if (selectedMenu != activeMenu && selectedMenu != -1) {
        activeMenu = selectedMenu;
    } else if (selectedMenu == activeMenu) {
        executeAction(activeMenu);
    }
}

void MenuState::executeAction(int selectedMenu) {
    switch (selectedMenu) {
        case NewGame:
            Game::getInstance().setState(new FieldSettingsState());
            break;
        case LoadGame:
        case Settings:
            Console::clear();
            Console::GoToXY(50, 12);
            Console::setTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            std::cout << "в разработке";
            Console::setTextAttribute(7);
            _getch();
            PlaySound(TEXT("sounds/exit.wav"), NULL, SND_FILENAME | SND_ASYNC);
            Console::clear();
            break;
        case Exit:
            Game::getInstance().quit();  // Завершение игры
            break;
    }
}