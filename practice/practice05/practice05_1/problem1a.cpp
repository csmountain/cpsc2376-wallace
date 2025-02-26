// AI Used to help with creating templates, some bug fixes, and comments. UI and large amounts of bugfixing done manually.
#include <iostream>
#include <vector>
#include <limits>
#include <iterator>
#include <sstream> 

int main()
{
    std::vector<int> numbers;
    std::string input;
    int number;
    int count = 1;

    while (true)
    {
        std::cout << "Integer " << count << " (press any non-numerical key and enter to stop the program): ";
        std::getline(std::cin, input);
        std::stringstream ss(input);

        if (ss >> number && ss.eof())
        {
            numbers.push_back(number);
            count++;
            std::cout << "\n";
        }
        else if (input.find('.') != std::string::npos)
        {
            std::cout << "\n***Error: Please enter a valid integer.***\n\n";
        }
        else
        {
            break;
        }
    }

    // Prints the numbers using iterators
    std::cout << "\nYou entered: ";
    for (auto it = numbers.begin(); it != numbers.end(); ++it)
    {
        std::cout << *it;
        if (std::next(it) != numbers.end())
        {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

    // Prints sum using an iterator loop
    int sumEven = 0;
    for (auto it = numbers.begin(); it != numbers.end(); ++it)
    {
        if (*it % 2 == 0)
        {
            sumEven += *it;
        }
    }
    std::cout << "\nSum of even numbers: " << sumEven << std::endl;

    return 0;
}