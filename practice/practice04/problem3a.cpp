#include <iostream>
#include <list>
#include <string>
#include <limits>
#include <sstream>

void displayMenu()
{
    std::cout << "\n1. Add Task" << std::endl;
    std::cout << "2. Remove Task" << std::endl;
    std::cout << "3. Show Tasks" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Choice: ";
}

void addTask(std::list<std::string> &tasks)
{
    std::string task;
    std::cout << "\nEnter task: ";
    std::getline(std::cin, task);
    tasks.push_back(task);
    std::cout << "Task added!" << std::endl;
}

void removeTask(std::list<std::string> &tasks)
{
    int taskNumber;
    std::cout << "\nEnter task number to remove: ";
    std::cin >> taskNumber;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (taskNumber > 0 && taskNumber <= tasks.size())
    {
        auto it = tasks.begin();
        std::advance(it, taskNumber - 1);
        tasks.erase(it);
        std::cout << "Task removed!" << std::endl;
    }
    else
    {
        std::cerr << "Invalid task number!" << std::endl;
    }
}

void showTasks(const std::list<std::string> &tasks)
{
    std::cout << "\nTasks:" << std::endl;
    if (tasks.empty())
    {
        std::cout << "No tasks available." << std::endl;
    }
    else
    {
        int taskNumber = 1;
        for (const auto &task : tasks)
        {
            std::cout << taskNumber << ". " << task << std::endl;
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
                std::cerr << "Invalid choice! Please try again." << std::endl;
            }
        }
        else
        {
            std::cerr << "Invalid input! Please enter a valid choice." << std::endl;
        }
    }

    return 0;
}