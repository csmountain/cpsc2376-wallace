#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <sstream>

double convertTemperature(double temp, char scale = 'F')
{
    if (scale == 'F')
    {
        return (temp * 9.0 / 5.0) + 32.0; // Celsius to Fahrenheit
    }
    else if (scale == 'C')
    {
        return (temp - 32.0) * 5.0 / 9.0; // Fahrenheit to Celsius
    }
    else
    {
        std::cerr << "Invalid scale provided." << std::endl;
        return temp;
    }
}

void displayMenu()
{
    std::cout << "1. Convert Celsius to Fahrenheit" << std::endl;
    std::cout << "2. Convert Fahrenheit to Celsius" << std::endl;
    std::cout << "Choose an option: ";
}

int main()
{
    int option;
    double temperature;
    char scale;
    std::string input;

    while (true)
    {
        displayMenu();
        std::getline(std::cin, input);
        std::stringstream(input) >> option;

        if (option == 1)
        {
            scale = 'F';
            std::cout << "Enter temperature in Celsius: ";
            break;
        }
        else if (option == 2)
        {
            scale = 'C';
            std::cout << "Enter temperature in Fahrenheit: ";
            break;
        }
        else
        {
            std::cerr << "\nInvalid option selected. Please try again.\n"
                      << std::endl;
        }
    }

    while (true)
    {
        std::cin >> input;
        std::stringstream ss(input);
        if (ss >> temperature)
        {
            break;
        }
        else
        {
            std::cerr << "Invalid temperature input. Please enter a valid number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    double convertedTemp = convertTemperature(temperature, scale);

    if (scale == 'F')
    {
        std::cout << "Converted: " << std::fixed << std::setprecision(2) << convertedTemp << "°F" << std::endl;
    }
    else if (scale == 'C')
    {
        std::cout << "Converted: " << std::fixed << std::setprecision(2) << convertedTemp << "°C" << std::endl;
    }

    return 0;
}