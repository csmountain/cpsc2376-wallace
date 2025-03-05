#include "Fraction.h"

Fraction::Fraction(int num, int denom) : numerator(num), denominator(denom)
{
    if (denom == 0)
    {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    simplify();
}

int Fraction::getNumerator() const
{
    return numerator;
}

int Fraction::getDenominator() const
{
    return denominator;
}

void Fraction::setNumerator(int num)
{
    numerator = num;
    simplify();
}

void Fraction::setDenominator(int denom)
{
    if (denom == 0)
    {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    denominator = denom;
    simplify();
}

void Fraction::simplify()
{
    if (denominator == 0)
    {
        throw std::invalid_argument("Denominator cannot be zero");
    }

    // Compute GCD using Euclidean algorithm
    int a = numerator, b = denominator;
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    int gcd = a; // GCD is stored in 'a' after loop exits

    // Simplify the fraction
    numerator /= gcd;
    denominator /= gcd;

    // Ensure the denominator is positive
    if (denominator < 0)
    {
        numerator = -numerator;
        denominator = -denominator;
    }
}

Fraction operator+(const Fraction &lhs, const Fraction &rhs)
{
    int num = lhs.numerator * rhs.denominator + rhs.numerator * lhs.denominator;
    int denom = lhs.denominator * rhs.denominator;
    return Fraction(num, denom);
}

Fraction operator-(const Fraction &lhs, const Fraction &rhs)
{
    int num = lhs.numerator * rhs.denominator - rhs.numerator * lhs.denominator;
    int denom = lhs.denominator * rhs.denominator;
    return Fraction(num, denom);
}

Fraction operator*(const Fraction &lhs, const Fraction &rhs)
{
    int num = lhs.numerator * rhs.numerator;
    int denom = lhs.denominator * rhs.denominator;
    return Fraction(num, denom);
}

Fraction operator/(const Fraction &lhs, const Fraction &rhs)
{
    if (rhs.numerator == 0)
    {
        throw std::invalid_argument("Division by zero");
    }
    int num = lhs.numerator * rhs.denominator;
    int denom = lhs.denominator * rhs.numerator;
    return Fraction(num, denom);
}

std::ostream &operator<<(std::ostream &os, const Fraction &fraction)
{
    os << fraction.numerator << "/" << fraction.denominator;
    return os;
}