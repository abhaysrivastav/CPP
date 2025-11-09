# Same Tree - Interview Notes 🎯

## Problem Type
- **Binary Tree Exact Match Check**
- Compare two trees for **structural and value equality**
- Simpler than Symmetric Tree (parallel comparison, not mirror)

---

## 🔑 Key Concept

Two trees are the **same** if:
- Both have same structure
- Corresponding nodes have same values
- **Parallel comparison**: `p->left` ↔ `q->left`, `p->right` ↔ `q->right`

**Visual:**
```
    p           q
   / \         / \
  pL pR       qL qR
  
pL ↔ qL  (parallel)
pR ↔ qR  (parallel)
```

---

## 🎯 Base Cases (IDENTICAL to Symmetric Tree!)

```cpp
if (!p && !q)           // Both null → same (true)
if (!p || !q)           // One null → NOT same (false)
if (p->val != q->val)   // Different values → NOT same (false)
```

**Interview Tip:** These base cases work for ANY tree comparison problem!

---

## 📋 Template: Recursive Solution

```cpp
bool isSameTree(TreeNode* p, TreeNode* q) {
    // Base cases
    if (!p && !q) return true;
    if (!p || !q) return false;
    if (p->val != q->val) return false;
    
    // Recursive case - parallel comparison
    return isSameTree(p->left, q->left) && 
           isSameTree(p->right, q->right);
}
```

**Complexity:**
- Time: O(min(n, m)) - stops at first mismatch or smaller tree end
- Space: O(min(h1, h2)) - recursion stack depth

---

## 🔄 Comparison: Same Tree vs Symmetric Tree

| **Aspect** | **Same Tree** | **Symmetric Tree** |
|------------|---------------|-------------------|
| **Input** | Two trees | One tree |
| **Check** | Exact match | Mirror match |
| **Comparison** | Parallel | Cross |
| **Recursive calls** | `(p->left, q->left)` | `(left->left, right->right)` |
|  | `(p->right, q->right)` | `(left->right, right->left)` |
| **Base cases** | ✅ Same | ✅ Same |

**Key Insight:** Only the recursive calls differ!

---

## 📋 Template: Iterative Solution (Queue-based)

```cpp
bool isSameTree(TreeNode* p, TreeNode* q) {
    queue<TreeNode*> que;
    que.push(p);
    que.push(q);
    
    while (!que.empty()) {
        TreeNode* first = que.front(); que.pop();
        TreeNode* second = que.front(); que.pop();
        
        // Same base cases!
        if (!first && !second) continue;
        if (!first || !second) return false;
        if (first->val != second->val) return false;
        
        // Parallel pairs
        que.push(first->left);
        que.push(second->left);
        que.push(first->right);
        que.push(second->right);
    }
    return true;
}
```

**Complexity:**
- Time: O(min(n, m))
- Space: O(w) - queue size (w = max width)

---

## 💡 Key Interview Points

1. **Simpler than Symmetric Tree**
   - No cross comparison needed
   - Straightforward parallel traversal

2. **Same base cases pattern**
   - Works for: Same Tree, Symmetric Tree, Subtree problems
   - Always check nulls before accessing values

3. **Early termination**
   - Returns `false` at first mismatch
   - No need to traverse entire tree if difference found

4. **Both approaches have same logic**
   - Recursive: elegant, less code
   - Iterative: explicit control, easier to debug

---

## 🚨 Common Mistakes to Avoid

❌ Forgetting to check if both are null first  
❌ Using wrong operator: `if (!p && q)` instead of `if (!p || !q)`  
❌ Accessing `p->val` before null check  
❌ Confusing with Symmetric Tree (using cross comparison)

---

## 🎓 Related Problems

This **tree comparison template** applies to:
- **Symmetric Tree** (LC 101) - change to cross comparison
- **Subtree of Another Tree** (LC 572) - use as helper function
- **Merge Two Binary Trees** (LC 617) - similar traversal pattern
- **Leaf-Similar Trees** (LC 872) - compare leaf sequences

**Pro Tip:** Master this template once, solve multiple problems! 🚀