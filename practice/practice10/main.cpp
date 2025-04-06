// AI Used to help with creating templates, some bug fixes, and comments. UI and large amounts of bugfixing done manually.
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
        double area = shape->getArea();
        // Check if the area is a whole number
        if (std::floor(area) == area)
        {
            std::cout << "Area: " << static_cast<int>(area) << std::endl; // Print as integer
        }
        else
        {
            std::cout << "Area: " << std::fixed << std::setprecision(4) << area << std::endl; // Print as double
        }
    }
}

int main()
{
    std::ifstream inputFile("shapes.txt");
    if (!inputFile)
    {
        std::cerr << "Error: Could not open file 'shapes.txt'." << std::endl;
        return 1;
    }

    std::vector<std::unique_ptr<Shape>> shapes;
    std::string line;

    while (std::getline(inputFile, line)) // Read each line from the file
    {
        std::istringstream iss(line);
        std::string shapeType;
        iss >> shapeType;

        if (shapeType == "rectangle")
        {
            double width, height;
            if (iss >> width >> height)
            {
                shapes.push_back(std::make_unique<Rectangle>(width, height)); // unique_ptr to Rectangle object
            }
        }
        else if (shapeType == "circle")
        {
            double radius;
            if (iss >> radius)
            {
                shapes.push_back(std::make_unique<Circle>(radius)); // unique_ptr to Circle object
            }
        }
        else
        {
            std::cerr << "Error: Unknown shape type '" << shapeType << "' in line: " << line << std::endl;
        }
    }
    
    inputFile.close();

    printAllAreas(shapes);

    return 0;
}