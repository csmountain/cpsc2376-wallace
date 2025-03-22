// AI Used to help with creating templates, some bug fixes, and comments. UI and large amounts of bugfixing done manually.
#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>

// Plain enum for game status
enum Status
{
    ONGOING,
    PLAYER_1_WINS,
    PLAYER_2_WINS,
    DRAW
};

// Plain enum for player tokens
enum Token
{
    EMPTY,
    PLAYER_1,
    PLAYER_2
};

// Entire game implementation in this class
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
    Token getCurrentPlayer() const; // Added method to get the current player
    bool isColumnFull(int col) const; // New method to check if a column is full
    friend std::ostream &operator<<(std::ostream &os, const Game &game); // Output operator for printing the game board
};

#endif // GAME_H