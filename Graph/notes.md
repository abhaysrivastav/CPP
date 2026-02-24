# Graph — DFS Notes

---

## 1. Adjacency List Representation

Each node stores a list of its **neighbours**.

```
Graph:
0 --- 1 --- 2
|         |
4 --- 3---/

adj[0] → [1, 4]
adj[1] → [0, 2, 3]
adj[2] → [1, 3]
adj[3] → [1, 2, 4]
adj[4] → [0, 3]
```

### Data structure used:
```cpp
vector<vector<int>> adj;  // V slots, each holds a list of neighbours
```

### Why not adjacency matrix?
| | Adjacency List | Adjacency Matrix |
|---|---|---|
| Space | O(V + E) ✅ | O(V²) ❌ |
| Best for | Sparse graphs | Dense graphs |

---

## 2. Graph Class Structure

```cpp
class Graph {
private:
    int V;
    vector<vector<int>> adj;
    void dfs(int node, vector<bool>& visited);  // private helper

public:
    Graph(int vertices);
    void addEdge(int u, int v);
    void runDFS(int start);  // public entry point
};
```

### Key design decisions:
- `dfs` is **private** — it's an internal helper
- `runDFS` is **public** — it sets up `visited` and kicks off DFS
- `visited` is passed by **reference** — so all recursive calls share the same visited array

---

## 3. Constructor

```cpp
Graph(int vertices) {
    V = vertices;
    adj = vector<vector<int>>(V);  // V slots, each an empty vector<int>
}
```

---

## 4. addEdge (Undirected)

```cpp
void addEdge(int u, int v) {
    adj[u].push_back(v);  // v is a neighbour of u
    adj[v].push_back(u);  // u is a neighbour of v (undirected = both directions)
}
```

For a **directed** graph → remove the second line.

---

## 5. DFS — Depth First Search

### Intuition:
> "Go as deep as possible into one path, backtrack when stuck, try the next path."

Like navigating a maze — always go deeper until dead end, then backtrack.

### Algorithm (pseudocode):
```
dfs(node, visited):
    mark node as visited
    print node
    for each neighbour of node:
        if neighbour not visited:
            dfs(neighbour, visited)
```

### C++ Implementation:
```cpp
void dfs(int node, vector<bool>& visited) {
    visited[node] = true;
    cout << node << " ";
    for (int neighbour : adj[node]) {
        if (!visited[neighbour]) {
            dfs(neighbour, visited);
        }
    }
}
```

---

## 6. runDFS — Entry Point

```cpp
void runDFS(int start) {
    vector<bool> visited(V, false);  // all nodes unvisited initially
    dfs(start, visited);
}
```

---

## 7. Handling Disconnected Components

If graph is **disconnected**, DFS from one node won't reach all nodes.

### Fix — loop over all nodes:
```cpp
void runDFS() {
    vector<bool> visited(V, false);
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(i, visited);  // new component found
        }
    }
}
```

```
Graph:
0 --- 1 --- 2       4 --- 5
             (disconnected)

DFS from 0 visits: 0, 1, 2
Loop finds 4 unvisited → DFS from 4 visits: 4, 5
```

---

## 8. DFS Trace Example

```
Graph: 0-1, 0-4, 1-2, 1-3, 3-4
Start: node 0

dfs(0) → visited[0]=T → explore neighbours [1,4]
  dfs(1) → visited[1]=T → explore neighbours [0,2,3]
    0 already visited, skip
    dfs(2) → visited[2]=T → explore neighbours [1,3]
      1 already visited, skip
      dfs(3) → visited[3]=T → explore neighbours [1,2,4]
        1,2 already visited, skip
        dfs(4) → visited[4]=T → explore neighbours [0,3]
          0,3 already visited, skip ↩
        ↩ back to 3
      ↩ back to 2
    ↩ back to 1
  ↩ back to 0

Output: 0 1 2 3 4
```

---

## 9. Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| Time | O(V + E) | Every node visited once (V), every edge checked once (E) |
| Space | O(V + E) | adj list (V+E) + visited vector (V) + recursion stack (V) |

### Recursion stack worst case:
```
Linear chain: 0 → 1 → 2 → 3 → ... → V
Depth = V → O(V) stack space
```
