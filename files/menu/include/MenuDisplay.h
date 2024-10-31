// MenuDisplay.h
#ifndef MENUDISPLAY_H
#define MENUDISPLAY_H

#include <string>

class MenuDisplay {
public:
    void printWelcomeScreen() const;
    void displayMenu(const std::string items[], int menuSize, int activeMenu) const;
};

#endif
