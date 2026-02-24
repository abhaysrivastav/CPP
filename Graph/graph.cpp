#include <iostream>
#include <vector>
#include <queue>
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

    void bfs(int start){
        std::vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while(!q.empty())
        {
            int temp = q.front();
            q.pop();

            std::cout << " " << temp;

            for(int neighbour : adj[temp])
            {
                if(!visited[neighbour])
                {
                    visited[neighbour] = true;
                    q.push(neighbour);
                }
            }

        }

    }

    int countComponent()
    {
        vector<bool> visited(V, false);
        int count = 0;

        for(int i=0; i< V; i++)
        {
            if(!visited[i])
            {
                dfs(i, visited);
                count++;
            }
        }
        return count;
    }


};

int main() {
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(5, 6);

    cout << "DFS starting from node 0: ";
    g.runDFS(0);
    cout << endl;

    cout << "BFS starting from node 0: ";
    g.bfs(0);
    cout << endl;

    cout << "Number of components: " << g.countComponent() << endl;

    return 0;
}
