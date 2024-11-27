#include "Game.h"
#include "Console.h"
#include <windows.h>
#include <iomanip>


int main() {
    setlocale(0, "Ru");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleTitle("Naval Battle");

    Console::clear();
    Console::setCursorVisible(false, 100);


    Game::getInstance().run();

    return 0;
}
