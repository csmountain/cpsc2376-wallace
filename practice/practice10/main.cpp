#include <iostream> 
#include <fstream> // for std::ifstream
#include <vector> // for std::vector
#include <memory> // for std::unique_ptr
#include <sstream> // for std::stringstream
#include <iomanip> // for std::setprecision
#include <cmath> // for M_PI

class Shape // base class for shapes with virtual method
{
public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
};

class Rectangle : public Shape // derived class for Rectangle
{
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double getArea() const override
    {
        return width * height;
    }
};

class Circle : public Shape // derived class for Circle
{
private:
    double radius;

public:
    Circle(double r) : radius(r) {}
    double getArea() const override
    {
        return M_PI * radius * radius;
    }
};

void printAllAreas(const std::vector<std::unique_ptr<Shape>> &shapes)
{
    for (const auto &shape : shapes)
    {
        std::cout << "Area: " << std::fixed << std::setprecision(4) << shape->getArea() << std::endl;
    }
}
