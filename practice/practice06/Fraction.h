#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <stdexcept>

class Fraction
{
protected:
    int numerator;
    int denominator;
    void simplify(); // Helper function to simplify the fraction

public:
    Fraction(int num = 0, int denom = 1);

    int getNumerator() const;
    int getDenominator() const;
    void setNumerator(int num);
    void setDenominator(int denom);

    // Friend functions for arithmetic operators
    friend Fraction operator+(const Fraction &lhs, const Fraction &rhs);
    friend Fraction operator-(const Fraction &lhs, const Fraction &rhs);
    friend Fraction operator*(const Fraction &lhs, const Fraction &rhs);
    friend Fraction operator/(const Fraction &lhs, const Fraction &rhs);

    // Friend function for stream insertion operator
    friend std::ostream &operator<<(std::ostream &os, const Fraction &fraction);
};

#endif // FRACTION_H