//AI used to help with templating and game logic. Manual testing was done to ensure the game works as intended. Bugfixing and UI was also all done by me.
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
    std::cout << "Welcome to Connect Four!\n\n";
    std::cout << "-- Two players will take turns dropping their pieces into a 7x6 grid. You are either team X's or team O's.\n";
    std::cout << "-- The first player to connect four of their shape in a row (horizontally, vertically, or diagonally) wins.\n";
    std::cout << "-- If the grid is full and no player has connected four pieces, the game is a draw. Have fun playing!\n";
}

std::vector<std::vector<Token>> makeBoard()
{
    return std::vector<std::vector<Token>>(ROWS, std::vector<Token>(COLS, Token::EMPTY));
}

void printBoard(const std::vector<std::vector<Token>> &board)
{
    std::cout << "-------------------------------------------";
    std::cout << "\n   1     2     3     4     5     6     7\n";
    std::cout << "___________________________________________\n";
    for (const auto &row : board)
    {
        std::cout << "|     |     |     |     |     |     |     |\n";
        for (const auto &cell : row)
        {
            char displayChar = ' ';
            if (cell == Token::PLAYER_1)
                displayChar = 'X';
            else if (cell == Token::PLAYER_2)
                displayChar = 'O';
            std::cout << "|  " << displayChar << "  ";
        }
        std::cout << "|\n";
        std::cout << "|_____|_____|_____|_____|_____|_____|_____|\n";
    }
    std::cout << "\n   1     2     3     4     5     6     7\n";
    std::cout << "-------------------------------------------\n";
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
        std::cout << "\nPlayer " << (currentPlayer == Token::PLAYER_1 ? "1 (X)" : "2 (O)") << ", enter column (1-7): ";
        std::cin >> col;
        if (std::cin.fail() || col < 1 || col > 7 || std::cin.peek() != '\n' || !dropToken(board, col - 1, currentPlayer))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n-------------------------------------------\n\nInvalid input. Please try again.\n\n";
            continue;
        }
        std::cout << "\n";

        GameState state = gameStatus(board);
        if (state != GameState::ONGOING)
        {
            printBoard(board);
            if (state == GameState::PLAYER_1_WINS)
            {
                std::cout << "\nPlayer 1 (X) wins!\n\n-------------------------------------------\n\n";
            }
            else if (state == GameState::PLAYER_2_WINS)
            {
                std::cout << "\nPlayer 2 (O) wins!\n\n-------------------------------------------\n\n";
            }
            else if (state == GameState::DRAW)
            {
                std::cout << "\nThe game is a draw!\n\n-------------------------------------------\n\n";
            }
            break;
        }

        currentPlayer = (currentPlayer == Token::PLAYER_1) ? Token::PLAYER_2 : Token::PLAYER_1;
    }
}

int main()
{
    printRules();
    std::cout << "\nReady to play? Press and enter anything to start: ";
    std::cin.get();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n";

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
        char response;
        bool validResponse = false;
        while (!validResponse)
        {
            std::cout << "Do you want to play again? (y/n): ";
            std::cin >> response;
            if (std::cin.fail() || std::cin.peek() != '\n')
            {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n-------------------------------------------\n";
            std::cout << "\nInvalid input. Please enter 'y' or 'n'.\n\n";
            std::cout << "-------------------------------------------\n\n";
            continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (response == 'y' || response == 'Y' || response == 'n' || response == 'N')
            {
            validResponse = true;
            playAgain = (response == 'y' || response == 'Y');
            if (!playAgain)
            {
                std::cout << "\n-------------------------------------------\n";
                std::cout << "\nThanks for playing!\n\n";
                std::cout << "-------------------------------------------\n\n";
            }
            }
            else
            {
            std::cout << "\n-------------------------------------------\n";
            std::cout << "\nInvalid input. Please enter 'y' or 'n'.\n\n";
            std::cout << "-------------------------------------------\n\n";
            }
        }
        if (playAgain)
        {
            std::cout << "\n";
        }
        }
    return 0;
}