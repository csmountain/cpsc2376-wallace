// Same code used as in Project 1 modified to use game.h and game.cpp, meaning little bugfixing was needed after plugging in the old values to the template.
// AI Used to help with creating templates, some bug fixes, and comments. UI and large amounts of bugfixing done manually.
#include "game.cpp"
#include "game.h"
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

            // Display the current player's turn
            Token currentPlayer = game.getCurrentPlayer();
            std::cout << "\nPlayer " << (currentPlayer == PLAYER_1 ? "1 (X)" : "2 (O)") << ", enter column (1-7): ";

            int col;
            std::cin >> col;
            std::cout << "\n";


            if (std::cin.fail() || std::cin.peek() != '\n' || !(col == 1 || col == 2 || col == 3 || col == 4 || col == 5 || col == 6 || col == 7))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\nInvalid input. Please enter an integer between 1 and 7.\n\n";
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Check if the column is full
            if (game.isColumnFull(col - 1))
            {
                std::cout << "\nColumn " << col << " is full. Please choose a different column.\n\n";
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
        while (true)
        {
            std::cout << "\nDo you want to play again? (y/n): ";
            std::cin >> response;

            if (std::cin.fail() || std::cin.peek() != '\n')
            {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nInvalid input. Please enter 'y' for yes or 'n' for no.\n";
            continue;
            }

            if (response == 'y' || response == 'Y')
            {
            playAgain = true;
            std::cout << "\nNew game started!\n\n";
            break;
            }
            else if (response == 'n' || response == 'N')
            {
            playAgain = false;
            std::cout << "\nThanks for playing!\n\n";
            break; // Exit the replay loop
            }
            else
            {
            std::cout << "\nInvalid input. Please enter 'y' for yes or 'n' for no.\n";
            }
        }

    }
    return 0;
}