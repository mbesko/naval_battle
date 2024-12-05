#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState {
public:
    virtual void display() = 0;
    virtual void handleInput() = 0;
    virtual ~GameState() = default;
};

#endif