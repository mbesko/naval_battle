// MenuDisplay.cpp
#include "MenuDisplay.h"
#include "Console.h"
#include <iostream>

void MenuDisplay::printWelcomeScreen() const {
    std::cout << R"(









                                 ███╗░░██╗░█████╗░██╗░░░██╗░█████╗░██╗░░░░░  ██████╗░░█████╗░████████╗████████╗██╗░░░░░███████╗
                                 ████╗░██║██╔══██╗██║░░░██║██╔══██╗██║░░░░░  ██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║░░░░░██╔════╝
                                 ██╔██╗██║███████║╚██╗░██╔╝███████║██║░░░░░  ██████╦╝███████║░░░██║░░░░░░██║░░░██║░░░░░█████╗░░
                                 ██║╚████║██╔══██║░╚████╔╝░██╔══██║██║░░░░░  ██╔══██╗██╔══██║░░░██║░░░░░░██║░░░██║░░░░░██╔══╝░░
                                 ██║░╚███║██║░░██║░░╚██╔╝░░██║░░██║███████╗  ██████╦╝██║░░██║░░░██║░░░░░░██║░░░███████╗███████╗
                                 ╚═╝░░╚══╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚══════╝  ╚═════╝░╚═╝░░╚═╝░░░╚═╝░░░░░░╚═╝░░░╚══════╝╚══════╝

                                                              Приветствуем вас в игре Морской Бой!

                                                                    █▀▄▀█ █▀▀ █▄░█ █░█
                                                                    █░▀░█ ██▄ █░▀█ █▄█
        )" << std::endl;
}

void MenuDisplay::displayMenu(const std::string items[], int menuSize, int activeMenu) const {
    printWelcomeScreen();
    Console::clear();
    printWelcomeScreen();
    for (int i = 0; i < menuSize; i++) {
        if (i == activeMenu)
            Console::setTextAttribute(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        else
            Console::setTextAttribute(FOREGROUND_GREEN);

        Console::GoToXY(70, 23 + i);
        std::cout << items[i] << std::endl;
        Console::setTextAttribute(7);
    }
}
