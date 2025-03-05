#include <iostream>
#include <limits>
#include <sstream>
#include "Fraction.h"
#include "Fraction.cpp"
#include "MixedFraction.h"
#include "MixedFraction.cpp"

void displayMenu()
{
    std::cout << "\nOptions:\n";
    std::cout << "1. Enter a fraction manually\n";
    std::cout << "2. Add a fraction\n";
    std::cout << "3. Subtract a fraction\n";
    std::cout << "4. Multiply by a fraction\n";
    std::cout << "5. Divide by a fraction\n";
    std::cout << "6. Display as Mixed Fraction\n";
    std::cout << "7. Clear Fraction\n";
    std::cout << "8. Exit\n";
    std::cout << "Choose an option: ";
}

Fraction enterFraction()
{
    int num, denom;
    std::string input;
    while (true)
    {
        std::cout << "Enter numerator: ";
        std::getline(std::cin, input);
        std::stringstream ss(input);
        if (ss >> num && ss.eof())
        {
            break;
        }
        std::cout << "Invalid input. Please enter an integer.\n";
    }
    while (true)
    {
        std::cout << "Enter denominator: ";
        std::getline(std::cin, input);
        std::stringstream ss(input);
        if (ss >> denom && ss.eof())
        {
            break;
        }
        std::cout << "Invalid input. Please enter an integer.\n";
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
        std::cout << "Invalid option. Please enter an integer between 1 and 8.\n";
    }
    return choice;
}

int main()
{
    Fraction currentFraction;
    int choice;

    while (true)
    {
        std::cout << "\nCurrent Fraction: " << currentFraction << "\n";
        displayMenu();
        choice = getMenuChoice();

        try
        {
            if (choice == 1)
            {
                currentFraction = enterFraction();
            }
            else if (choice == 2)
            {
                currentFraction = currentFraction + enterFraction();
            }
            else if (choice == 3)
            {
                currentFraction = currentFraction - enterFraction();
            }
            else if (choice == 4)
            {
                currentFraction = currentFraction * enterFraction();
            }
            else if (choice == 5)
            {
                currentFraction = currentFraction / enterFraction();
            }
            else if (choice == 6)
            {
                MixedFraction mixed(currentFraction);
                std::cout << "Mixed Fraction: " << mixed << "\n";
            }
            else if (choice == 7)
            {
                currentFraction = Fraction();
            }
            else if (choice == 8)
            {
                std::cout << "Exiting...\n";
                break;
            }
            else
            {
                std::cout << "Invalid option. Please enter an integer between 1 and 8.\n";
            }
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}