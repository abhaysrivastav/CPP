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

---

## 10. BFS — Breadth First Search

### Intuition:
> "Visit all nodes at the current level before going deeper — like ripples in water."

Like a family tree — visit all children first, then all grandchildren.

### DFS vs BFS:
| | DFS | BFS |
|---|---|---|
| Strategy | Go deep first | Level by level |
| Data structure | Recursion (implicit stack) | Queue (explicit) |
| Time | O(V + E) | O(V + E) |
| Space | O(V + E) + call stack | O(V + E) |

---

### BFS Algorithm (pseudocode):
```
bfs(start):
    create visited vector (size V, all false)
    create queue

    mark start as visited        ← mark BEFORE enqueuing
    push start to queue

    while queue not empty:
        node = front of queue
        pop from queue
        print node

        for each neighbour of node:
            if not visited:
                visited[neighbour] = true   ← mark BEFORE enqueuing
                push neighbour into queue
```

### Key insight — mark visited BEFORE pushing:
```
❌ Wrong: mark when processing → same node can be added to queue multiple times
✅ Right: mark when enqueuing  → each node added exactly once
```

---

### C++ Implementation:
```cpp
void bfs(int start) {
    vector<bool> visited(V, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (int neighbour : adj[node]) {
            if (!visited[neighbour]) {
                visited[neighbour] = true;
                q.push(neighbour);
            }
        }
    }
}
```

### Queue operations used:
```cpp
q.push(x);    // enqueue
q.front();    // peek front element
q.pop();      // remove front element
q.empty();    // check if queue is empty
```

---

### BFS Trace Example:
```
Graph: 0-1, 0-4, 1-2, 1-3, 3-4
Start: node 0

Queue: [0]          visited: [T,F,F,F,F]
Dequeue 0, print 0
  Push 1 → Queue: [1]       visited: [T,T,F,F,F]
  Push 4 → Queue: [1,4]     visited: [T,T,F,F,T]

Dequeue 1, print 1
  0 visited, skip
  Push 2 → Queue: [4,2]     visited: [T,T,T,F,T]
  Push 3 → Queue: [4,2,3]   visited: [T,T,T,T,T]
  4 visited, skip

Dequeue 4, print 4
  0,3 already visited, skip

Dequeue 2, print 2
  1,3 already visited, skip

Dequeue 3, print 3
  all neighbours visited, skip

Output: 0 1 4 2 3

Levels:
  Level 0: 0
  Level 1: 1, 4    ← neighbours of 0
  Level 2: 2, 3    ← neighbours of 1 and 4
```


Question 1:

If you call dfs(0, visited) on the graph above, which nodes get visited?

if I will call dfs(0, visited) on the graph , then nodes which are connected to the 0 will get visited 


Question 2:

After that DFS finishes, which nodes are still false in visited?
 nodes 4 , 5 and 6 will be unvisited 


Question 3:

What does finding an unvisited node after a DFS tell you?
dfs will tell that other nodes are not connected to the current source , so that can not be visisted, so we should call dfs to the next unvisited node as source 


countComponents():
    create visited vector
    count = 0

    for each node 0 to V-1:
        if node not visited:
            dfs(node, visited)     ← what two things happen here?
            count++

    return count

