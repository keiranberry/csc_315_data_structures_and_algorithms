#include "fraction.h"

fraction::fraction()
{
    numerator = 0;
    denominator = 1;
}

fraction::fraction(int numerator, int denominator)
{
    numerator = 0;
    denominator = 0;
}

fraction::fraction(int wholeNum)
{
    numerator = 0;
    denominator = 1;
}

fraction::~fraction()
{
    numerator = 0;
    denominator = 0;
}

void fraction::add(fraction fOne, fraction fTwo, fraction& final)
{
    if(fOne.denominator != fTwo.denominator)
    {
        fTwo.numerator = fTwo.numerator * fOne.denominator;
        fOne.denominator = fOne.denominator * fTwo.denominator;
        fOne.numerator = fOne.numerator * fTwo.denominator;
        fTwo.denominator = fOne.denominator;
    }

    final.numerator = fOne.numerator + fTwo.numerator;
    final.denominator = fOne.denominator;
}

void fraction::subtract(fraction fOne, fraction fTwo, fraction &final)
{
    if(fOne.denominator != fTwo.denominator)
    {
        fTwo.numerator = fTwo.numerator * fOne.denominator;
        fOne.denominator = fOne.denominator * fTwo.denominator;
        fOne.numerator = fOne.numerator * fTwo.denominator;
        fTwo.denominator = fOne.denominator;
    }

    final.numerator = fOne.numerator - fTwo.numerator;
    final.denominator = fOne.denominator;
}

void fraction::multiply(fraction fOne, fraction fTwo, fraction &final)
{
    final.numerator = fOne.numerator * fTwo.numerator;
    final.denominator = fOne.denominator * fTwo.denominator;
}

void fraction::divide(fraction fOne, fraction fTwo, fraction &final)
{
    final.numerator = fOne.numerator * fTwo.denominator;
    final.denominator = fOne.denominator * fTwo.numerator;
}

void fraction::print(fraction fOne, fraction fTwo, fraction final, char function)
{
    if(fOne.denominator == 1)
    {
        cout << fOne.numerator;
    }

    else
    {
        cout << fOne.numerator << "/" << fOne.denominator;
    }

    cout << " " << function << " ";

    if(fTwo.denominator == 1)
    {
        cout << fTwo.numerator;
    }

    else
    {
        cout << fTwo.numerator << "/" << fTwo.denominator;
    }

    cout << " = " << final.numerator << "/" << final.denominator << endl;
}
