#ifndef FRACTION_H
#define FRACTION_H

#include <stdexcept>

class Fraction
{
private:
    int num; // numerator
    int den; // denominator

    void simplify(); // Helper function to simplify the fraction

public:
    // Constructors
    Fraction();
    Fraction(int n, int d);

    // Getters and Setters
    int getNumerator() const;
    int getDenominator() const;
    void setNumerator(int n);
    void setDenominator(int d);
};

#endif // FRACTION_H