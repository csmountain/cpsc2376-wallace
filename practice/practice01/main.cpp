#include <iostream>
#include <vector>
#include <numeric>
#include <limits>

// Function to print the menu
void printMenu()
{
    std::cout << "----------------------------------------------------------\n";
    std::cout << "Menu:\n";
    std::cout << "1. Add item to vector\n";
    std::cout << "2. Print vector\n";
    std::cout << "3. Double the vector\n";
    std::cout << "4. Find the sum\n";
    std::cout << "5. Print multiples of a value\n";
    std::cout << "6. Exit\n";
}

// Function to add an item to the vector
void addItem(std::vector<int>& vec)
{
    int item;
    std::cout << "Enter item to add: ";
    while (!(std::cin >> item)) {
        std::cin.clear(); // clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
        std::cout << "Invalid input. Please enter a number: ";
    }
    std::cout << "\nAdding " << item << " to the vector.\n";
    vec.push_back(item);
}

// Function to print the vector
void printVector(const std::vector<int> &vec)
{
    std::cout << "\nVector: ";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec.at(i) << " ";
    }
    std::cout << std::endl;
}

// Function to double the values in the vector
void doubleVector(std::vector<int> &vec)
{
    for (size_t i = 0; i < vec.size(); ++i)
    {
        vec.at(i) *= 2;
        std::cout << "\nDoubling vector(s)!";
    }
}

// Function to find the sum of the vector elements
void findSum(const std::vector<int> &vec)
{
    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    std::cout << "\nSum: " << sum << std::endl;
}

// Function to print multiples of a user-defined value
void printMultiples(const std::vector<int> &vec)
{ 
    int value;
    std::cout << "Enter value to find multiples of: ";
    std::cin >> value;
    std::cout << "\nMultiples of " << value << ": ";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (vec.at(i) % value == 0)
        {
            std::cout << vec.at(i) << " ";
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