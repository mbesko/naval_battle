// FieldSettingsDisplay.h
#ifndef FIELDSETTINGSDISPLAY_H
#define FIELDSETTINGSDISPLAY_H

#include <string>

class FieldSettingsDisplay {
public:
    void displayScreen(const std::string items[], const int values[], int menuSize, int activeItem) const;
};

#endif
