#include <cmath>
#include <cctype>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct vertex
{
    int degree = 0;
    vector<int> paths;
};

void readIn(ifstream& fin, vector<vertex>& vec, int& numEdges);

bool hasCircuit(vector<vertex>& vec);

void circuit(vector<vertex>& vec, vector<int>& path, int numEdges);