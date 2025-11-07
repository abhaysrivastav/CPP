
#include <iostream>
#include <queue>
using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool isSymmetric(TreeNode* root)
    { 
        if(!root) return true;
        queue<TreeNode*> q;
        q.push(root->left);
        q.push(root->right);

        while(!q.empty())
        {
            TreeNode* left=q.front(); 
            q.pop();

            TreeNode* right=q.front();
            q.pop();

            if(!left && !right) continue;

            if(!left || !right) return false;

            if(left->val != right->val) return false;
            
            q.push(left->left);
            q.push(right->right);
            q.push(left->right);
            q.push(right->left);
        }
        return true;
    }
    // ============= RECURSIVE APPROACH =============
    // bool isSymmetric(TreeNode* root) {
    //     if(!root) return true;
    //     return isMirror(root->left, root->right);
    // }
    
    // private:
    //     bool isMirror(TreeNode* l, TreeNode* r) {
    //         if (!l && !r) return true;
    //         if (!l || !r) return false;
    //         if (l->val != r->val) return false;
    //         return isMirror(l->left, r->right) && isMirror(l->right, r->left);
    //     }
};

int main() {
    Solution sol;
    
    // Test Case 1: [1,2,2,3,4,4,3] - Symmetric
    //       1
    //      / \
    //     2   2
    //    / \ / \
    //   3  4 4  3
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(2);
    root1->left->left = new TreeNode(3);
    root1->left->right = new TreeNode(4);
    root1->right->left = new TreeNode(4);
    root1->right->right = new TreeNode(3);
    
    cout << "Test Case 1: [1,2,2,3,4,4,3]" << endl;
    cout << "Expected: true (1)" << endl;
    cout << "Result: " << (sol.isSymmetric(root1) ? "true" : "false") << endl;
    cout << "---" << endl;
    
    // Test Case 2: [1,2,2,null,3,null,3] - Not Symmetric
    //       1
    //      / \
    //     2   2
    //      \   \
    //       3   3
    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(2);
    root2->left->right = new TreeNode(3);
    root2->right->right = new TreeNode(3);
    
    cout << "Test Case 2: [1,2,2,null,3,null,3]" << endl;
    cout << "Expected: false (0)" << endl;
    cout << "Result: " << (sol.isSymmetric(root2) ? "true" : "false") << endl;
    cout << "---" << endl;
    
    // Test Case 3: [1] - Single node
    TreeNode* root3 = new TreeNode(1);
    cout << "Test Case 3: [1]" << endl;
    cout << "Expected: true (1)" << endl;
    cout << "Result: " << (sol.isSymmetric(root3) ? "true" : "false") << endl;
    cout << "---" << endl;
    
    // Test Case 4: nullptr - Empty tree
    TreeNode* root4 = nullptr;
    cout << "Test Case 4: []" << endl;
    cout << "Expected: true (1)" << endl;
    cout << "Result: " << (sol.isSymmetric(root4) ? "true" : "false") << endl;
    
    return 0;
}