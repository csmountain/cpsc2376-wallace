#include <iostream>
#include <vector>
#include <numeric>   // For std::accumulate
#include <algorithm> // For std::for_each
#include <limits>

int main()
{
    std::vector<int> numbers;
    int number;
    int count = 1;
    const int maxCount = 5;

    while (count <= maxCount)
    {
        std::cout << "Integer " << count << " out of " << maxCount << " (press any non-numerical key and enter to stop the program): ";
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

    // Clear the error state caused by non-integer input
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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

    // Use std::for_each with a lambda function to print each element squared
    std::cout << "Squared values: ";
    std::for_each(numbers.begin(), numbers.end(), [](int n)
    {
        std::cout << static_cast<long long>(n) * n << " ";
    });
    std::cout << std::endl;

    // Use a lambda function with std::accumulate to sum up all squared values
    long long sumOfSquares = std::accumulate(numbers.begin(), numbers.end(), 0LL, [](long long sum, int n)
    {
        return sum + static_cast<long long>(n) * n;
    });

    // Print the result
    std::cout << "Sum of squared values: " << sumOfSquares << std::endl;

    return 0;
}