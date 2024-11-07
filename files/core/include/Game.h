#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "../../entities/include/Ship.h"

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
//    void runGame(Ship* currentShip, int go, bool enemy, bool open, bool& actionConfirmed);
    void quit();
};

#endif
