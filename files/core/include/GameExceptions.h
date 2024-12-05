// GameExceptions.h
#ifndef GAME_EXCEPTIONS_H
#define GAME_EXCEPTIONS_H

#include <iostream>
#include <exception>

// Базовый класс для всех пользовательских исключений
class GameException : public std::exception {
public:
    const char* what() const noexcept override {
            return "GameException occurred";
    }
};

// Исключение при попытке доступа к отсутствующей способности
class AbilityNotAvailableException : public GameException {
public:
    const char* what() const noexcept override {
            return "Нет доступных способностей.";
    }
};

class ShipPlacementException  : public GameException {
public:
    const char* what() const noexcept override {
            return "Невозможно разместить корабль. Попробуйте другую позицию.";
    }
};

class AbilityAcquisitionException  : public GameException {
public:
    const char* what() const noexcept override {
            return "Не удалось получить способность. Попробуйте снова.";
    }
};


#endif // GAME_EXCEPTIONS_H
