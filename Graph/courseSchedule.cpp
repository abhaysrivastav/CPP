#include <iostream>
#include <vector>
using namespace std;

bool dfs(int node, vector<vector<int>>& adj, vector<int>& state) {
    // ① Mark node as IN_STACK
    state[node] = 1;

    for(int neighbour : adj[node]) {
        if(state[neighbour] == 1)  // ② neighbour is IN_STACK
            return true;            //    what does this mean?

        if(state[neighbour] == 0)  // ③ unvisited
            if(dfs(neighbour, adj, state))
                return true;
    }

    // ④ Mark node as DONE
    state[node] = 2;
    return false;
}

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adjList(numCourses);
    // 1. Build adjacency list (directed: prereq[1] → prereq[0])
    for(auto& dependencies: prerequisites)
    {
        adjList[dependencies[0]].push_back(dependencies[1]);
    }
    // 2. Create a state array: 0=unvisited, 1=in_stack, 2=done
    //std::vector<bool> visited(numCourses, 0);
    std::vector<int> state(numCourses, 0);
    
    // 3. For each unvisited node, run DFS
    for(int i=0; i < numCourses; i++)
    {
        if(state[i] == 0)
        {
            if(dfs(i, adjList, state))      
                return false; 
        }
        
    }
    return true;
}

int main() {
    // Test 1: simple prereq, no cycle → true
    vector<vector<int>> p1 = {{1, 0}};
    cout << "Test 1 (expected true):  " << (canFinish(2, p1) ? "true" : "false") << endl;

    // Test 2: direct cycle 0→1→0 → false
    vector<vector<int>> p2 = {{1, 0}, {0, 1}};
    cout << "Test 2 (expected false): " << (canFinish(2, p2) ? "true" : "false") << endl;

    // Test 3: longer cycle 0→1→2→3→1 → false
    vector<vector<int>> p3 = {{1, 0}, {2, 1}, {3, 2}, {1, 3}};
    cout << "Test 3 (expected false): " << (canFinish(4, p3) ? "true" : "false") << endl;

    // Test 4: single course, no prereqs → true
    vector<vector<int>> p4 = {};
    cout << "Test 4 (expected true):  " << (canFinish(1, p4) ? "true" : "false") << endl;

    return 0;
}
