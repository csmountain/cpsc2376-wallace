#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <limits>
#include <cmath>

template <typename T>
T calculate(T num1, T num2, char op)
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
            std::cerr << "Error: Division by zero." << std::endl;
            throw std::invalid_argument("Division by zero");
        }
    }
    else
    {
        std::cerr << "Error: Invalid operation." << std::endl;
        throw std::invalid_argument("Invalid operation");
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
            std::cerr << "Invalid input. Please enter a valid number." << std::endl;
        }
    }
}

void printResult(double result)
{
    if (result == static_cast<int>(result))
    {
        std::cout << "Result: " << static_cast<int>(result) << std::endl;
    }
    else
    {
        std::cout << "Result: " << result << std::endl;
    }
}

int main()
{
    std::string input1, input2, operation;
    char op;

    std::cout << "Enter first number: ";
    std::getline(std::cin, input1);
    std::cout << "Enter second number: ";
    std::getline(std::cin, input2);
    std::cout << "Enter operation (+, -, *, /): ";
    std::getline(std::cin, operation);
    op = operation[0];

    double num1, num2;

    if (isDouble(input1))
    {
        num1 = std::stod(input1);
    }
    else
    {
        num1 = static_cast<double>(std::stoi(input1));
    }

    if (isDouble(input2))
    {
        num2 = std::stod(input2);
    }
    else
    {
        num2 = static_cast<double>(std::stoi(input2));
    }

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