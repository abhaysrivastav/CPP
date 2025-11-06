// Pattern 1: Top-Down (Pre-order style)
void traverse(TreeNode* root, int depth) {
    if (!root) return;
    // Process current node
    traverse(root->left, depth + 1);
    traverse(root->right, depth + 1);
}

// Pattern 2: Bottom-Up (Post-order style)
int calculate(TreeNode* root) {
    if (!root) return 0;
    int left = calculate(root->left);
    int right = calculate(root->right);
    return combine(left, right);  // Combine results
}

Recursive Pattern:
□ Base case: nullptr → 0
□ Recursive: 1 + max(left, right)
□ Time: O(n), Space: O(h)

Iterative Pattern:
□ Use queue for BFS
□ Capture levelSize = q.size() at START
□ For loop exactly levelSize times
□ Only push non-null children
□ Increment depth per level
□ Time: O(n), Space: O(w)

Common Bugs:
□ Pushing NULL to queue (use if(node), not if(!node))
□ Not capturing level size before for loop
□ Incrementing depth per node instead of per level