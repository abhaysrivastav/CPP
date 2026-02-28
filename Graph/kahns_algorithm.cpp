#include <vector>
#include <queue>
#include <iostream>
using namespace std;

// ============================================================
// KAHN'S ALGORITHM — Step-by-step guided implementation
// Work through each step in order. Read the hint before coding.
// ============================================================


// ----------------------------------------------------------------
// STEP 1: Compute In-Degrees
// ----------------------------------------------------------------
// Intuition: For every directed edge A → B, node B has one more
//            "dependency". Count how many dependencies each node has.
//
// Task: Fill in the loop body.
//       edges[i] = {from, to}  →  which end gets its count incremented?
// ----------------------------------------------------------------
vector<int> computeIndegree(int n, vector<vector<int>>& edges) {
    vector<int> indegree(n, 0);

    for (auto& edge : edges) {
        // TODO: increment the in-degree of the destination node
        indegree[edge[1]]++;
    }

    return indegree;
}


// ----------------------------------------------------------------
// STEP 2: Build Adjacency List
// ----------------------------------------------------------------
// Intuition: You need to know, for each node, which nodes it points TO.
//            When you "finish" a node, you'll visit its neighbors.
//
// Task: For each edge A → B, record B in adj[A].
// ----------------------------------------------------------------
vector<vector<int>> buildAdjList(int n, vector<vector<int>>& edges) {
    vector<vector<int>> adj(n);

    for (auto& edge : edges) {
        // TODO: add the destination to adj[source]
        adj[edge[0]].push_back(edge[1]);
    }

    return adj;
}


// ----------------------------------------------------------------
// STEP 3: Initialize the Queue
// ----------------------------------------------------------------
// Intuition: Nodes with in-degree 0 have NO dependencies.
//            They are safe to process immediately — seed the BFS with them.
//
// Task: Loop through all nodes. Which ones go into the queue first?
// ----------------------------------------------------------------
queue<int> initQueue(vector<int>& indegree) {
    queue<int> q;

    // TODO: enqueue every node whose in-degree is 0
    for(int i =0 ; i < indegree.size(); i++)
    {
        if(indegree[i] == 0)
        {
            q.push(i);
        }
    }

    return q;
}


// ----------------------------------------------------------------
// STEP 4: BFS — the core of Kahn's algorithm
// ----------------------------------------------------------------
// Intuition:
//   - Dequeue a node u  → it's "done", add it to the result.
//   - For each neighbor v of u: u is no longer a dependency of v,
//     so decrement indegree[v].
//   - If indegree[v] becomes 0, v is now free → enqueue it.
//
// Task: Fill in the while-loop body using the three sub-steps above.
// ----------------------------------------------------------------
vector<int> bfs(int n,
                vector<vector<int>>& adj,
                vector<int>& indegree,
                queue<int>& q) {
    vector<int> result;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // TODO 4a: record u in result
        result.push_back(u);

        for (int v : adj[u]) {
            // TODO 4b: remove u's contribution to v's in-degree
            indegree[v]--;

            // TODO 4c: if v has no more dependencies, enqueue it
            if(indegree[v] == 0) q.push(v);
        }
    }

    return result;
}


// ----------------------------------------------------------------
// STEP 5: Tie it all together + cycle detection
// ----------------------------------------------------------------
// Intuition: If the graph has a cycle, the nodes in that cycle
//            will NEVER reach in-degree 0, so the queue empties
//            before all nodes are processed.
//
// Task: Call steps 1-4 in order, then check whether the result
//       contains all n nodes. If not, a cycle exists.
// ----------------------------------------------------------------
vector<int> topologicalSort(int n, vector<vector<int>>& edges) {

    // TODO: compute in-degrees (call computeIndegree)
    vector<int> indegree = computeIndegree(n,edges);


    // TODO: build adjacency list (call buildAdjList)
    vector<vector<int>> adj = buildAdjList(n,edges);


    // TODO: initialize the queue (call initQueue)
    queue<int> q = initQueue(indegree);

    // TODO: run BFS (call bfs)
    vector<int> result = bfs(n,adj,indegree, q);

    // TODO: cycle check — return result if valid, else return {}

    if(result.size() == n) return result;
    else return {};
}


// ----------------------------------------------------------------
// Test your implementation here
// ----------------------------------------------------------------
// Graph:  0 → 2 → 5
//          \       ↑
//           → 3 ───┘ ← 4 ← 1
//
// Expected topological order: [0, 1, 2, 3, 4, 5]  (one valid order)
// ----------------------------------------------------------------
int main() {
    int n = 6;
    vector<vector<int>> edges = {
        {0, 2}, {0, 3},
        {1, 3}, {1, 4},
        {2, 5}, {3, 5}, {4, 5}
    };

    vector<int> order = topologicalSort(n, edges);

    if (order.empty()) {
        cout << "Cycle detected! No topological order exists." << endl;
    } else {
        cout << "Topological order: ";
        for (int node : order) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
