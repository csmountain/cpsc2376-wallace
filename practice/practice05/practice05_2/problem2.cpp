#include <iostream>
#include <vector>
#include <numeric> // For std::accumulate
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

    // Calculate the sum of all elements in the vector
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);

    // Calculate the product of all elements in the vector
    int product = std::accumulate(numbers.begin(), numbers.end(), 1, std::multiplies<int>());

    // Print the results
    std::cout << "Sum of all elements: " << sum << std::endl;
    std::cout << "Product of all elements: " << product << std::endl;

    return 0;
}