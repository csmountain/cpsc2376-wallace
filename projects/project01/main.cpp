#include <iostream>
#include <vector>
#include <limits>

enum class GameState
{
    ONGOING,
    PLAYER_1_WINS,
    PLAYER_2_WINS,
    DRAW
};
enum class Token
{
    EMPTY,
    PLAYER_1,
    PLAYER_2
};

const int ROWS = 6;
const int COLS = 7;

void printRules()
{
    std::cout << "Welcome to Connect Four!\n";
    std::cout << "Players take turns dropping colored discs into a vertical grid.\n";
    std::cout << "The first player to connect four discs in a row (horizontally, vertically, or diagonally) wins.\n";
    std::cout << "If the grid is full and no player has connected four discs, the game is a draw.\n";
}

std::vector<std::vector<Token>> makeBoard()
{
    return std::vector<std::vector<Token>>(ROWS, std::vector<Token>(COLS, Token::EMPTY));
}

void printBoard(const std::vector<std::vector<Token>> &board)
{
    std::cout << " 1 2 3 4 5 6 7\n";
    for (const auto &row : board)
    {
        for (const auto &cell : row)
        {
            char displayChar = ' ';
            if (cell == Token::PLAYER_1)
                displayChar = 'X';
            else if (cell == Token::PLAYER_2)
                displayChar = 'O';
            std::cout << "|" << displayChar;
        }
        std::cout << "|\n";
    }
}

bool dropToken(std::vector<std::vector<Token>> &board, int col, Token token)
{
    if (col < 0 || col >= COLS)
        return false;

    for (int row = ROWS - 1; row >= 0; --row)
    {
        if (board[row][col] == Token::EMPTY)
        {
            board[row][col] = token;
            return true;
        }
    }
    return false;
}

bool checkWin(const std::vector<std::vector<Token>> &board, Token token)
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

GameState gameStatus(const std::vector<std::vector<Token>> &board)
{
    if (checkWin(board, Token::PLAYER_1))
    {
        return GameState::PLAYER_1_WINS;
    }
    if (checkWin(board, Token::PLAYER_2))
    {
        return GameState::PLAYER_2_WINS;
    }

    // Check for draw
    for (const auto &row : board)
    {
        for (const auto &cell : row)
        {
            if (cell == Token::EMPTY)
            {
                return GameState::ONGOING;
            }
        }
    }

    return GameState::DRAW;
}

void play(std::vector<std::vector<Token>> &board)
{
    Token currentPlayer = Token::PLAYER_1;
    while (true)
    {
        printBoard(board);
        int col;
        std::cout << "Player " << (currentPlayer == Token::PLAYER_1 ? "1 (X)" : "2 (O)") << ", enter column (1-7): ";
        std::cin >> col;
        if (std::cin.fail() || col < 1 || col > 7 || !dropToken(board, col - 1, currentPlayer))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again.\n";
            continue;
        }

        GameState state = gameStatus(board);
        if (state != GameState::ONGOING)
        {
            printBoard(board);
            if (state == GameState::PLAYER_1_WINS)
            {
                std::cout << "Player 1 (X) wins!\n";
            }
            else if (state == GameState::PLAYER_2_WINS)
            {
                std::cout << "Player 2 (O) wins!\n";
            }
            else if (state == GameState::DRAW)
            {
                std::cout << "The game is a draw!\n";
            }
            break;
        }

        currentPlayer = (currentPlayer == Token::PLAYER_1) ? Token::PLAYER_2 : Token::PLAYER_1;
    }
}

int main()
{
    printRules();
    std::cout << "Ready to play? Press y to start: ";
    char startResponse;
    std::cin >> startResponse;

    if (startResponse == 'y' || startResponse == 'Y')
    {
        bool playAgain = true;
        while (playAgain)
        {
            auto board = makeBoard();
            GameState state = GameState::ONGOING;
            while (state == GameState::ONGOING)
            {
                play(board);
                state = gameStatus(board);
            }
            // Handle end of game and ask if the user wants to play again
            std::cout << "Do you want to play again? (y/n): ";
            char response;
            std::cin >> response;
            playAgain = (response == 'y' || response == 'Y');
        }
    }
    return 0;
}