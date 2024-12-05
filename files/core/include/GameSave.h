#ifndef GAMESAVE_H
#define GAMESAVE_H


#include <string>

class Player;


class GameSave {
private:
    std::string filePath; // Общий путь для файлов сохранения

public:
    GameSave(const std::string& filePath);
    GameSave();

    void save( Player& player1,  Player& player2) ; // Сохранение данных двух игроков
    void load(Player& player1, Player& player2) ;            // Загрузка данных двух игроков

    void tmpsave(Player& player1, Player& player2) ;
    void tmpload(Player& player1, Player& player2) ;
    void tmpdel() ;    // Загрузка данных двух игроков

    friend std::ostream& operator<<(std::ostream& out, const GameSave& save);
    friend std::istream& operator>>(std::istream& in, GameSave& save);
};

#endif // GAMESAVE_H
