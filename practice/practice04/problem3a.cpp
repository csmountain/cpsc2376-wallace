// AI Used to help with creating templates, some bug fixes, and comments. UI and large amounts of bugfixing done manually.
#include <iostream>
#include <list>
#include <string>
#include <limits>
#include <sstream>

void displayMenu()
{
    std::cout << "1. Add Task" << std::endl;
    std::cout << "2. Remove Task" << std::endl;
    std::cout << "3. Show Tasks" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "\nChoice: ";
}

void addTask(std::list<std::string> &tasks)
{
    std::string task;
    std::cout << "\nEnter task: ";
    std::getline(std::cin, task);
    tasks.push_back(task);
    std::cout << "\nTask added!\n" << std::endl;
}

void removeTask(std::list<std::string> &tasks)
{
    if (tasks.empty())
    {
        std::cerr << "\nNo tasks available to remove.\n" << std::endl;
        return;
    }

    std::string input;
    int taskNumber;
    while (true)
    {
        std::cout << "\nEnter task number to remove: ";
        std::getline(std::cin, input);
        std::istringstream iss(input);
        if (iss >> taskNumber && iss.eof() && taskNumber > 0 && taskNumber <= tasks.size())
        {
            auto it = tasks.begin();
            std::advance(it, taskNumber - 1);
            tasks.erase(it);
            std::cout << "\nTask removed!\n" << std::endl;
            break;
        }
        else
        {
            std::cerr << "\nInvalid task number! Please try again." << std::endl;
        }
    }
}

void showTasks(const std::list<std::string> &tasks)
{
    std::cout << "\nTasks:" << std::endl;
    if (tasks.empty())
    {
        std::cout << "\nNo tasks available.\n" << std::endl;
    }
    else
    {
        int taskNumber = 1;
        for (const auto &task : tasks)
        {
            std::cout << "\nTask " << taskNumber << ". " << task << "\n" << std::endl;
            ++taskNumber;
        }
    }
}

int main()
{
    std::list<std::string> tasks;
    int choice;
    std::string input;

    while (true)
    {
        displayMenu();
        std::getline(std::cin, input);
        std::istringstream iss(input);
        if (iss >> choice && iss.eof())
        {
            if (choice == 1)
            {
                addTask(tasks);
            }
            else if (choice == 2)
            {
                removeTask(tasks);
            }
            else if (choice == 3)
            {
                showTasks(tasks);
            }
            else if (choice == 4)
            {
                std::cout << "Exiting..." << std::endl;
                break;
            }
            else
            {
                std::cerr << "\nInvalid input! Please enter a valid choice.\n" << std::endl;
            }
        }
        else
        {
            std::cerr << "\nInvalid input! Please enter a valid choice.\n" << std::endl;
        }
    }

    return 0;
}