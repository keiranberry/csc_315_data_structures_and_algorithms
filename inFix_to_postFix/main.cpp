#include <iostream>
#include "inFix_to_postFix.h"

int main(int argc, char** argv)
{

    stack<char> operators;
    vector<char> output;
    stack<int> ints;
    stack<char> opers;
    string convert;
    string infix = "Infix: ";
    char input;
    char top;
    int i;
    int toPush;
    int operandOne;
    int operandTwo;
    bool solve = true;

    cout << "Please input an expression in infix notation, **followed by an equals sign** ." << endl;
    cout << "Examples: 4 + 5 * 2 / 7 =" << endl;
    cout << "          a / d * c - b =" << endl;

    while(cin >> input && input != '=')
    {
        if(isalnum(input))
        {
            output.push_back(input);
            infix = infix + input;
            if(isalpha(input))
            {
                solve = false;
            }
        }

        else if (input == '+' || input == '-' || input == '*' ||
                 input == '/' || input == '%')
        {
            output.push_back(' ');
            infix = infix + " " + input + " ";

            if(operators.empty() || operators.top() == '(' || operators.top() == ')')
            {
                operators.push(input);
            }

            else
            {
                while(!operators.empty() && precedence(input) <= precedence(operators.top())
                      && operators.top() != '(')
                {
                    output.push_back(operators.top());
                    output.push_back(' ');
                    operators.pop();
                }
                operators.push(input);
            }

        }

        else if(input == '(')
        {
            operators.push(input);
            infix = infix + input;
        }

        else if(input == ')')
        {
            infix = infix + input;
            while(operators.top() != '(')
            {
                output.push_back(' ');
                output.push_back(operators.top());
                operators.pop();
            }

            operators.pop();
        }
    }

    while(!operators.empty())
    {
        if(operators.top() != '(' && operators.top() != ')')
        {
            output.push_back(' ');
            output.push_back(operators.top());
        }

        operators.pop();
    }

    cout << infix << endl << "Postfix: ";

    for(i = 0; i < output.size(); i++)
    {
        cout << output[i];
    }

    if(solve)
    {
        for(i = 0; i < output.size(); i++)
        {
            if(isalnum(output[i]))
            {
                convert = convert + output[i];
            }

            else if(output[i] == ' ')
            {
                if(!convert.empty())
                {
                    ints.push(stoi(convert));
                    convert.clear();
                }
            }

            else
            {
                operandTwo = ints.top();
                ints.pop();
                operandOne = ints.top();
                ints.pop();

                if(output[i] == '+')
                {
                    ints.push(operandOne + operandTwo);
                }

                else if(output[i] == '-')
                {
                    ints.push(operandOne - operandTwo);
                }

                else if(output[i] == '*')
                {
                    ints.push(operandOne * operandTwo);
                }

                else if(output[i] == '/')
                {
                    ints.push(operandOne / operandTwo);
                }

                else
                {
                    ints.push(operandOne % operandTwo);
                }
            }

        }
        cout << " = " << ints.top() << endl;
    }

    return 0;
}

int precedence(char op)
{
    if(op == '+' || op == '-')
    {
        return 0;
    }

    else if(op == '*' || op == '/' || op == '%')
    {
        return 1;
    }

    else if(op == '(' || op == ')')
    {
        return 2;
    }
}
