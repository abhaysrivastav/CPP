# Symmetric Tree - Interview Notes 🎯

## Problem Type
- **Binary Tree Symmetry Check** (Mirror Property)
- Can be solved both **Recursively** and **Iteratively**

---

## 🔑 Key Concepts

### 1. Mirror Property
Two trees are mirrors if:
- Root values are equal
- `left->left` mirrors `right->right`
- `left->right` mirrors `right->left`

**Visual:**
```
    Left          Right
    / \           / \
   LL LR         RL RR
   
LL ↔ RR  (outer pair)
LR ↔ RL  (inner pair)
```

---

## 🎯 Base Cases (SAME for both approaches!)

```cpp
if (!left && !right)           // Both null → symmetric (continue/true)
if (!left || !right)           // One null → NOT symmetric (false)
if (left->val != right->val)   // Different values → NOT symmetric (false)
```

**Interview Tip:** Always handle null cases BEFORE accessing node values!

---

## 📋 Template: Recursive Approach

```cpp
bool isSymmetric(TreeNode* root) {
    if (!root) return true;  // Edge case
    return isMirror(root->left, root->right);
}

bool isMirror(TreeNode* l, TreeNode* r) {
    // Base cases
    if (!l && !r) return true;
    if (!l || !r) return false;
    if (l->val != r->val) return false;
    
    // Recursive case - check mirror pairs
    return isMirror(l->left, r->right) && 
           isMirror(l->right, r->left);
}
```

**Complexity:**
- Time: O(n) - visit each node once
- Space: O(h) - recursion stack (h = height)

---

## 📋 Template: Iterative Approach (Queue-based)

```cpp
bool isSymmetric(TreeNode* root) {
    if (!root) return true;
    
    queue<TreeNode*> q;
    q.push(root->left);
    q.push(root->right);
    
    while (!q.empty()) {
        TreeNode* left = q.front(); q.pop();
        TreeNode* right = q.front(); q.pop();
        
        // Same base cases as recursive!
        if (!left && !right) continue;
        if (!left || !right) return false;
        if (left->val != right->val) return false;
        
        // Enqueue mirror pairs
        q.push(left->left);
        q.push(right->right);
        q.push(left->right);
        q.push(right->left);
    }
    return true;
}
```

**Complexity:**
- Time: O(n)
- Space: O(w) - queue size (w = max width of tree)

---

## 💡 Key Interview Points

1. **Logic is IDENTICAL** in both approaches
   - Same base cases
   - Same comparisons
   - Only difference: call stack vs queue

2. **Push nodes in pairs** (iterative)
   - Always pop TWO nodes at once
   - Compare as mirror pairs

3. **It's OK to push null** to queue
   - Handle null check at loop start
   - Avoids complex null checking before push

4. **Recursion → Iteration Pattern**
   ```
   Recursive call    →  Push to queue/stack
   Function stack    →  Data structure
   Return value      →  Continue/break logic
   ```

---

## 🚨 Common Mistakes to Avoid

❌ Accessing `node->val` without null check  
❌ Pushing only one node at a time (need pairs!)  
❌ Wrong pairing: `left->left` with `right->left` (should be `right->right`)  
❌ Using `||` instead of `&&` for recursive calls

---

## 🎓 Related Patterns

This **mirror checking template** can be reused for:
- Same Tree (LC 100)
- Invert Binary Tree (LC 226)
- Subtree of Another Tree (LC 572)

**Key:** Any tree comparison problem can use similar base cases!