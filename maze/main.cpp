#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>

using namespace std;

bool openInput(ifstream& fileIn, string fileName);
bool workOrderEmpty(vector<queue<int>> wo);
bool isShorter(vector<int> current, vector<int> test);
bool alreadyBeen(vector<int> predecessor, int space);
void noDupes(vector<int>& currIn);

int main() {

    vector<vector<int>> paths;
    vector<queue<int>> workOrder;
    string fileName;
    int currentInput;
    int currentTo;
    int loc;
    int frw;
    int end;
    int i;
    int j;
    vector<int> pred;
    vector<int> currentShortest;
    ifstream input;
    paths.resize(100);

    cout << "Please input the name of a maze file which will be read: " << endl;
    cin >> fileName;

    if(!openInput(input, fileName))
    {
        cout << "There was an error opening your file. Please make sure the extension is included ";
        cout << "and the file is in the right location." << endl;
        exit;
    }

    input >> loc;
    input >> end;

    while(input >> currentInput)
    {
        input >> currentTo;
        while(currentTo != -1)
        {
            paths[currentInput].push_back(currentTo);
            input >> currentTo;
        }
    }
    paths.resize(currentInput + 1);
    workOrder.resize(currentInput + 1);
    pred.resize(paths.size() + 2, -1);
    currentShortest.resize(paths.size() + 2, 0);

    for(i=1; i<paths.size(); i++)
    {
        for(j=0; j<paths[i].size(); j++)
        {
            workOrder[i].push(paths[i][j]);
        }
    }

    i=1;
    while(loc != end)
    {
        frw = workOrder[loc].front();
        workOrder[loc].pop();
        if(alreadyBeen(pred, frw))
        {
            while(workOrder[loc].empty())
            {
                loc = pred[i-1];
                i--;
            }
            frw = workOrder[loc].front();
            workOrder[pred[i]].pop();
        }
        pred[i] = loc;
        if(frw == end)
        {
            if(isShorter(currentShortest, pred))
            {
                currentShortest = pred;
            }
        }

        else if(workOrder[frw].empty())
        {
            loc = pred[i];
            if(!workOrder[loc].empty())
            {
                frw = workOrder[loc].front();
            }
            while(workOrder[frw].empty())
            {
                pred[i + 1] = -1;
                loc = pred[i-1];
                if(!workOrder[loc].empty())
                {
                    frw = workOrder[loc].front();
                }
                i--;
            }
        }
        i++;
        loc = frw;
        pred[i] = loc;
    }

    noDupes(currentShortest);

    cout << "Start -> ";
    j = 2;
    for(i=0; i<currentShortest.size(); i++)
    {
        if(currentShortest[i] != -1)
        {
            cout << currentShortest[i] << " -> ";
            j++;
        }
    }

    cout << end << " -> Exit" << endl;
    cout << "Total cost: " << j << endl;
    return 0;

    /* This commented-out main function works for parts 1-3. To test parts 1-3, simply comment out the
     * existing main and uncomment this one!*/
    /*vector<vector<int>> paths;
    vector<queue<int>> workOrder;
    string fileName;
    int currentInput;
    int currentTo;
    int loc = 1;
    int frw;
    int i;
    int j;
    vector<int> pred;
    vector<int> currentShortest;
    ifstream input;
    paths.resize(100);

    cout << "Please input the name of a maze file which will be read: " << endl;
    cin >> fileName;

    if(!openInput(input, fileName))
    {
        cout << "There was an error opening your file. Please make sure the extension is included ";
        cout << "and the file is in the right location." << endl;
        exit;
    }



    while(input >> currentInput)
    {
        input >> currentTo;
        while(currentTo != -1)
        {
            paths[currentInput].push_back(currentTo);
            input >> currentTo;
        }
    }
    paths.resize(currentInput);
    workOrder.resize(currentInput);
    pred.resize(paths.size() + 2, -1);
    currentShortest.resize(paths.size() + 2, 0);

    for(i=1; i<paths.size(); i++)
    {
        for(j=0; j<paths[i].size(); j++)
        {
            workOrder[i].push(paths[i][j]);
        }
    }

    i=1;
    while(loc != paths.size())
    {
        frw = workOrder[loc].front();
        workOrder[loc].pop();
        pred[i] = loc;
        if(frw == paths.size())
        {
            if(isShorter(currentShortest, pred))
            {
                currentShortest = pred;
            }
        }

        else if(workOrder[frw].empty())
        {
            loc = pred[i];
            if(!workOrder[loc].empty())
            {
                frw = workOrder[loc].front();
            }
            while(workOrder[frw].empty())
            {
                pred[i + 1] = -1;
                loc = pred[i-1];
                if(!workOrder[loc].empty())
                {
                    frw = workOrder[loc].front();
                }
                i--;
            }
        }
        i++;
        loc = frw;
        pred[i] = loc;
    }

    cout << "Start -> ";
    j = 2;
    for(i=0; i<currentShortest.size(); i++)
    {
        if(currentShortest[i] != -1)
        {
            cout << currentShortest[i] << " -> ";
            j++;
        }
    }

    cout << paths.size() << " -> Exit" << endl;
    cout << "Total cost: " << j << endl;
    return 0;*/
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

bool workOrderEmpty(vector<queue<int>> wo)
{
    int i;
    for(i=0; i<wo.size(); i++)
    {
        if(!wo[i].empty())
        {
            return false;
        }
    }

    return true;
}

bool isShorter(vector<int> current, vector<int> test)
{
    int i;
    int currentSize = 0;
    int testSize = 0;

    for(i=0; i<current.size(); i++)
    {
        if(current[i] != -1)
        {
            currentSize ++;
        }
    }

    for(i=0; i<test.size(); i++)
    {
        if(test[i] != -1)
        {
            testSize++;
        }
    }

    if(testSize < currentSize)
    {
        return true;
    }

    return false;
}

bool alreadyBeen(vector<int> predecessor, int space)
{
    int i;
    for(i=0; i<predecessor.size(); i++)
    {
        if(predecessor[i] == space)
        {
            return true;
        }
    }

    return false;
}

void noDupes(vector<int>& currIn)
{
    int i, j;
    for(i=0; i<currIn.size(); i++)
    {
        if(currIn[i] != -1)
        {
            for(j=0; j<currIn.size(); j++)
            {
                if(j != i)
                {
                    if(currIn[j] == currIn[i])
                    {
                        currIn[j] = -1;
                    }
                }
            }
        }
    }
}