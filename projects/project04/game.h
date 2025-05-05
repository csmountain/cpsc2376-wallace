// AI Used to help with creating templates, some bug fixes, and comments. UI and large amounts of bugfixing done manually.
#pragma once

#include <vector>
#include <SDL2/SDL.h>

// Enums for game tokens and status
enum Token
{
    EMPTY,
    PLAYER_1,
    PLAYER_2
};
enum Status
{
    ONGOING,
    PLAYER_1_WINS,
    PLAYER_2_WINS,
    DRAW
};

class Game
{
public:
    static const int ROWS = 6;
    static const int COLS = 7;

    Game();
    void play(int col);
    Status status() const;
    Token getCurrentPlayer() const;
    bool isColumnFull(int col) const;

    // New method for rendering the game
    void draw(SDL_Renderer *renderer) const;

private:
    std::vector<std::vector<Token>> board;
    Token currentPlayer;

    bool checkWin(Token token) const;
};