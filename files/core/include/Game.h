#ifndef GAME_H
#define GAME_H

#include "GameState.h"

class Game {
private:
    static Game* instance;
    GameState* state;
    bool isRunning;
    Game();

public:
    static Game& getInstance();
    void setState(GameState* newState);
    void run();
    void quit();
};

#endif
