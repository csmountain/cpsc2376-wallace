#ifndef MIXEDFRACTION_H
#define MIXEDFRACTION_H

#include "Fraction.h"

class MixedFraction : public Fraction
{
private:
    int wholeNumber;

public:
    MixedFraction(int whole = 0, int num = 0, int denom = 1);
    MixedFraction(const Fraction &fraction);

    // Friend function for stream insertion operator
    friend std::ostream &operator<<(std::ostream &os, const MixedFraction &mixedFraction);
};

#endif // MIXEDFRACTION_H