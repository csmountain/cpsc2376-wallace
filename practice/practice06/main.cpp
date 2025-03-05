#include <iostream>
#include "Fraction.h"
#include "Fraction.cpp"

int main()
{
    try
    {
        Fraction f1;
        Fraction f2(3, 4);
        Fraction f3(6, 8);

        std::cout << "Fraction f1: " << f1 << std::endl;
        std::cout << "Fraction f2: " << f2 << std::endl;
        std::cout << "Fraction f3: " << f3 << std::endl;

        f3.setNumerator(9);
        f3.setDenominator(12);
        std::cout << "Fraction f3 after setting new values: " << f3 << std::endl;

        Fraction f4 = f2 + f3;
        std::cout << "f2 + f3 = " << f4 << std::endl;

        Fraction f5 = f2 - f3;
        std::cout << "f2 - f3 = " << f5 << std::endl;

        Fraction f6 = f2 * f3;
        std::cout << "f2 * f3 = " << f6 << std::endl;

        Fraction f7 = f2 / f3;
        std::cout << "f2 / f3 = " << f7 << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}