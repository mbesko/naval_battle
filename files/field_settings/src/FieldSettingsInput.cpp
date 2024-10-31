// FieldSettingsInput.cpp
#include "FieldSettingsInput.h"
#include "Game.h"
#include "MenuState.h"
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>

int FieldSettingsInput::handleInput(int currentSetting, int values[], int menuSize) {
    char ch = _getch();
    if (ch == -32) ch = _getch(); // Обработка стрелок

    switch (ch) {
        case ESC:
            PlaySound(TEXT("sounds/exit.wav"), NULL, SND_FILENAME | SND_ASYNC);
            Game::getInstance().setState(new MenuState());
            break;
        case UP:
            if (currentSetting > 0) {
                PlaySound(TEXT("sounds/menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
                --currentSetting;
                return currentSetting;
            }
            break;
        case DOWN:
            if (currentSetting < menuSize - 1) {
                PlaySound(TEXT("sounds/menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
                ++currentSetting;
                return currentSetting;
            }
            break;
        case LEFT:
            if (currentSetting < 5 ) {
                if (values[currentSetting]>0 && currentSetting != 0 || currentSetting == 0 && values[currentSetting]>2){
                --values[currentSetting];
                    if (checkFieldSpace(values) != 0)
                        ++values[currentSetting];
                PlaySound(TEXT("sounds/down.wav"), NULL, SND_FILENAME | SND_ASYNC);}
                return currentSetting;
            }
            break;
        case RIGHT:
            if (currentSetting < 5) {
                if (currentSetting == 0 && values[0] < 10 || currentSetting != 0){
                    ++values[currentSetting];}
                    if (currentSetting > 0){
                        if (checkFieldSpace(values) != 0)
                            --values[currentSetting];}}
            if (currentSetting < 5) PlaySound(TEXT("sounds/up.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    return currentSetting;
            break;
        case ENTER:
            return 10; // Возвращает выбранный пункт меню
    }
    return -1;
}

int FieldSettingsInput::checkFieldSpace(int values[]) {
    int required_cells =  values[1] * 1 +  values[2] * 2 +  values[3] * 3 +  values[4] * 4;
    int required_space = 0;

    required_space +=  values[1] * (1 + 2);
    required_space +=  values[2] * (2 + 2);
    required_space +=  values[3] * (3 + 2);
    required_space +=  values[4] * (4 + 2);

    int total_cells =  values[0] *  values[0];
    if (required_cells <= total_cells && required_space <= total_cells) {
        return 0; // Места хватает
    } else {
        return 1; // Места не хватает
    }
}
