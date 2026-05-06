#include <iostream>
#include <omp.h>
#include <vector>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // BFS
    void parallelBFS(int start) {
        vector<bool> visited(V, false);
        vector<int> curr_level, next_level;

        visited[start] = true;
        curr_level.push_back(start);

        while (!curr_level.empty()) {
            next_level.clear();
            
            #pragma omp parallel for
            for (int i = 0; i < curr_level.size(); i++) {
                int node = curr_level[i];
                cout << node << " ";

                for (auto adj_node: adj[node]) {
                    if (!visited[adj_node]) {
                        #pragma omp critical
                        {
                            visited[adj_node] = true;
                            next_level.push_back(adj_node);
                        }
                    }   
                }
            }
            curr_level = next_level;
        }
        cout << endl;
    }

    // DFS
    void dfsUtils(int node, vector<bool> &visited) {
        visited[node] = true;
        cout << node << " ";

        for (auto adj_node : adj[node]) {
            bool should_visit = false;

            #pragma omp critical
            {
                if (!visited[adj_node]) {
                    #pragma omp task
                    dfsUtils(adj_node, visited);
                }
            }
            if (should_visit) {
                #pragma omp task
                dfsUtils(adj_node, visited);
            }
        }
    }

    void parallelDfs(int start) {
        vector<bool> visited(V, false);
        
        #pragma omp parallel
        {
            #pragma omp single
            {
                dfsUtils(start, visited);
            }
        }
        cout << endl;
    }
};

int main() {
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;
    Graph g(V);

    cout << "Enter number of edges: ";
    int E;
    cin >> E;

    for (int i = 0; i < E; ++i) {
        int u, v;
        cout << "Enter edge (u v), eg. 0 1: ";
        cin >> u >> v;
        g.addEdge(u, v);
    }

    g.parallelBFS(0);

    cout << "DFS---> " << endl;
    g.parallelDfs(0);
    return 0;
}