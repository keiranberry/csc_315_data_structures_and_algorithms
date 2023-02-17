#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

bool isPrime(int input);
bool openInput(ifstream& fileIn, string fileName);

int main() {
    vector<string> names;
    string file1;
    string file2;
    ifstream input1;
    ifstream input2;
    string currentFirst;
    string currentLast;
    string fullName;
    int commaPos;
    int nameAscii;
    bool breakLoop = false;
    int iterator = 1;
    int i=0;
    int totalHash = 0;
    cout << "Please input the names of two files ";
    cout << "containing names that will be hashed: " << endl;
    cin >> file1;
    cin >> file2;
    names.resize(2003, "");

    if(!openInput(input1, file1) || !openInput(input2, file2))
    {
        cout << "There was an error opening one or more of your input files. Please try again ";
        cout << "by re-running the program and make sure you have written the file extensions." << endl;
        exit;
    }

    input1 >> currentFirst;

    while(input1 >> currentFirst)
    {
        nameAscii = 0;
        iterator = 0;
        totalHash ++;
        commaPos = currentFirst.find(',');
        currentLast = currentFirst.substr(commaPos + 1);
        currentFirst = currentFirst.substr(0, commaPos);
        for(i = 0; i < currentLast.length(); i++)
        {
            nameAscii = nameAscii + currentLast[i];
        }
        nameAscii = nameAscii % names.size();

        if(names[nameAscii] == "")
        {
            totalHash ++;
            names[nameAscii] = currentFirst + " " + currentLast;
        }

        else
        {
            while(names[nameAscii + iterator] != "" && nameAscii + iterator < names.size())
            {
                iterator++;
            }

            if(nameAscii + iterator == names.size())
            {
                cout << "Vector is full." << endl;
                exit;
            }
            totalHash++;
            names[nameAscii + iterator] = currentFirst + " " + currentLast;
        }

    }

    cout << "----- Intersection -----" << endl;
    cout << "------------------------" << endl;

    input2 >> currentFirst;

    while(input2 >> currentFirst)
    {
        nameAscii = 0;
        breakLoop = false;
        totalHash++;
        commaPos = currentFirst.find(',');
        currentLast = currentFirst.substr(commaPos + 1);
        currentFirst = currentFirst.substr(0, commaPos);
        fullName = currentFirst + " " + currentLast;

        for(i = 0; i < currentLast.length(); i++)
        {
            nameAscii = nameAscii + currentLast[i];
        }
        nameAscii = nameAscii % names.size();

        if(names[nameAscii] != "")
        {
            if(names[nameAscii] == fullName)
            {
                cout << nameAscii << ", " << currentFirst << "," << currentLast << endl;
            }

            else
            {
                while(names[nameAscii] != "" && breakLoop == false)
                {
                    nameAscii ++;
                    if(names[nameAscii] == fullName)
                    {
                        totalHash++;
                        cout << nameAscii << ", " << currentFirst << "," << currentLast << endl;
                        breakLoop = true;
                    }
                }
            }
        }
    }

    cout << "------------------------" << endl;
    cout << "We did " << totalHash << " hash mappings" << endl;

    return 0;
}

/*isPrime was used to check the next prime number after 2002
  which is double the size of the first list
  it will not be used in the function main, but could be
  implemented if you wanted to use other files*/
bool isPrime( int input)
{
    int i = 3;

    if (input > 1)
    {
        if (input == 2 || input == 3)
        {
            return true;
        }

        if (input % 2 == 0)
        {
            return false;
        }

        while ( i < input)

        { if (input % i == 0)
            {
                return false;
            }
            i = i + 2;
        }
        return true;
    }

    return false;
}

bool openInput(ifstream& fileIn, string fileName)
{
    //open the input file
    fileIn.open(fileName);

    //if the input file opened, return true
    if (fileIn.is_open())
    {
        return true;
    }

        //otherwise, return false
    else
    {
        return false;
    }

}
