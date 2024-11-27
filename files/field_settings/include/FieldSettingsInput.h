// FieldSettingsInput.h
#ifndef FIELDSETTINGSINPUT_H
#define FIELDSETTINGSINPUT_H

#include "KeyCodes.h"

class FieldSettingsInput {
public:
    int handleInput(int currentSetting, int values[], int menuSize);
    int checkFieldSpace(int values[]);
};

#endif
