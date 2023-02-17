#include "euler.h"

void readIn(ifstream& fin, vector<vertex>& vec, int& numEdges)
{
    int nums;
    int numTwo;

    while(fin >> nums)
    {
        fin >> numTwo;
        vec[nums].paths.push_back(numTwo);
        vec[numTwo].paths.push_back(nums);
        vec[nums].degree++;
        vec[numTwo].degree++;
        numEdges++;
    }
}


bool hasCircuit(vector<vertex>& vec)
{
    int i;
    bool possible = true;

    for(i = 0; i < vec.size(); i++)
    {
        if(vec[i].degree % 2 != 0)
        {
            possible = false;
        }
    }

    return possible;
}

void circuit(vector<vertex>& vec, vector<int>& path, int numEdges)
{
    int i = 0;
    int j;
    int k = 0;
    int curr = 1;
    int next;
    path.push_back(1);
    while(i<numEdges-1)
    {
        if(!vec[curr].paths.empty())
        {
            next = vec[curr].paths[k];
            k++;
            if(i == numEdges - 2)
            {
                path.push_back(vec[curr].paths[0]);
                i++;
            }

            else if(i > 3 && vec[next].paths[0] == 1)
            {
                //skip the other else if
            }

            else if(vec[next].paths.size() >= 2)
            {
                vec[curr].paths.erase(vec[curr].paths.begin()+k-1);
                for(j = 0; j < vec[next].paths.size(); j++)
                {
                    if(vec[next].paths[j] == curr)
                    {
                        vec[next].paths.erase(vec[next].paths.begin() + j);
                    }
                }
                curr = next;
                k = 0;
                i++;
                path.push_back(curr);
            }
        }
    }

    path.push_back(1);
}