#include "graph.h"

graph create_graph(int vertex_num){
    graph newGraph;
    newGraph.v_num = vertex_num;
    newGraph.matrix.resize(vertex_num);
    for(int i = 0; i < vertex_num; i++){
        newGraph.matrix[i].resize(vertex_num);
    }
    return newGraph;
}
//find cycles
int find_cycles(graph inGraph, vector<vector<int>>& cycles){
    vector<int> temp_cycle;
    vector<int> all_next;
    stack<int> pathing;
    int num_visited = 0;
    int num_cycles = 0, count = 0;
    int curr_v, next_v;
    vector<bool> visited;
    int num_next = 0;

    visited.resize(inGraph.v_num, false);
    curr_v = find_first_v(inGraph);
    while(num_visited < inGraph.v_num){
        pathing.push(curr_v);
        visited[curr_v] = true;
        num_visited++;
        num_next = num_next_v(inGraph, curr_v, all_next);
        next_v = all_next.back();
        all_next.pop_back();

        if(visited[next_v]){ //we found a cycle!
            temp_cycle.insert(temp_cycle.begin(),next_v);
            while(pathing.top() != next_v){
                temp_cycle.insert(temp_cycle.begin(), pathing.top());
                pathing.pop();
            }
            temp_cycle.insert(temp_cycle.begin(), pathing.top());
            pathing.pop();
            cycles.push_back(temp_cycle);
            num_cycles++;
            temp_cycle.clear();
            if(all_next.size() == 0){ //no more forks, we found the last cycle
                return num_cycles;
            }
            else {
                next_v = all_next.back();
                all_next.pop_back();
            }

        }
        curr_v = next_v;


    }
    return num_cycles;

}

//topsort
vector<int> topsort(graph& inGraph){
    queue<int> q;
    int counter = 0;
    vector<int> topNum;
    vector<int> inDegs;

    topNum.resize(inGraph.v_num, -1);
    inDegs.resize(inGraph.v_num, 0);

    //first find all vertexes with in-degree 0
    for(int i = 0; i < inGraph.matrix.size(); i++){
        int in_deg = get_in_deg(inGraph, i);
        inDegs[i] = in_deg;
        if(in_deg == 0)
            q.push(i);
    }

    while(!q.empty()){
        int v = q.front();
        q.pop();
        topNum[v] = ++counter;

        for(int i = 0; i < inGraph.matrix[v].size(); i++){
            if(inGraph.matrix[v][i] == 1){
                if( --inDegs[i] == 0)
                    q.push(i);
            }
        }

    }
    if(counter != inGraph.v_num){
        cout << "Cycle found while attempting to topSort. \nExiting Program\n";
        exit(1);
    }



    return topNum;
}

//single_source Shortest_path unweighted graph
vector<vector<int>> UW_shortest_path(graph inGraph, int start_vert){
    vector<vector<int>> shortest_paths;
    SSSPUG_table table = create_SSSPUG_table(inGraph.v_num);
    table.distances[start_vert] = 0;
    vector<int> path_to_node;

    for(int currDist = 0; currDist < inGraph.v_num; currDist++){
        for(int v = 0; v < inGraph.v_num; v++){
            if(!table.visited[v] && table.distances[v] == currDist){
                table.visited[v] = true;
                for(int w = 0; w < inGraph.matrix[v].size(); w++){
                    if(inGraph.matrix[v][w] == 1 && table.distances[w] == INT_MAX){
                        table.distances[w] = currDist + 1;
                        table.path[w] = v;
                    }
                }
            }
        }
    }

    int curr_vert;
    for(int i = 0; i < inGraph.matrix.size(); i++){
        path_to_node.clear();
        curr_vert = i;
        while(curr_vert != start_vert) {
            path_to_node.insert(path_to_node.begin(), curr_vert);
            curr_vert = table.path[curr_vert];
        }
        path_to_node.insert(path_to_node.begin(), start_vert);
        shortest_paths.push_back(path_to_node);
    }

    return shortest_paths;
}

