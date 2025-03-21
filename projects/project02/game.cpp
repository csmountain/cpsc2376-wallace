#include "game.h"

Game::Game() : board(ROWS, std::vector<Token>(COLS, EMPTY)), currentPlayer(PLAYER_1) {}

void Game::play(int col)
{
    if (col < 0 || col >= COLS)
        return;

    for (int row = ROWS - 1; row >= 0; --row)
    {
        if (board[row][col] == EMPTY)
        {
            board[row][col] = currentPlayer;
            currentPlayer = (currentPlayer == PLAYER_1) ? PLAYER_2 : PLAYER_1;
            return;
        }
    }
}

bool Game::checkWin(Token token) const
{
    // Check horizontal
    for (int row = 0; row < ROWS; ++row)
    {
        for (int col = 0; col < COLS - 3; ++col)
        {
            if (board[row][col] == token && board[row][col + 1] == token &&
                board[row][col + 2] == token && board[row][col + 3] == token)
            {
                return true;
            }
        }
    }

    // Check vertical
    for (int col = 0; col < COLS; ++col)
    {
        for (int row = 0; row < ROWS - 3; ++row)
        {
            if (board[row][col] == token && board[row + 1][col] == token &&
                board[row + 2][col] == token && board[row + 3][col] == token)
            {
                return true;
            }
        }
    }

    // Check diagonal (bottom-left to top-right)
    for (int row = 3; row < ROWS; ++row)
    {
        for (int col = 0; col < COLS - 3; ++col)
        {
            if (board[row][col] == token && board[row - 1][col + 1] == token &&
                board[row - 2][col + 2] == token && board[row - 3][col + 3] == token)
            {
                return true;
            }
        }
    }

    // Check diagonal (top-left to bottom-right)
    for (int row = 0; row < ROWS - 3; ++row)
    {
        for (int col = 0; col < COLS - 3; ++col)
        {
            if (board[row][col] == token && board[row + 1][col + 1] == token &&
                board[row + 2][col + 2] == token && board[row + 3][col + 3] == token)
            {
                return true;
            }
        }
    }

    return false;
}

Status Game::status() const
{
    if (checkWin(PLAYER_1))
        return PLAYER_1_WINS;
    if (checkWin(PLAYER_2))
        return PLAYER_2_WINS;

    for (const auto &row : board)
    {
        for (const auto &cell : row)
        {
            if (cell == EMPTY)
                return ONGOING;
        }
    }

    return DRAW;
}

std::ostream &operator<<(std::ostream &os, const Game &game)
{
    os << "-------------------------------------------\n";
    os << "   1     2     3     4     5     6     7\n";
    os << "___________________________________________\n";
    for (const auto &row : game.board)
    {
        os << "|     |     |     |     |     |     |     |\n";
        for (const auto &cell : row)
        {
            char displayChar = ' ';
            if (cell == PLAYER_1)
                displayChar = 'X';
            else if (cell == PLAYER_2)
                displayChar = 'O';
            os << "|  " << displayChar << "  ";
        }
        os << "|\n";
        os << "|_____|_____|_____|_____|_____|_____|_____|\n";
    }
    os << "   1     2     3     4     5     6     7\n";
    os << "-------------------------------------------\n";
    return os;
}