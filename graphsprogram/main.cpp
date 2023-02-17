#include <iostream>
#include "graph.h"

int main() {

    /****************************************************************************
     * Robert Book helped me with testing, so the input files are courtesy of him
     ***************************************************************************/
    //names of input files
    string cycle_find_in = "cycleGraph.txt";
    string top_sort_in = "top_sort_in.txt";
    string SSSPUG_in = "SSSPUG_in.txt";
    string Primm_in = "Primm_in.txt";
    string DJKA_in = "DJKA_in.txt";
    string FF_in = "FF_in2.txt";
    string Kruskal_in = "Kruskal_in.txt";
    string Euler_in = "Euler_in.txt";

    //names of output files
    string top_sort_out = "top_sort_out.txt";
    string Primm_out = "Primm_out.txt";
    string Kruskal_out = "Kruskal_out.txt";
    string Euler_out = "Euler_out.txt";

    //ifstream for input files
    ifstream F_cycle_in;
    ifstream F_top_sort_in;
    ifstream F_SSSPUG_in;
    ifstream F_Primm_in;
    ifstream F_DJKA_in;
    ifstream F_FF_in;
    ifstream F_Kruskal_in;
    ifstream F_Euler_in;

    //ofstream for output files
    ofstream F_top_sort_out;
    ofstream F_Primm_out;
    ofstream F_Kruskal_out;
    ofstream F_Euler_out;

    //open input files
    F_cycle_in.open(cycle_find_in);
    if(!F_cycle_in.is_open()){
        cout << "Unable to open input file: " << cycle_find_in;
        exit(0);
    }
    F_top_sort_in.open(top_sort_in);
    if(!F_top_sort_in.is_open()){
        cout << "Unable to open input file: " << top_sort_in;
        exit(0);
    }
    F_SSSPUG_in.open(SSSPUG_in);
    if(!F_SSSPUG_in.is_open()){
        cout << "Unable to open input file: " << SSSPUG_in;
        exit(0);
    }
    F_Primm_in.open(Primm_in);
    if(!F_Primm_in.is_open()){
        cout << "Unable to open input file: " << Primm_in;
        exit(0);
    }
    F_DJKA_in.open(DJKA_in);
    if(!F_DJKA_in.is_open()){
        cout << "Unable to open input file: " << DJKA_in;
        exit(0);
    }
    F_FF_in.open(FF_in);
    if(!F_FF_in.is_open()){
        cout << "Unable to open input file: " << FF_in;
        exit(0);
    }
    F_Kruskal_in.open(Kruskal_in);
    if(!F_Kruskal_in.is_open()){
        cout << "Unable to open input file: " << Kruskal_in;
        exit(0);
    }
    F_Euler_in.open(Euler_in);
    if(!F_Euler_in.is_open()){
        cout << "Unable to open input file: " << Euler_in;
        exit(0);
    }

    //open output files
    F_top_sort_out.open(top_sort_out);
    if(!F_top_sort_out.is_open()){
        cout << "Unable to open output file: " << top_sort_out;
        exit(0);
    }
    F_Primm_out.open(Primm_out);
    if(!F_Primm_out.is_open()){
        cout << "Unable to open output file: " << Primm_out;
        exit(0);
    }
    F_Kruskal_out.open(Kruskal_out);
    if(!F_Kruskal_out.is_open()){
        cout << "Unable to open output file: " << Kruskal_out;
        exit(0);
    }
    F_Euler_out.open(Euler_out);
    if(!F_Euler_out.is_open()){
        cout << "Unable to open output file: " << Euler_out;
        exit(0);
    }

    //graphs for each function in
    graph find_cycles_graph = read_dot(F_cycle_in);
    graph top_sort_graph = read_dot(F_top_sort_in);
    graph SSSPUG_graph = read_dot( F_SSSPUG_in);
    graph Primm_graph = read_dot(F_Primm_in);
    graph DJKA_graph = read_dot(F_DJKA_in);
    graph FF_graph = read_dot(F_FF_in);
    graph Kruskal_graph = read_dot(F_Kruskal_in);
    graph Euler_graph = read_dot(F_Euler_in);

    //Cycle Finding
    vector<vector<int>> cycles;
    int num_cycles = find_cycles(find_cycles_graph, cycles);
    cout << endl << "Cycle Finding: " << endl;
    cout << endl << "There are " << num_cycles << " cycles in " << cycle_find_in << endl;

    for(int i = 0; i < cycles.size(); i++){
        cout << endl << "Cycle " << i + 1 << ": ";
        for(int j = 0; j < cycles[i].size(); j++ ){
            cout << cycles[i][j];
            if(j != cycles[i].size() - 1)
                cout << " -> ";
        }
    }

    //Topological Sort
    topsort(top_sort_graph);
    dot_out(F_top_sort_out, top_sort_graph);
    cout << endl << endl << "Topological sort solution written to file: top_sort_out.txt" << endl;

    //Single-Source Shortest-Path unweighted graph
    vector<vector<int>> shortest_paths = UW_shortest_path(SSSPUG_graph, 0);

    cout << endl << endl;
    cout << "Single-Source Shortest-Path unweighted graph: " << endl;
    cout << "Start: 1" << endl;
    for(int i = 0; i < shortest_paths.size(); i++){
        cout << endl << "Shortest path from 1 to " << i << ": ";
        for(int j = 0; j < shortest_paths[i].size(); j++){
            cout << shortest_paths[i][j];
            if(j != shortest_paths[i].size() - 1){
                cout << " -> ";
            }
        }
    }


    //Prim's Algorithm
    graph Primm_graph_out = PrimsAlgorithm(Primm_graph, 0);
    dot_out(F_Primm_out, Primm_graph_out);
    cout << endl << endl << "Prim's Algorithm solution written to: Primm_out.txt" << endl;

    //Dijkstra's Algorithm
    vector<vector<int>> shortest_weight_paths = DijksatraAlgorithm(DJKA_graph, 0);
    cout << endl << endl;
    cout << "Dijkstra's Algorithm: " << endl;
    cout << "Start: 1"<< endl;
    for(int i = 0; i < shortest_weight_paths.size(); i++){
        cout << endl << "From 1 to " << i << ": ";
        for(int j = 0; j < shortest_weight_paths[i].size(); j++){
            cout << shortest_weight_paths[i][j];
            if(j != shortest_weight_paths[i].size() - 1){
                cout << " -> ";
            }
        }
    }

    //Ford-Fulkerson algorithm
    int max_flow = Ford_Fulk_algorithm(FF_graph, 0, 5);
    cout << endl << endl;
    cout << "Ford-Fulkerson's Algorithm:" << endl;
    cout << "Maximum flow allowed from source to sink in " << FF_in << ": " << max_flow << endl;

    //Kruskal's Algorithm
    graph Kruskal_out_graph = Kruskal_algorithm(Kruskal_graph);
    dot_out(F_Kruskal_out, Kruskal_out_graph);
    cout << endl << endl << "Kruskal's Algorithm solution written to: Kruskal_out.txt" << endl;

    //Euler circuits
    graph Euler_out_graph = Fleury_algorithm(Euler_graph);
    dot_out(F_Euler_out, Euler_out_graph);
    cout << endl << endl << "Euler Circuit solution written to: Euler_out.txt" << endl;

    cout << endl << endl;
    return 0;
}