#include <iostream>

struct Point
{
    float x;
    float y;
};

// Function to calculate the midpoint between two points (returns a Point object)
Point calcMidpoint(const Point *p1, const Point *p2)
{
    // TODO: Implement midpoint formula using p1 and p2
    // Hint: midpoint x = (x1 + x2) / 2, midpoint y = (y1 + y2) / 2
    return Point{0.0f, 0.0f}; // Placeholder return value
}

int main()
{
    // Step 1: Create two points with example coordinates
    Point a{1.0f, 2.0f};
    Point b{5.0f, 6.0f};

    // Step 2: Call calcMidpoint using pointers to 'a' and 'b'
    Point mid = calcMidpoint(/* Fill this in */);

    // Step 3: Print the midpoint coordinates
    std::cout << "Midpoint is at (" << mid.x << ", " << mid.y << ")" << std::endl; // Should be (3, 4)

    return 0;
}