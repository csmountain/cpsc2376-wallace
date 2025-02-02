// Copilot and AI used in the code for a template
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


}