//Prims Algorithm
graph PrimsAlgorithm(graph inGraph, int start){
    PrimTable table = create_PrimTable(inGraph.v_num);
    graph out_graph = create_graph(inGraph.v_num);
    out_graph.weighted = true;
    out_graph.graph_name = inGraph.graph_name + " Prim's Algorithm";
    out_graph.graph_type = inGraph.graph_type;
    int num_known = 0;
    int cur_vert = start;
    int min_weight;

    table.weight[start] = 0;
    while(num_known < inGraph.v_num){ //while there are unknown verts
        min_weight = INT_MAX;
        //mark curr_vert as known
        table.known[cur_vert] = true;
        //mark all verts that are attatched to cur_vert with their weights and path if they are unvisited and weight < cur_weight
        for(int i = 0; i < inGraph.matrix[cur_vert].size(); i++){
            if(inGraph.matrix[cur_vert][i] > 0 && !table.known[i] && inGraph.matrix[cur_vert][i] < table.weight[i]){
                table.weight[i] = inGraph.matrix[cur_vert][i];
                table.path[i] = cur_vert;
            }
        }
        //get next vert
        for(int i = 0; i < table.known.size(); i++){
            if(table.weight[i] < min_weight && !table.known[i]){
                cur_vert = i;
                min_weight = table.weight[i];
            }
        }
        num_known++;
    }
    //convert to min spanning tree
    int prev_vert = -1;
    for(int i = 0; i < out_graph.v_num; i++){
        prev_vert = table.path[i];
        out_graph.matrix[i][prev_vert] = table.weight[i];
        out_graph.matrix[prev_vert][i] = table.weight[i];
    }
    return out_graph;


}

///* other functions used for previous main functions *///
int find_first_v(graph inGraph){
    for(int i = 0; i < inGraph.matrix.size(); i++){
        for(int j = 0; j < inGraph.matrix[i].size(); j++) {
            if (inGraph.matrix[i][j] > 0)
                return i;
        }
    }
    return -1;
}

int num_next_v(graph inGraph, int start, vector<int>& all_next){
    int count = 0;
    for(int i = 0; i < inGraph.matrix[start].size(); i++){
        if(inGraph.matrix[start][i] > 0){
            count++;
            all_next.push_back(i);
        }
    }
    return count;
}

int get_in_deg(graph inGraph, int vert){
    int count = 0;
    for(int i = 0; i < inGraph.matrix[vert].size(); i++){
        if(inGraph.matrix[i][vert] > 0)
            count++;
    }
    return count;
}

SSSPUG_table create_SSSPUG_table(int num_verts){
    SSSPUG_table new_table;
    for(int i = 0; i < num_verts; i++){
        new_table.distances.push_back(INT_MAX);
        new_table.visited.push_back(false);
        new_table.path.push_back(-1);
    }
    return new_table;
}

PrimTable create_PrimTable(int num_verts){
    PrimTable new_table;
    for(int i = 0; i < num_verts; i++){
        new_table.known.push_back(false);
        new_table.weight.push_back(INT_MAX);
        new_table.path.push_back(0);
    }
    return new_table;
}
//DOT files read in
graph read_dot(ifstream& fin){
    vector<vector<int>> edges;
    vector<int> temp_edge;
    vector<int> verts;
    graph out_graph;
    string inGraphName;
    string inGraphType;
    string inVert1, inVert2;
    bool directed = false, weighted = false;


    //get graph type and name
    fin >> inGraphType >> inGraphName;


    if(inGraphType == "digraph")
        directed = true;
    else if(inGraphType == "graph")
        directed = false;
    else{
        cout << "Unrecognized type of graph" << endl;
        exit(1);
    }

    fin.ignore(256, '\n');
    while(fin >> inVert1 && inVert1 != "}"){
        temp_edge.clear();
        if(directed){
            fin.ignore(256, '>'); //skip until next vert input
        }
        else{
            fin.get();
            fin.get();
            fin.get();
        }
        fin >> inVert2;
        temp_edge.push_back(stoi(inVert1));
        temp_edge.push_back(stoi(inVert2));
        fin.get();

        if(fin.peek() == '['){
            fin.ignore(256, '=');
            fin >> inVert1;
            temp_edge.push_back(stoi(inVert1));
            fin.ignore(256, '\n');
        }
        edges.push_back(temp_edge);
    }

    //fill array with all vertices
    for(int i = 0; i < edges.size(); i++){
        if(edges[i].size() > 2)
            weighted = true;
        if(!in_vec(verts, edges[i][0]))
            verts.push_back(edges[i][0]);
        if(!in_vec(verts, edges[i][1]))
            verts.push_back(edges[i][1]);
    }


    out_graph = create_graph(verts.size());
    out_graph.graph_name = inGraphName;
    out_graph.e_num = edges.size();
    out_graph.graph_type = inGraphType;
    if(directed) {
        for (int i = 0; i < edges.size(); i++) {
            if (weighted)
                out_graph.matrix[edges[i][0]][edges[i][1]] = edges[i][2];
            else
                out_graph.matrix[edges[i][0]][edges[i][1]] = 1;
        }
    }
    else{
        for(int i = 0; i < edges.size(); i++){
            if(weighted){
                out_graph.matrix[edges[i][0]][edges[i][1]] = edges[i][2];
                out_graph.matrix[edges[i][1]][edges[i][0]] = edges[i][2];
            }
            else{
                out_graph.matrix[edges[i][0]][edges[i][1]] = 1;
                out_graph.matrix[edges[i][1]][edges[i][0]] = 1;
            }
        }
    }

    return out_graph;
}

