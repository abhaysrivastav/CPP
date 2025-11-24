#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Recursive approach (commented out)
/*
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root) return nullptr;
    if (p->val < root->val && q->val < root->val)
        return lowestCommonAncestor(root->left, p, q);
    if (p->val > root->val && q->val > root->val)
        return lowestCommonAncestor(root->right, p, q);
    return root;
}
*/

// Iterative approach
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    TreeNode* current = root;
    while (current) {
        if (p->val < current->val && q->val < current->val) {
            current = current->left;
        } else if (p->val > current->val && q->val > current->val) {
            current = current->right;
        } else {
            return current;
        }
    }
    return nullptr; // Should not reach here if p and q exist
}

int main() {
    /*
        Example BST:
                6
               / \
              2   8
             / \ / \
            0  4 7  9
              / \
             3   5
    */
    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(4);
    root->left->right->left = new TreeNode(3);
    root->left->right->right = new TreeNode(5);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);

    TreeNode* p = root->left; // 2
    TreeNode* q = root->right; // 8
    TreeNode* lca = lowestCommonAncestor(root, p, q);
    cout << "LCA of 2 and 8: " << (lca ? lca->val : -1) << endl;

    p = root->left; // 2
    q = root->left->right; // 4
    lca = lowestCommonAncestor(root, p, q);
    cout << "LCA of 2 and 4: " << (lca ? lca->val : -1) << endl;

    p = root->left->right->left; // 3
    q = root->left->right->right; // 5
    lca = lowestCommonAncestor(root, p, q);
    cout << "LCA of 3 and 5: " << (lca ? lca->val : -1) << endl;

    return 0;
}