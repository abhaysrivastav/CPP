# Path Sum - Interview Notes 🎯

## Problem Type
- **Root-to-Leaf Path Sum Check**
- DFS traversal with target tracking
- Classic tree recursion pattern

---

## 🔑 Key Concepts

### 1. What is a Root-to-Leaf Path?
- Starts at root, ends at a **leaf node**
- **Leaf** = node with NO children (`!left && !right`)
- Must reach a leaf to be valid (intermediate nodes don't count)

### 2. Two Approaches to Track Sum

**Approach A: Accumulate (Add as we go)**
```
Path: 5 → 4 → 11 → 2
sum = 0 → 5 → 9 → 20 → 22
```

**Approach B: Subtract from Target** ⭐ **Simpler!**
```
Path: 5 → 4 → 11 → 2, target = 22
remaining = 22 → 17 → 13 → 2 → 0 ✅
```

**Why subtract is better:** No need to pass accumulated sum around!

---

## 🎯 Base Cases

```cpp
// Case 1: Empty node
if (!root) return false;  // No path possible

// Case 2: Leaf node - CHECK if we found target!
if (!root->left && !root->right) {
    return targetSum == root->val;  // Have we reduced to exactly this value?
}
```

**Critical:** Only check sum equality at LEAF nodes, not internal nodes!

---

## 📋 Template: Recursive Solution

```cpp
bool hasPathSum(TreeNode* root, int targetSum) {
    // Base case 1: Empty node
    if (!root) return false;
    
    // Base case 2: Leaf node - check if target reached
    if (!root->left && !root->right) {
        return targetSum == root->val;
    }
    
    // Recursive case: Check left OR right subtree
    // Subtract current value from target
    return hasPathSum(root->left, targetSum - root->val) || 
           hasPathSum(root->right, targetSum - root->val);
}
```

**Complexity:**
- Time: O(n) - visit each node once (worst case all paths checked)
- Space: O(h) - recursion stack (h = height)

---

## 💡 Key Interview Points

### 1. **Use OR (`||`), not AND (`&&`)**
- Need **at least ONE** valid path
- If left has valid path → return true
- If right has valid path → return true
- Don't need BOTH paths to be valid

### 2. **Subtract at Each Level**
- Pass `targetSum - root->val` to children
- Simplifies logic - no extra sum parameter needed

### 3. **Leaf Check is Critical**
```cpp
// ❌ Wrong: Checking at internal nodes
if (root->val == targetSum) return true;

// ✅ Correct: Only check at leaves
if (!root->left && !root->right) {
    return targetSum == root->val;
}
```

### 4. **Empty Tree Edge Case**
- `root = nullptr` → return `false`
- Empty tree has no paths (not even to a "null leaf")

---

## 🚨 Common Mistakes to Avoid

❌ Checking sum at internal nodes (must reach leaf!)  
❌ Using AND (`&&`) instead of OR (`||`)  
❌ Forgetting to subtract `root->val` when recursing  
❌ Treating `nullptr` as a leaf node  
❌ Returning true when `targetSum == 0` at non-leaf node

---

## 🔄 Alternative: Iterative Solution (Optional)

Can use **queue/stack** with pairs `(node, remainingSum)`:

```cpp
bool hasPathSum(TreeNode* root, int targetSum) {
    if (!root) return false;
    
    queue<pair<TreeNode*, int>> q;
    q.push({root, targetSum});
    
    while (!q.empty()) {
        auto [node, remaining] = q.front();
        q.pop();
        
        // Leaf check
        if (!node->left && !node->right) {
            if (remaining == node->val) return true;
            continue;
        }
        
        // Add children with updated remaining
        if (node->left) 
            q.push({node->left, remaining - node->val});
        if (node->right) 
            q.push({node->right, remaining - node->val});
    }
    return false;
}
```

---

## 🎓 Related Problems

This **path sum with target** pattern applies to:
- **Path Sum II** (LC 113) - return all valid paths (need backtracking)
- **Path Sum III** (LC 437) - paths don't need to start at root
- **Binary Tree Maximum Path Sum** (LC 124) - find max sum path
- **Sum Root to Leaf Numbers** (LC 129) - sum all root-to-leaf numbers

**Pro Tip:** Master the leaf check + OR logic for path problems! 🚀