#include "Game.h"
#include "MenuState.h"
#include <windows.h>

Game* Game::instance = nullptr;

Game::Game() : state(new MenuState()), isRunning(true) {}

Game& Game::getInstance() {
    if (!instance) {
        instance = new Game();
    }
    return *instance;
}

void Game::setState(GameState* newState) {
    delete state;
    state = newState;
}

void Game::run() {
    while (isRunning) {
        Console::clear();
        state->display();
        state->handleInput();
    }
}

void Game::quit() {
    isRunning = false;  // Остановка игрового цикла
}