# Binary Tree Level Order Traversal - Interview Notes 🎯

## Problem Type
- **Breadth-First Search (BFS)** on a binary tree
- Return values level by level (left to right)

---

## 🔑 Key Concepts

### 1. Level Order Traversal
- Visit all nodes at each depth before going deeper
- Output: `vector<vector<int>>` (one vector per level)

### 2. Data Structure: Queue
- Use `queue<TreeNode*>` for BFS
- FIFO: process nodes in the order they were added

### 3. Level Separation
- At each iteration, `queue.size()` gives number of nodes at current level
- Process exactly `size` nodes, then add their children for next level

---

## 📋 Template: BFS Level Order

```cpp
vector<vector<int>> levelOrder(TreeNode* root) {
    if (!root) return {};
    vector<vector<int>> result;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        vector<int> level;
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front(); q.pop();
            level.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(level);
    }
    return result;
}
```

---

## 💡 Key Interview Points

- **Why queue?**
  - Ensures left-to-right, level-by-level order
- **Why use `queue.size()`?**
  - Separates levels cleanly
- **Edge cases:**
  - Empty tree → return `{}`
  - Single node → `[[val]]`
- **Time Complexity:** O(n) (every node visited once)
- **Space Complexity:** O(w) (max width of tree in queue)

---

## 🚨 Common Mistakes

❌ Using stack (gives DFS, not BFS)
❌ Not separating levels (all values in one vector)
❌ Forgetting to check for empty tree

---

## 🎓 Related Patterns

- Zigzag Level Order (LC 103): alternate left/right
- Level Order Bottom-Up (LC 107): reverse result
- Average of Levels (LC 637): compute average per level

**Pro Tip:** Master BFS with queue for all level-based tree problems! 🚀
