#include <iostream>
#include <vector>

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

void play(std::vector<std::vector<Token>> &board)
{
    // Implement turn logic here
}

GameState gameStatus(const std::vector<std::vector<Token>> &board)
{
    // Implement game status check here
    return GameState::ONGOING;
}

int main()
{
    printRules();
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
    return 0;
}