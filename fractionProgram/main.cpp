#include "fraction.h"


int main(int argc, char** argv)
{
    fraction fracOne;
    fraction fracTwo;
    fraction output;
    menu(fracOne, fracTwo);

    output.multiply(fracOne, fracTwo, output);
    output.print(fracOne, fracTwo, output, '*');

    output.divide(fracOne, fracTwo, output);
    output.print(fracOne, fracTwo, output, '/');

    output.add(fracOne, fracTwo, output);
    output.print(fracOne, fracTwo, output, '+');

    output.subtract(fracOne, fracTwo, output);
    output.print(fracOne, fracTwo, output, '-');

    return 0;
}

void menu(fraction& fOne, fraction& fTwo)
{
    int choice = 0;
    cout << "Enter the number corresponding to your choice" << endl;
    cout << "1: Enter a fraction in the form x/y" << endl;
    cout << "2: Enter a whole number in the form x" << endl;
    cin >> choice;

    if(choice == 1)
    {
        cout << "Please enter a fraction in the form x/y (Do not use whitespace)" << endl;
        cin >> fOne.numerator;
        cin.get();
        cin >> fOne.denominator;
    }
    else if(choice == 2)
    {
        cout << "Please enter a whole number in the form x" << endl;
        cin >> fOne.numerator;
        fOne.denominator = 1;
    }
    else
    {
        cout << "Invalid option selected, please restart and try again" << endl;
        //menu(fOne, fTwo);
    }

    choice = 0;
    cout << "Enter the number corresponding to your choice for the second number" << endl;
    cout << "1: Enter a fraction in the form x/y" << endl;
    cout << "2: Enter a whole number in the form x" << endl;
    cin >> choice;

    if(choice == 1)
    {
        cout << "Please enter a fraction in the form x/y (Do not use whitespace)" << endl;
        cin >> fTwo.numerator;
        cin.get();
        cin >> fTwo.denominator;
    }
    else if(choice == 2)
    {
        cout << "Please enter a whole number in the form x" << endl;
        cin >> fTwo.numerator;
        fTwo.denominator = 1;
    }
    else
    {
        cout << "Invalid option selected, please restart and try again" << endl;
    }

    if(fOne.denominator == 0 || fTwo.denominator == 0)
    {
        cout << "One or more of the denominators entered is zero. Please restart and try again." << endl;
    }
}

