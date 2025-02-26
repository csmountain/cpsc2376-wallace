// AI Used to help with creating templates, some bug fixes, and comments. UI and large amounts of bugfixing done manually.
#include <iostream>
#include <vector>
#include <numeric>   
#include <algorithm> 
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

    // Print the numbers in the same order
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

    // Use std::for_each with a lambda function to print each element squared
    std::cout << "\nSquared values: ";
    std::for_each(numbers.begin(), numbers.end(), [](int n)
        { std::cout << static_cast<long long>(n) * n << " "; });
    std::cout << std::endl;

    // Use a lambda function with std::accumulate to sum up all squared values
    long long sumOfSquares = std::accumulate(numbers.begin(), numbers.end(), 0LL, [](long long sum, int n)
        { return sum + static_cast<long long>(n) * n; });

    // Print the result
    std::cout << "\nSum of squared values: " << sumOfSquares << std::endl;

    return 0;
}