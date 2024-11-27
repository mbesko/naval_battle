#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include "Console.h"
#include "MenuDisplay.h"
#include "MenuInput.h"
#include <string>

class MenuState : public GameState {
private:
    enum MenuItems {
        NewGame = 0,
        LoadGame,
        Settings,
        Exit
    };

    std::string items[4];
    int activeMenu;
    int menuSize;
    MenuDisplay menuDisplay;
    MenuInput input;

public:
    MenuState();
    void display() override;
    void handleInput() override;
    void executeAction(int selectedMenu);
};

#endif
