#include <iostream>
#include <string>
#include <cmath>
#include <cctype>

using namespace std;

int GCD(int first, int second);

int main(int argc, char** argv)
{
    int a;
    int b;
    int out;
    cout << "Please enter the first number for the GCD algorithm" << endl;
    cin >> a;
    cout << "Please enter the second number for the GCD algorithm" << endl;
    cin >> b;
    out = GCD(a, b);
    cout << a << ", " << b << endl;
    cout << "GCD(" << a << ", " << b << ") = " << out<< endl;
    return 0;
}

int GCD(int first, int second)
{
    int remainder;
    if(first == 0)
    {
        return second;
    }

    else if(second == 0)
    {
        return first;
    }

    else
    {
        remainder = first%second;
        return GCD(second, remainder);
    }
}