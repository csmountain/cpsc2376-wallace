#include <iostream>
#include <iomanip>
#include <limits>

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

    while (true)
    {
        displayMenu();
        std::cin >> option;

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
            std::cerr << "\nInvalid option selected. Please try again." << std::endl;
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
        }
    }

    std::cin >> temperature;
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