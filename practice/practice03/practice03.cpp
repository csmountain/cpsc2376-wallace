// Fixed Code. AI was used to help with formatting, finding std::invalid argument fixes during unit testing.

#include <iostream>
#include <vector>

class MathUtils
{
public:
    static int sumRange(int start, int end)
    {
        int sum = 0;
        for (int i = start; i <= end; i++) // Fix includes '=' now
        { 
            sum += i;
        }
        return sum;
    }

    static bool containsNegative(const std::vector<int> &numbers)
    {
        for (size_t i = 0; i < numbers.size(); i++) // Fixed it to correct loop condition
        { 
            if (numbers[i] < 0) // Fix: Checks for negative numbers now
            { 
                return true;
            }
        }
        return false;
    }

    static int findMax(const std::vector<int> &numbers)
    {
        if (numbers.empty())
            throw std::invalid_argument("Cannot find max of an empty vector."); // Fixed to where it correctly returns that it is invalid.
        int maxVal = numbers[0];
        for (size_t i = 1; i < numbers.size(); i++) // Fixed it to correct loop condition
        { 
            if (numbers[i] > maxVal) // Fixes: Correct comparison
            { 
                maxVal = numbers[i];
            }
        }
        return maxVal;
    }
};

int main()
{
    std::cout << "Sum from 1 to 5: " << MathUtils::sumRange(1, 5) << std::endl;
    std::vector<int> values = {3, -1, 5, 7};
    std::cout << "Contains negative? " << MathUtils::containsNegative(values) << std::endl;
    std::cout << "Max value: " << MathUtils::findMax(values) << std::endl;
    return 0;
}