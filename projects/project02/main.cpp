#include "game.h"
#include "game.cpp"
#include <iostream>
#include <limits>

void printRules()
{
    std::cout << "Welcome to Connect Four!\n\n";
    std::cout << "-- Two players will take turns dropping their pieces into a 7x6 grid. You are either team X's or team O's.\n";
    std::cout << "-- The first player to connect four of their shape in a row (horizontally, vertically, or diagonally) wins.\n";
    std::cout << "-- If the grid is full and no player has connected four pieces, the game is a draw. Have fun playing!\n";
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
        Game game;
        while (game.status() == ONGOING)
        {
            std::cout << game;
            int col;
            std::cout << "\nEnter column (1-7): ";
            std::cin >> col;

            if (std::cin.fail() || col < 1 || col > 7)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\nInvalid input. Please try again.\n";
                continue;
            }

            game.play(col - 1);
        }

        std::cout << game;
        Status result = game.status();
        if (result == PLAYER_1_WINS)
            std::cout << "\nPlayer 1 (X) wins!\n";
        else if (result == PLAYER_2_WINS)
            std::cout << "\nPlayer 2 (O) wins!\n";
        else if (result == DRAW)
            std::cout << "\nThe game is a draw!\n";

        char response;
        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> response;
        playAgain = (response == 'y' || response == 'Y');
    }

    std::cout << "\nThanks for playing!\n";
    return 0;
}