// FieldSettingsDisplay.cpp
#include "FieldSettingsDisplay.h"
#include "Console.h"
#include <iostream>

void FieldSettingsDisplay::displayScreen(const std::string items[], const int values[], int menuSize, int activeItem) const {
    Console::GoToXY(50, 10);
    std::cout << R"(






                                                     █▀▀ █ █▀▀ █░░ █▀▄   █▀ █▀▀ ▀█▀ ▀█▀ █ █▄░█ █▀▀ █▀
                                                     █▀░ █ ██▄ █▄▄ █▄▀   ▄█ ██▄ ░█░ ░█░ █ █░▀█ █▄█ ▄█
    )" << std::endl;

    for (int i = 0; i < menuSize; i++) {
        if (i == activeItem)
            Console::setTextAttribute(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        else
            Console::setTextAttribute(FOREGROUND_GREEN);

        Console::GoToXY(64, 20 + i);
        std::cout << "| " << items[i];
        if (i < 5) {
            std::cout << "  |  " << values[i] << std::endl;
        }
        Console::setTextAttribute(7);
    }
}