//Dijkstra's Algorithm
vector<vector<int>> DijksatraAlgorithm(graph inGraph, int vert){
    DJKATable table;
    int num_known = 0;
    int min_dist = INT_MAX;
    int curr_vert = vert;
    int cvw = 0;

    table.known.resize(inGraph.v_num);
    table.dist.resize(inGraph.v_num);
    table.path.resize(inGraph.v_num);
    vector<int> temp_path_vec;
    vector<vector<int>> all_paths;

    for(int i = 0; i < inGraph.v_num; i++){
        table.adj.push_back(inGraph.matrix[i]);
    }

    for(int i = 0; i < inGraph.v_num; i++){
        table.dist[i] = INT_MAX;
        table.known[i] = false;
    }

    table.dist[vert] = 0;

    while(num_known < inGraph.v_num){
        min_dist = INT_MAX;
        for(int i = 0; i < inGraph.v_num; i++){
            if(!table.known[i] && table.dist[i] < min_dist){
                curr_vert = i;
                min_dist = table.dist[i];
            }
        }

        table.known[curr_vert] = true;
        num_known++;

        for(int i = 0; i < inGraph.v_num; i++){
            if(inGraph.matrix[curr_vert][i] > 0){
                if(!table.known[i]){
                    cvw = inGraph.matrix[curr_vert][i];
                    if(table.dist[curr_vert] + cvw < table.dist[i]){
                        table.dist[i] = table.dist[curr_vert] + cvw;
                        table.path[i] = curr_vert;
                    }
                }
            }
        }
    }

    for(int i = 0; i < inGraph.v_num; i++){
        temp_path_vec.clear();
        curr_vert = i;
        while(curr_vert != vert){
            temp_path_vec.insert(temp_path_vec.begin(), curr_vert);
            curr_vert = table.path[curr_vert];
        }
        temp_path_vec.insert(temp_path_vec.begin(), vert);
        all_paths.push_back(temp_path_vec);
    }
    return all_paths;
}
//Ford-Fulkerson Algorithm
int Ford_Fulk_algorithm(graph& inGraph, int s, int t){
    int u, v;
    int parent[inGraph.v_num];
    graph residualGraph = create_graph(inGraph.v_num);
    int max_flow = 0, path_flow;

    for(int i = 0; i < inGraph.v_num; i++){
        for(int j = 0; j < inGraph.v_num; j++){
            residualGraph.matrix[i][j] = inGraph.matrix[i][j];
        }
    }
    residualGraph.e_num = inGraph.e_num;
    residualGraph.weighted = inGraph.weighted;

    while(path_from_s_to_t(residualGraph, s, t, parent)){
        path_flow = INT_MAX;
        for(v = t; v!= s; v = parent[v]){
            u = parent[v];
            if(residualGraph.matrix[u][v] < path_flow)
                path_flow = residualGraph.matrix[u][v];
        }

        for(v = t; v != s; v = parent[v]){
            u = parent[v];
            residualGraph.matrix[u][v] -= path_flow;
            residualGraph.matrix[v][u] += path_flow;
        }

        max_flow += path_flow;
    }
    return max_flow;
}
//Kruskal's Algorithm
graph Kruskal_algorithm(graph inGraph){
    graph out_graph;
    KruskalTable table;
    vector<int> temp_vec;
    vector<int> vert_set;
    int curr_set = 1, curr_weight = 1;
    int num_edges_accepted = 0;

    //set up table
    for(int i = 0; i < inGraph.v_num; i++){
        for(int j = i; j < inGraph.v_num; j++){
            if(inGraph.matrix[i][j] > 0){
                temp_vec.clear();
                temp_vec.push_back(i);
                temp_vec.push_back(j);
                table.edge.push_back(temp_vec);
                table.weight.push_back(inGraph.matrix[i][j]);
                table.action.push_back(false);
            }
        }
    }

    vert_set.resize(inGraph.v_num, 0);

    while(num_edges_accepted != (inGraph.v_num - 1)){
        for(int i = 0; i < table.edge.size(); i++){
            if(table.weight[i] == curr_weight && !table.action[i]){
                if(vert_set[table.edge[i][0]] == 0  && vert_set[table.edge[i][1]] == 0){ //if neither vertex of edge is in a set
                    vert_set[table.edge[i][0]] = curr_set;
                    vert_set[table.edge[i][1]] = curr_set;
                    curr_set++;
                    table.action[i] = true;
                    num_edges_accepted++;
                }
                else if(vert_set[table.edge[i][0]] == 0 || vert_set[table.edge[i][1]] == 0){  //if one or the other is not in a set
                    if(vert_set[table.edge[i][0]] == 0)
                        vert_set[table.edge[i][0]] = vert_set[table.edge[i][1]];
                    else
                        vert_set[table.edge[i][1]] = vert_set[table.edge[i][0]];
                    table.action[i] = true;
                    num_edges_accepted++;
                }
                else if(vert_set[table.edge[i][0]] != vert_set[table.edge[i][1]]) { // if they are a part of two different sets
                    //combine sets
                    if(vert_set[table.edge[i][0]] < vert_set[table.edge[i][1]])
                        for(int j = 0; j < vert_set.size(); j++){
                            if(vert_set[j] == vert_set[table.edge[i][1]])
                                vert_set[j] = vert_set[table.edge[i][0]];
                        }
                    else
                        for(int j = 0; j < vert_set.size(); j++) {
                            if (vert_set[j] == vert_set[table.edge[i][0]])
                                vert_set[j] = vert_set[table.edge[i][1]];
                        }
                    table.action[i] = true;
                    num_edges_accepted++;
                }
            }
        }
        curr_weight++;
    }
    out_graph = create_graph(inGraph.v_num);
    for(int i = 0; i < table.edge.size(); i++){
        if(table.action[i]) {
            out_graph.matrix[table.edge[i][0]][table.edge[i][1]] = table.weight[i];
            out_graph.matrix[table.edge[i][1]][table.edge[i][0]] = table.weight[i];
            out_graph.e_num++;
        }
    }
    out_graph.graph_name = inGraph.graph_name + " Kruskal Algorithm";
    out_graph.graph_type = inGraph.graph_type;
    out_graph.weighted = inGraph.weighted;

    return out_graph;
}
///* other functions used for previous main functions *///
bool in_vec(vector<int> vec, int data){
    for(int i = 0; i < vec.size(); i++){
        if(vec[i] == data)
            return true;
    }
    return false;
}

