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
        std::cout << "Updated average: " << (totalGrades / static_cast<double>(count)) << std::endl;
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
            std::cout << "Email sent to student@example.com: Grade dropped below " << threshold << "%" << std::endl;
        }
    }

private:
    int threshold;
};

int main()
{
    return 0;
}