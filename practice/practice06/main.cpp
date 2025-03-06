// AI Used to help with creating templates, some bug fixes, and comments. UI and large amounts of bugfixing done manually.
#include <iostream>
#include <limits>
#include <sstream>
#include "Fraction.h"
#include "Fraction.cpp"
#include "MixedFraction.h"
#include "MixedFraction.cpp"

void displayMenu() // Function to display the menu
{
    std::cout << "\nFraction Options:\n";
    std::cout << "\n1. Enter a fraction manually\n";
    std::cout << "2. Add a fraction\n";
    std::cout << "3. Subtract a fraction\n";
    std::cout << "4. Multiply by a fraction\n";
    std::cout << "5. Divide by a fraction\n";
    std::cout << "6. Display as Mixed Fraction\n";
    std::cout << "7. Clear Fraction\n";
    std::cout << "8. Exit\n";
    std::cout << "\nChoose an option: ";
}

Fraction enterFraction()
{
    int num, denom;
    std::string input;
    while (true)
    {
        std::cout << "\nEnter numerator: ";
        std::getline(std::cin, input);
        std::stringstream ss(input); // stringstream used to check if input is an integer
        if (ss >> num && ss.eof())
        {
            std::cout << std::endl;
            break;
        }
        std::cout << "\nInvalid input. Please enter an integer.\n";
    }
    while (true)
    {
        std::cout << "Enter denominator: ";
        std::getline(std::cin, input);
        std::stringstream ss(input); // stringstream used to check if input is an integer
        if (ss >> denom && ss.eof())
        {
            std::cout << std::endl;
            break;
        }
        std::cout << "\nInvalid input. Please enter an integer.\n\n";
    }

    return Fraction(num, denom);
}

int getMenuChoice()
{
    int choice;
    std::string input;
    while (true)
    {
        std::getline(std::cin, input);
        std::stringstream ss(input);
        if (ss >> choice && ss.eof())
        {
            break;
        }
        std::cout << "\nInvalid option. Please enter an integer between 1 and 8.\n\nChoose an option: ";
    }
    return choice;
}

int main()
{
    Fraction currentFraction;
    int choice;

    while (true)
    {
        std::cout << "Current Fraction: " << currentFraction << "\n";
        displayMenu();
        choice = getMenuChoice();

        try
        {
            if (choice == 1)
            {
                currentFraction = enterFraction();
                std::cout << "--------------------------------------------------------------------\n";
            }
            else if (choice == 2)
            {
                currentFraction = currentFraction + enterFraction();
                std::cout << "--------------------------------------------------------------------\n";
            }
            else if (choice == 3)
            {
                currentFraction = currentFraction - enterFraction();
                std::cout << "--------------------------------------------------------------------\n";
            }
            else if (choice == 4)
            {
                currentFraction = currentFraction * enterFraction();
                std::cout << "--------------------------------------------------------------------\n";
            }
            else if (choice == 5)
            {
                currentFraction = currentFraction / enterFraction();
                std::cout << "--------------------------------------------------------------------\n";
            }
            else if (choice == 6)
            {
                MixedFraction mixed(currentFraction);
                std::cout << "\nMixed Fraction: " << mixed << "\n\n";
                std::cout << "--------------------------------------------------------------------\n";
            }
            else if (choice == 7)
            {
                std::cout << "\n--------------------------------------------------------------------\n";
                currentFraction = Fraction();
            }
            else if (choice == 8)
            {
                std::cout << "\nExiting...\n";
                break;
            }
            else
            {
                std::cout << "\nInvalid option. Please enter an integer between 1 and 8.\n\n";
            }
        }
        catch (const std::invalid_argument &e) // Catch invalid_argument exceptions
        {
            std::cerr << "Error: " << e.what() << std::endl;
            std::cout << "\n--------------------------------------------------------------------\n";
        }
    }

    return 0;
}