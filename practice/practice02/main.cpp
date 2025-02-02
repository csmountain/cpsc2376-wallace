// Copilot and AI used in the code for a template. Personal changes, including switch statements to if else statements were made.
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

// Function to read the balance from the file
double readBalanceFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        exit(1);
    }
    double balance;
    file >> balance;
    file.close();
    return balance;
}

// Function to write the balance to the file
void writeBalanceToFile(const std::string &filename, double balance)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        exit(1);
    }
    file << balance;
    file.close();
}

// Function to check the balance
void checkBalance(double balance)
{
    std::cout << "Your current balance is: $" << std::fixed << std::setprecision(2) << balance << std::endl;
}

// Function to deposit money
double deposit(double balance)
{
    double amount;
    std::cout << "Enter deposit amount: ";
    std::cin >> amount;
    if (amount <= 0)
    {
        std::cerr << "Error: Deposit amount must be positive." << std::endl;
        return balance;
    }
    balance += amount;
    std::cout << "Deposit successful. Your new balance is: $" << std::fixed << std::setprecision(2) << balance << std::endl;
    return balance;
}

// Function to withdraw money
double withdraw(double balance)
{
    double amount;
    std::cout << "Enter withdrawal amount: ";
    std::cin >> amount;
    if (amount <= 0)
    {
        std::cerr << "Error: Withdrawal amount must be positive." << std::endl;
        return balance;
    }
    if (amount > balance)
    {
        std::cerr << "Error: Insufficient funds. Your balance is $" << std::fixed << std::setprecision(2) << balance << std::endl;
        return balance;
    }
    balance -= amount;
    std::cout << "Withdrawal successful. Your new balance is: $" << std::fixed << std::setprecision(2) << balance << std::endl;
    return balance;
}

int main()
{
    const std::string filename = "account_balance.txt";
    double balance;

    // Check if the file exists
    std::ifstream file(filename);
    if (!file.is_open())
    {
        // File does not exist, create it and set initial balance to $100.00
        std::cout << "Welcome to Your Bank Account!" << std::endl;
        std::cout << "Initializing account with $100.00..." << std::endl;
        balance = 100.00;
        writeBalanceToFile(filename, balance);
    }
    else
    {
        // File exists, read the current balance
        balance = readBalanceFromFile(filename);
        std::cout << "Welcome to Your Bank Account!" << std::endl;
        std::cout << "Your current balance is: $" << std::fixed << std::setprecision(2) << balance << std::endl;
    }

    while (true)
    {
        std::cout << "\nMenu:\n";
        std::cout << "1. Check Balance\n";
        std::cout << "2. Deposit Money\n";
        std::cout << "3. Withdraw Money\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 1)
        {
            checkBalance(balance);
        }
        else if (choice == 2)
        {
            balance = deposit(balance);
            writeBalanceToFile(filename, balance);
        }
        else if (choice == 3)
        {
            balance = withdraw(balance);
            writeBalanceToFile(filename, balance);
        }
        else if (choice == 4)
        {
            std::cout << "Exiting...\n";
            break;
        }
        else
        {
            std::cerr << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}