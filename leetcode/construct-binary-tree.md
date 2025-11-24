# Construct Binary Tree from Preorder and Inorder Traversal - Interview Notes 🎯

## Problem Type
- **Tree Construction from Traversals**
- Given preorder and inorder arrays, reconstruct the binary tree
- Classic divide-and-conquer problem using tree traversal properties

---

## 🔑 Key Concepts

### 1. Tree Traversals Reminder
- **Preorder:** Root → Left → Right (root is first element in subtree)
- **Inorder:** Left → Root → Right (root splits left and right subtrees)

### 2. Divide and Conquer Approach
- Use preorder to identify root of each subtree
- Use inorder to determine left/right subtree boundaries
- Recursively build left and right subtrees

### 3. Index Management
- Pass array indices instead of copying arrays (efficient)
- Track current ranges for preorder and inorder in each recursive call

---

## 🎯 Base Cases

```cpp
// Empty subtree: no elements to process
if (preStart > preEnd) return nullptr;

// Note: No need to check inorder - both arrays have same size for valid subtrees
```

---

## 📋 Template: Recursive Helper Function

```cpp
TreeNode* buildHelper(vector<int>& preorder, int preStart, int preEnd,
                     vector<int>& inorder, int inStart, int inEnd) {
    // Base case
    if (preStart > preEnd) return nullptr;
    
    // Get root from preorder
    int rootVal = preorder[preStart];
    TreeNode* root = new TreeNode(rootVal);
    
    // Find root position in inorder
    int rootIndex = -1;
    for (int i = inStart; i <= inEnd; i++) {
        if (inorder[i] == rootVal) {
            rootIndex = i;
            break;
        }
    }
    
    // Calculate subtree sizes
    int leftSize = rootIndex - inStart;
    int rightSize = inEnd - rootIndex;
    
    // Recurse on left subtree
    root->left = buildHelper(preorder, preStart + 1, preStart + leftSize,
                            inorder, inStart, rootIndex - 1);
    
    // Recurse on right subtree
    root->right = buildHelper(preorder, preStart + leftSize + 1, preEnd,
                             inorder, rootIndex + 1, inEnd);
    
    return root;
}

// Main function
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    return buildHelper(preorder, 0, preorder.size() - 1,
                      inorder, 0, inorder.size() - 1);
}
```

---

## 💡 Key Interview Points

### 1. **Why Use Indices Instead of Subarrays?**
- Avoids copying arrays (O(n) space per call)
- More efficient, especially for large trees
- Standard approach for tree construction problems

### 2. **Preorder vs Inorder Role**
- **Preorder:** Provides root for each subtree
- **Inorder:** Provides left/right subtree boundaries
- Together they uniquely determine the tree

### 3. **Index Calculations**
- Left preorder: `preStart + 1` to `preStart + leftSize`
- Right preorder: `preStart + leftSize + 1` to `preEnd`
- Left inorder: `inStart` to `rootIndex - 1`
- Right inorder: `rootIndex + 1` to `inEnd`

### 4. **Edge Cases**
- Single node tree
- All nodes in left subtree
- All nodes in right subtree
- Empty tree (though constraints say n >= 1)

---

## 📊 Complexity Analysis

- **Time:** O(n²) worst case (finding root index takes O(n) per level)
- **Space:** O(n) for recursion stack + O(h) for indices
- **Note:** Can be optimized to O(n) with inorder index map

---

## 🚨 Common Mistakes to Avoid

❌ Using `preorder.size()` instead of `preorder.size() - 1` for end index  
❌ Off-by-one errors in index calculations  
❌ Forgetting to handle empty subtrees  
❌ Using wrong indices for left/right subtrees  
❌ Not finding root index correctly (loop bounds)

---

## 🔄 Optimization: Use HashMap for Root Index

For O(n) time, precompute inorder indices:

```cpp
unordered_map<int, int> inorderMap;
for (int i = 0; i < inorder.size(); i++) {
    inorderMap[inorder[i]] = i;
}

// Then in helper:
int rootIndex = inorderMap[rootVal];  // O(1) lookup
```

---

## 🎓 Related Problems

This **traversal-based construction** pattern applies to:
- **Construct Binary Tree from Inorder and Postorder** (LC 106)
- **Construct Binary Tree from Preorder and Postorder** (LC 889)
- **Recover Binary Search Tree** (LC 99) - similar traversal manipulation
- **Serialize and Deserialize Binary Tree** (LC 297) - related to traversals

**Pro Tip:** Master index management for all tree construction problems! 🚀

