#include <iostream>
#include <vector>
#include <numeric>

void printMenu()
{
    std::cout << "Menu:\n";
    std::cout << "1. Add item to vector\n";
    std::cout << "2. Print vector\n";
    std::cout << "3. Double the vector\n";
    std::cout << "4. Find the sum\n";
    std::cout << "5. Print multiples of a value\n";
    std::cout << "6. Exit\n";
}

void addItem(std::vector<int> &vec)
{
    int item;
    std::cout << "Enter item to add: ";
    std::cin >> item;
    vec.push_back(item);
}

void printVector(const std::vector<int> &vec)
{
    std::cout << "Vector: ";
    for (int item : vec)
    {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void doubleVector(std::vector<int> &vec)
{
    for (int &item : vec)
    {
        item *= 2;
    }
}

void findSum(const std::vector<int> &vec)
{
    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    std::cout << "Sum: " << sum << std::endl;
}

void printMultiples(const std::vector<int> &vec)
{
    int value;
    std::cout << "Enter value to find multiples of: ";
    std::cin >> value;
    std::cout << "Multiples of " << value << ": ";
    for (int item : vec)
    {
        if (item % value == 0)
        {
            std::cout << item << " ";
        }
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> vec;
    int choice;

    while (true)
    {
        printMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1)
        {
            addItem(vec);
        }
        else if (choice == 2)
        {
            printVector(vec);
        }
        else if (choice == 3)
        {
            doubleVector(vec);
        }
        else if (choice == 4)
        {
            findSum(vec);
        }
        else if (choice == 5)
        {
            printMultiples(vec);
        }
        else if (choice == 6)
        {
            std::cout << "Exiting...\n";
            break;
        }
        else
        {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}