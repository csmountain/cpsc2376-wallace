// AI Used to help with creating templates, some bug fixes, and comments. UI and large amounts of bugfixing done manually.
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <limits>
#include <cmath>

template <typename T>
T calculate(T num1, T num2, char &op)
{
    while (true)
    {
        if (op == '+')
        {
            return num1 + num2;
        }
        else if (op == '-')
        {
            return num1 - num2;
        }
        else if (op == '*')
        {
            return num1 * num2;
        }
        else if (op == '/')
        {
            if (num2 != 0)
                return num1 / num2;
            else
            {
                throw std::invalid_argument("\nResult: Division by zero\n");
            }
        }
        else
        {
            std::cerr << "\nError: Invalid operation. Please enter a valid operation \n\n(+, -, *, /): ";
            std::string operation;
            std::getline(std::cin, operation);
            op = operation[0];
        }
    }
}

bool isDouble(const std::string &input)
{
    return input.find('.') != std::string::npos;
}

template <typename T>
T getValidNumber(const std::string &prompt)
{
    T num;
    std::string input;
    while (true)
    {
        std::cout << prompt;
        std::getline(std::cin, input);
        std::istringstream iss(input);
        if (iss >> num)
        {
            return num;
        }
        else
        {
            std::cerr << "\nError: Invalid input. Please enter a valid number." << std::endl;
        }
    }
}

void printResult(double result)
{
    if (result == static_cast<int>(result))
    {
        std::cout << "\nResult: " << static_cast<int>(result) << std::endl;
    }
    else
    {
        std::cout << "\nResult: " << result << std::endl;
    }
}

int main()
{
    std::string input1, input2, operation;
    char op;
    double num1, num2;

    while (true)
    {
        std::cout << "Enter first number: ";
        std::getline(std::cin, input1);
        std::istringstream iss1(input1);
        if (iss1 >> num1)
        {
            break;
        }
        else
        {
            std::cerr << "\nError: Invalid input. Please enter a valid number.\n"
                      << std::endl;
        }
    }

    while (true)
    {
        std::cout << "\nEnter second number: ";
        std::getline(std::cin, input2);
        std::istringstream iss2(input2);
        if (iss2 >> num2)
        {
            break;
        }
        else
        {
            std::cerr << "\nError: Invalid input. Please enter a valid number." << std::endl;
        }
    }

    std::cout << "\nEnter operation (+, -, *, /): ";
    std::getline(std::cin, operation);
    op = operation[0];

    try
    {
        double result = calculate(num1, num2, op);
        printResult(result);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}