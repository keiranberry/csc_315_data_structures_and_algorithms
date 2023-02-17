#include "euler.h"

int main(int argc, char** argv)
{
    ifstream input;
    string fileIn;
    vector<vertex> verts;
    vector<int> route;
    int edges = 0;
    route.resize(0);
    verts.resize(100);
    int i = 0;

    cout << "Please enter the name of a file containing a graph: " << endl;
    cin >> fileIn;
    input.open(fileIn);
    if(!input.is_open())
    {
        cout << "There was a problem opening your input file" << endl;
        exit(0);
    }

    readIn(input, verts, edges);
    if(!hasCircuit(verts))
    {
        cout << "There is no possible Euler Circuit for this problem" << endl;
        exit(0);
    }

    circuit(verts, route, edges);


    for(i = 0; i<route.size()-1; i++)
    {
        cout << route[i] << " -> ";
    }

    cout << route[route.size()-1];

    return 0;
}
