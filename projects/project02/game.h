#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>

enum Status
{
    ONGOING,
    PLAYER_1_WINS,
    PLAYER_2_WINS,
    DRAW
};

enum Token
{
    EMPTY,
    PLAYER_1,
    PLAYER_2
};

class Game
{
private:
    static const int ROWS = 6;
    static const int COLS = 7;
    std::vector<std::vector<Token>> board;
    Token currentPlayer;

    bool checkWin(Token token) const;

public:
    Game();
    void play(int col);
    Status status() const;
    friend std::ostream &operator<<(std::ostream &os, const Game &game);
};

#endif // GAME_H