#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

class Employee
{
protected:
    std::string name;
    int id;

public:
    Employee(std::string name, int id) : name(name), id(id) {}
    virtual ~Employee() = default;
    virtual double calculateSalary() const = 0;
    virtual void displayInfo() const
    {
        std::cout << "ID: " << id << ", Name: " << name;
    }
};

class SalariedEmployee : public Employee
{
    double monthlySalary;

public:
    SalariedEmployee(std::string name, int id, double monthlySalary)
        : Employee(name, id), monthlySalary(monthlySalary) {}
    double calculateSalary() const override
    {
        return monthlySalary;
    }
    void displayInfo() const override
    {
        Employee::displayInfo();
        std::cout << ", Type: Salaried, Monthly Salary: $" << monthlySalary << "\n";
    }
};

class HourlyEmployee : public Employee
{
    double hourlyRate;
    int hoursWorked;

public:
    HourlyEmployee(std::string name, int id, double hourlyRate, int hoursWorked)
        : Employee(name, id), hourlyRate(hourlyRate), hoursWorked(hoursWorked) {}
    double calculateSalary() const override
    {
        return hourlyRate * hoursWorked;
    }
    void displayInfo() const override
    {
        Employee::displayInfo();
        std::cout << ", Type: Hourly, Hours Worked: " << hoursWorked
                  << ", Hourly Rate: $" << hourlyRate
                  << ", Salary: $" << calculateSalary() << "\n";
    }
};

class CommissionEmployee : public Employee
{
    double baseSalary;
    double salesAmount;
    double commissionRate;

public:
    CommissionEmployee(std::string name, int id, double baseSalary, double salesAmount, double commissionRate)
        : Employee(name, id), baseSalary(baseSalary), salesAmount(salesAmount), commissionRate(commissionRate) {}
    double calculateSalary() const override
    {
        return baseSalary + (salesAmount * commissionRate);
    }
    void displayInfo() const override
    {
        Employee::displayInfo();
        std::cout << ", Type: Commission, Base Salary: $" << baseSalary
                  << ", Sales: $" << salesAmount
                  << ", Commission Rate: " << commissionRate * 100 << "%"
                  << ", Salary: $" << calculateSalary() << "\n";
    }
};

void loadEmployees(const std::string &filename, std::vector<Employee *> &employees)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Error opening file: " << filename << "\n\n";
        return;
    }
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string type, name;
        int id;
        if (!(iss >> type >> id >> name))
        {
            std::cerr << "Invalid data format in file: " << line << "\n\n";
            continue;
        }
        if (type == "Salaried")
        {
            double salary;
            if (iss >> salary)
                employees.push_back(new SalariedEmployee(name, id, salary));
        }
        else if (type == "Hourly")
        {
            double rate;
            int hours;
            if (iss >> rate >> hours)
                employees.push_back(new HourlyEmployee(name, id, rate, hours));
        }
        else if (type == "Commission")
        {
            double base, sales, rate;
            if (iss >> base >> sales >> rate)
                employees.push_back(new CommissionEmployee(name, id, base, sales, rate));
        }
        else
        {
            std::cerr << "Unknown employee type: " << type << "\n\n";
        }
    }
}

int main()
{
    std::vector<Employee *> employees;
    loadEmployees("employees.txt", employees);

    for (const auto &emp : employees)
    {
        emp->displayInfo();
    }

    for (auto emp : employees)
    {
        delete emp;
    }
    return 0;
}
