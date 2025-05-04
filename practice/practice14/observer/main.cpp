// AI Used to help with creating templates, some bug fixes, and comments. UI and large amounts of bugfixing done manually.
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <numeric>

// Observer interface
class Observer
{
public:
    virtual void update(int grade) = 0;
    virtual ~Observer() = default;
};

// GradeBook class (Subject)
class GradeBook
{
public:
    void addObserver(std::shared_ptr<Observer> observer)
    {
        observers.push_back(observer);
    }

    void setGrade(int grade)
    {
        grades.push_back(grade);
        notifyObservers(grade);
    }

private:
    void notifyObservers(int grade)
    {
        for (const auto &observer : observers)
        {
            observer->update(grade);
        }
    }

    std::vector<int> grades;
    std::vector<std::shared_ptr<Observer>> observers;
};

// Averager class (Observer)
class Averager : public Observer
{
public:
    void update(int grade) override
    {
        totalGrades += grade;
        ++count;
        std::cout << "\nUpdated average: " << (totalGrades / static_cast<double>(count)) << "\n" << std::endl;
    }

private:
    int totalGrades = 0;
    int count = 0;
};

// Notifier class (Observer)
class Notifier : public Observer
{
public:
    explicit Notifier(int threshold) : threshold(threshold) {}

    void update(int grade) override
    {
        if (grade < threshold)
        {
            std::cout << "Email sent to student@example.com: Grade dropped below " << threshold << "%\n" << std::endl;
        }
    }

private:
    int threshold;
};

int main()
{
    auto gradeBook = std::make_shared<GradeBook>();

    auto averager = std::make_shared<Averager>();
    auto notifier = std::make_shared<Notifier>(60);

    gradeBook->addObserver(averager);
    gradeBook->addObserver(notifier);

    int grade;
    std::string input;

    while (true)
    {
        // Display menu
        std::cout << "--- Grade Management Menu ---" << std::endl;
        std::cout << "1. Enter grade" << std::endl;
        std::cout << "2. Exit grading" << std::endl;
        std::cout << "\nEnter your choice: ";
        std::cin >> input;

        if (input == "1")
        {
            while (true)
            {
                std::cout << "\nEnter grade: ";
                std::cin >> input;

                try
                {
                    grade = std::stoi(input);

                    if (grade < 0 || grade > 100)
                    {
                        std::cout << "\nInvalid grade. Please enter a grade between 0 and 100." << std::endl;
                        continue;
                    }

                    gradeBook->setGrade(grade);
                    break; // Exit the inner loop after successfully entering a grade
                }
                catch (const std::invalid_argument &)
                {
                    std::cout << "\nInvalid input. Please enter a numeric grade." << std::endl;
                }
                catch (const std::out_of_range &)
                {
                    std::cout << "Invalid input. Grade is out of range." << std::endl;
                }
            }
        }
        else if (input == "2")
        {
            std::cout << "\nExiting grading..." << std::endl;
            break;
        }
        else
        {
            std::cout << "\nInvalid choice. Please enter 1 or 2." << std::endl;
        }
    }

    return 0;
}