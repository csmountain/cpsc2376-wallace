#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <sstream> // For std::stringstream

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
            std::cout << "Error: Please enter a valid integer.\n";
        }
        else
        {
            break;
        }
    }

    // Print the numbers in the same order
    std::cout << "You entered: ";
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

    // Calculate the product of all elements in the vector using long long
    long long product = std::accumulate(numbers.begin(), numbers.end(), 1LL, std::multiplies<long long>());

    // Print the results
    std::cout << "\nSum of all elements: " << sum << std::endl;
    std::cout << "\nProduct of all elements: " << product << std::endl;

    return 0;
}