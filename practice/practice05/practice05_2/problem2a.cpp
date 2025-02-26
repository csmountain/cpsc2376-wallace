// AI Used to help with creating templates, some bug fixes, and comments. UI and large amounts of bugfixing done manually.
#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <sstream> 

int main()
{
    std::vector<int> numbers;
    std::string input;
    int number;
    int count = 1;
    const int maxCount = 5;

    while (count <= maxCount)
    {
        std::cout << "Integer " << count << " out of " << maxCount << " (press any non-numerical key and enter to stop the program): ";
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

    // Prints numbers in the same order
    std::cout << "\nYou entered: ";
    for (size_t i = 0; i < numbers.size(); ++i)
    {
        std::cout << numbers[i];
        if (i != numbers.size() - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

    // Calculates sum of all elements in the vector
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);

    // Calculates product of all elements in the vector 
    long long product = std::accumulate(numbers.begin(), numbers.end(), 1LL, std::multiplies<long long>());

    // Print the results
    std::cout << "\nSum of all elements: " << sum << std::endl;
    std::cout << "\nProduct of all elements: " << product << std::endl;

    return 0;
}