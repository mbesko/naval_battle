//
// Created by Maxim on 07.11.2024.
//

#ifndef NAVAL_BATTLE_GAMEFIELDINPUT_H
#define NAVAL_BATTLE_GAMEFIELDINPUT_H

#include "../../core/include/KeyCodes.h"
#include <conio.h>

class GameFieldInput {
public:
    int handleGameFieldInput(int &cursorX, int &cursorY, int height, int width);
};


#endif //NAVAL_BATTLE_GAMEFIELDINPUT_H
