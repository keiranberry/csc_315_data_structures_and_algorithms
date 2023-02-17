#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include <iterator>

using namespace std;


struct graph{
    string graph_name;
    string graph_type;
    int v_num = 0;
    int e_num = 0;
    vector<vector<int>> matrix;
    bool weighted = false;
};

graph create_graph(int vertex_num);

///* other structures used by main functions *///
struct SSSPUG_table{
    vector<int> distances;
    vector<bool> visited;
    vector<int> path;
};

struct PrimTable{
    vector<bool> known;
    vector<int> weight;
    vector<int> path;
};

struct DJKATable{
    vector<vector<int>> adj;
    vector<bool> known;
    vector<int> dist;
    vector<int> path;
};

struct KruskalTable{
    vector<vector<int>> edge;
    vector<int> weight;
    vector<bool> action;
};

struct EulerTable{
    vector<vector<int>> edges;
    vector<bool> edge_visited;
};

SSSPUG_table create_SSSPUG_table(int num_verts);
PrimTable create_PrimTable(int num_verts);

//find cycles
int find_cycles(graph inGraph, vector<vector<int>>& cycles);
//topsort
vector<int> topsort(graph& inGraph);
//single_source Shortest_path unweighted graph
vector<vector<int>> UW_shortest_path(graph inGraph, int start_vert);
//Prims Algorithm
graph PrimsAlgorithm(graph inGraph, int start_vert);

///* other functions used for previous main functions *///
int find_first_v(graph inGraph);
int num_next_v(graph inGraph, int start, vector<int>& all_next);
int get_in_deg(graph inGraph, int vert);

//DOT files read in
graph read_dot(ifstream& fin);
//Dijkstra's Algorithm
vector<vector<int>> DijksatraAlgorithm(graph inGraph, int vert);
//Ford-Fulkerson Algorithm
int Ford_Fulk_algorithm(graph& inGraph, int source, int sink);
//Kruskal's Algorithm
graph Kruskal_algorithm(graph inGraph);

///* other functions used for previous main functions *///
bool in_vec(vector<int> vec, int data);

bool path_from_s_to_t(graph residual_graph, int s, int t, int parent[]);

//Euler circuits
graph Fleury_algorithm(graph inGraph);
//outputting to DOT files
void dot_out(ofstream& outFile, graph outGraph);
