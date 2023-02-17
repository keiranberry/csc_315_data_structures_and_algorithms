#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;


class fraction
{
public:

    int numerator;
    int denominator;
    fraction();
    fraction(int numerator, int denominator);
    fraction(int wholeNum);
    ~fraction();

    void add(fraction fOne, fraction fTwo, fraction& final);
    void subtract(fraction fOne, fraction fTwo, fraction& final);
    void multiply(fraction fOne, fraction fTwo, fraction& final);
    void divide(fraction fOne, fraction fTwo, fraction& final);
    void print(fraction fOne, fraction fTwo, fraction final, char function);

};

void menu(fraction& fOne, fraction& fTwo);