//bfs search algorithm from geeks for geeks
bool path_from_s_to_t(graph inGraph, int s, int t, int parent[]){
    vector<bool> visited;
    queue<int> q;
    int u;

    visited.resize(inGraph.v_num, false);
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while(!q.empty()){
        u = q.front();
        q.pop();

        for(int i = 0; i < inGraph.v_num; i++){
            if(visited[i] == false && inGraph.matrix[u][i] > 0){
                if(i == t){
                    parent[i] = u;
                    return true;
                }
                q.push(i);
                parent[i] = u;
                visited[i] = true;
            }
        }
    }

    return false;

}

//Euler circuits
graph Fleury_algorithm(graph inGraph){
    vector<int> num_conn;
    graph graph_out;
    vector<int> path;
    EulerTable table;
    vector<int> temp_vec;
    int count_odd_verts = 0;
    int curr_vert = -1;
    int num_burned_bridges = 0;
    bool found_edge = false;
    int end_vert = -1;

    //set number of connections and initialize table
    num_conn.resize(inGraph.v_num, 0);
    for(int i = 0; i < inGraph.v_num; i++){
        temp_vec.clear();
        for(int j = i; j < inGraph.v_num; j++){
            if(inGraph.matrix[i][j] > 0){
                temp_vec.push_back(i);
                temp_vec.push_back(j);
                table.edges.push_back(temp_vec);
                temp_vec.clear();
                table.edge_visited.push_back(false);
                num_conn[i]++;
                num_conn[j]++;
            }
        }
    }

    for(int i = 0; i < num_conn.size(); i++){
        if(num_conn[i] % 2 == 1) {
            count_odd_verts++;

        }
    }

    if(count_odd_verts > 2 || count_odd_verts == 1){
        cout << "Graph does not have euler circuit or path" << endl;
        exit(2);
    }
    if(count_odd_verts == 0) {
        curr_vert = 0;
        end_vert = 0;
    }
    else{
        for(int i = 0; i < num_conn.size(); i++){
            if(num_conn[i] %2 == 1){
                if(curr_vert == -1)
                    curr_vert = i;
                else
                    end_vert = i;

            }
        }
    }


    while(num_burned_bridges < table.edges.size()){
        path.push_back(curr_vert);
        found_edge = false;
        for(int i = 0; i < table.edges.size() && !found_edge; i++){
            if(table.edges[i][0] == curr_vert && !table.edge_visited[i]){
                if(table.edges[i][1] == end_vert){
                    if(num_conn[end_vert] > 1){
                        curr_vert = table.edges[i][1];
                        table.edge_visited[i] = true;
                        num_burned_bridges++;
                        found_edge = true;
                    }
                    else if(num_burned_bridges == table.edges.size() - 1){
                        curr_vert = table.edges[i][1];
                        table.edge_visited[i] = true;
                        num_burned_bridges++;
                        found_edge = true;
                    }
                }
                else {
                    curr_vert = table.edges[i][1];
                    table.edge_visited[i] = true;
                    num_burned_bridges++;
                    found_edge = true;
                }
                num_conn[table.edges[i][1]]--;
                num_conn[table.edges[i][0]]--;
            }
            else if(table.edges[i][1] == curr_vert && !table.edge_visited[i]){
                if(table.edges[i][0] == end_vert){
                    if(num_conn[end_vert] > 1){
                        curr_vert = table.edges[i][0];
                        table.edge_visited[i] = true;
                        num_burned_bridges++;
                        found_edge = true;
                    }
                    else if(num_burned_bridges == table.edges.size() - 1){
                        curr_vert = table.edges[i][0];
                        table.edge_visited[i] = true;
                        num_burned_bridges++;
                        found_edge = true;
                    }
                }
                else {
                    curr_vert = table.edges[i][0];
                    table.edge_visited[i] = true;
                    num_burned_bridges++;
                    found_edge = true;
                }
                num_conn[table.edges[i][1]]--;
                num_conn[table.edges[i][0]]--;
            }
        }
    }
    path.push_back(curr_vert);

    //convert to graph
    graph_out = create_graph(inGraph.v_num);
    graph_out.graph_name = inGraph.graph_name + " Fleury's Algorithm";
    graph_out.graph_type = "digraph";
    graph_out.v_num = inGraph.v_num;
    graph_out.e_num = inGraph.e_num;
    graph_out.weighted = inGraph.weighted;
    for(int i = 0 ; i < path.size() - 1; i++){
        graph_out.matrix[path[i]][path[i+1]] = 1;
    }
    return graph_out;

}
//outputting to DOT files

void dot_out(ofstream& outFile, graph outGraph){
    outFile << outGraph.graph_type << " " << "\"" << outGraph.graph_name << "\" {\n";
    if(outGraph.graph_type == "graph"){
        for(int i = 0; i < outGraph.v_num; i++){
            for(int j = i; j < outGraph.v_num; j++){
                if(outGraph.matrix[i][j] > 0){
                    outFile << "\t" << i << " -- " << j;
                    if(outGraph.weighted)
                        outFile << " [ label = " << outGraph.matrix[i][j] << " ]";
                    outFile << "\n";
                }
            }
        }
    }
    else{
        for(int i = 0; i < outGraph.v_num; i++){
            for(int j = 0; j < outGraph.v_num; j++){
                if(outGraph.matrix[i][j] > 0){
                    outFile << "\t" << i << " -> " << j;
                    if(outGraph.weighted)
                        outFile << " [ label = " << outGraph.matrix[i][j] << " ]";
                    outFile << "\n";
                }
            }
        }
    }
    outFile << "}";
}