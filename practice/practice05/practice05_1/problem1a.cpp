#include <iostream>
#include <vector>
#include <limits>
#include <iterator>

int main()
{
    std::vector<int> numbers;
    int number;
    int count = 1;

    while (true)
    {
        std::cout << "Integer " << count << " (press any non-numerical key and enter to stop the program): ";
        if (std::cin >> number)
        {
            numbers.push_back(number);
            count++;
            std::cout << "\n";
        }
        else
        {
            break;
        }
    }

    // Clear the error state
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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