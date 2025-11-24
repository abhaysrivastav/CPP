# Lowest Common Ancestor (LCA) in Binary Search Tree - Interview Notes 🎯

## Problem Type
- **BST-Specific LCA Problem**
- Find the lowest common ancestor of two nodes in a BST
- Exploits BST property for efficient O(h) solution

---

## 🔑 Key Concepts

### 1. What is LCA?
- The **lowest node** in the tree that has both `p` and `q` as descendants.
- A node can be a descendant of itself.
- In BST, LCA is the first node where paths to `p` and `q` diverge.

### 2. BST Property Exploitation
- **Left subtree**: All values < current node
- **Right subtree**: All values > current node
- Use this to decide direction without searching both subtrees

### 3. Decision Logic
- If both `p` and `q` < current: LCA in left subtree
- If both `p` and `q` > current: LCA in right subtree
- Otherwise: Current node is LCA (split point or match)

---

## 🎯 Base Cases

```cpp
// Case 1: Empty tree
if (!root) return nullptr;

// Case 2: Split point found
// (Handled implicitly in the logic)
```

**No explicit base cases needed** - the logic handles everything!

---

## 📋 Template: Recursive Solution

```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root) return nullptr;
    
    // Both in left subtree
    if (p->val < root->val && q->val < root->val)
        return lowestCommonAncestor(root->left, p, q);
    
    // Both in right subtree
    if (p->val > root->val && q->val > root->val)
        return lowestCommonAncestor(root->right, p, q);
    
    // Split point: root is LCA
    return root;
}
```

**Complexity:**
- Time: O(h) - height of BST
- Space: O(h) - recursion stack

---

## 📋 Template: Iterative Solution

```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    TreeNode* current = root;
    while (current) {
        if (p->val < current->val && q->val < current->val) {
            current = current->left;
        } else if (p->val > current->val && q->val > current->val) {
            current = current->right;
        } else {
            return current;  // Split point found
        }
    }
    return nullptr;  // Should not reach (p and q guaranteed to exist)
}
```

**Complexity:**
- Time: O(h)
- Space: O(1) - no recursion stack

---

## 💡 Key Interview Points

### 1. **Why O(h) instead of O(n)?**
- BST property allows directional movement
- Never search both subtrees
- Only traverse one path from root to LCA

### 2. **Recursive vs Iterative**
- **Recursive**: Clean, but O(h) stack space
- **Iterative**: Explicit loop, O(1) space
- Both equally efficient in practice

### 3. **Edge Cases**
- `p` or `q` is root: Returns root
- `p` is ancestor of `q`: Returns `p`
- Both in same subtree: Returns subtree LCA

### 4. **Assumptions**
- All node values are unique
- `p != q`
- Both `p` and `q` exist in BST

---

## 🚨 Common Mistakes to Avoid

❌ Using regular binary tree LCA approach (search both subtrees)  
❌ Forgetting that a node can be descendant of itself  
❌ Not handling when one node is ancestor of the other  
❌ Using wrong comparison operators (`<=` instead of `<`)  
❌ Returning wrong node when split point is found

---

## 🔄 Comparison: BST LCA vs Regular Tree LCA

| Aspect              | BST LCA                | Regular Tree LCA       |
|---------------------|-----------------------|-----------------------|
| **Approach**       | Directional traversal | Search both subtrees  |
| **Time**           | O(h)                  | O(n)                  |
| **Space**          | O(h) or O(1)          | O(n)                  |
| **Implementation** | Simple loop/recursion | Complex backtracking  |

---

## 🎓 Related Problems

This **BST traversal template** applies to:
- **Binary Tree LCA** (LC 236) - need to search both sides
- **Path Sum** (LC 112) - similar directional traversal
- **Insert/Delete in BST** (LC 701/450) - same movement logic
- **Validate BST** (LC 98) - range checking during traversal

**Pro Tip:** Master this directional traversal pattern for all BST problems! 🚀