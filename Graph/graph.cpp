#include <iostream>
#include <vector>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adj;

    // private helper — called recursively
    void dfs(int node, vector<bool>& visited) 
    {
        visited[node] = true;
        std::cout << node << " " ;
        for(int neighbour : adj[node])
        {
             if(!visited[neighbour]){
                dfs(neighbour, visited);
            }

        }
    }

public:
    Graph(int vertices) {
        V = vertices;
        adj = std::vector<vector<int>>(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // public entry point — sets up visited and kicks off dfs
    void runDFS(int start) {
        // TODO 1: create visited vector of size V, all false
        // TODO 2: call dfs(start, visited)
        std::vector<bool> visited(V, false);
        dfs(start, visited);

    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    cout << "DFS starting from node 0: ";
    g.runDFS(0);
    cout << endl;

    return 0;
}
