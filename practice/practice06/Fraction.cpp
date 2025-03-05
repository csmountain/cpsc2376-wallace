#include "Fraction.h"

// Default constructor
Fraction::Fraction() : num(0), den(1) {}

// Parameterized constructor
Fraction::Fraction(int n, int d) : num(n), den(d)
{
    if (d == 0)
    {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    simplify();
}

// Getters
int Fraction::getNumerator() const
{
    return num;
}

int Fraction::getDenominator() const
{
    return den;
}

// Setters
void Fraction::setNumerator(int n)
{
    num = n;
    simplify();
}

void Fraction::setDenominator(int d)
{
    if (d == 0)
    {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    den = d;
    simplify();
}

// Helper function to simplify the fraction
void Fraction::simplify()
{
    if (den == 0)
    {
        throw std::invalid_argument("Denominator cannot be zero");
    }

    // Compute GCD using Euclidean algorithm
    int a = num, b = den;
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    int gcd = a; // GCD is stored in 'a' after loop exits

    // Simplify the fraction
    num /= gcd;
    den /= gcd;

    // Ensure the denominator is positive
    if (den < 0)
    {
        num = -num;
        den = -den;
    }
}