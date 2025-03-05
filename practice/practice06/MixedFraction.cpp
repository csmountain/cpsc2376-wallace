#include "MixedFraction.h"

MixedFraction::MixedFraction(int whole, int num, int denom) : Fraction(num, denom), wholeNumber(whole)
{
    if (denom == 0)
    {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    // Convert to improper fraction
    setNumerator(whole * denom + num);
    setDenominator(denom);
    simplify();
}

MixedFraction::MixedFraction(const Fraction &fraction) : Fraction(fraction)
{
    wholeNumber = getNumerator() / getDenominator();
    setNumerator(getNumerator() % getDenominator());
}

std::ostream &operator<<(std::ostream &os, const MixedFraction &mixedFraction)
{
    if (mixedFraction.wholeNumber != 0)
    {
        os << mixedFraction.wholeNumber << " ";
    }
    if (mixedFraction.getNumerator() != 0)
    {
        os << mixedFraction.getNumerator() << "/" << mixedFraction.getDenominator();
    }
    else if (mixedFraction.wholeNumber == 0)
    {
        os << "0";
    }
    return os;
}