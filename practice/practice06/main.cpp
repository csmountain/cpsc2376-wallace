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

        std::cout << "Fraction f1: " << f1.getNumerator() << "/" << f1.getDenominator() << std::endl;
        std::cout << "Fraction f2: " << f2.getNumerator() << "/" << f2.getDenominator() << std::endl;
        std::cout << "Fraction f3: " << f3.getNumerator() << "/" << f3.getDenominator() << std::endl;

        f3.setNumerator(9);
        f3.setDenominator(12);
        std::cout << "Fraction f3 after setting new values: " << f3.getNumerator() << "/" << f3.getDenominator() << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}