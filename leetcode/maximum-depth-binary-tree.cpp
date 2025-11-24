#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int maxDepth(TreeNode* root) {
        // if (root == nullptr) return 0;
        // return 1 + max(maxDepth(root->left), maxDepth(root->right));
        if (root == nullptr) return 0;
        
        queue<TreeNode*> q;
        q.push(root);
        int depth = 0;
        
        while(!q.empty())
        {
            int levelSize=q.size();
            depth++;
            
            for(int i=0; i< levelSize;i++)
            {
                TreeNode* current=q.front();
                q.pop();

                if(current->left) q.push(current->left);
                if(current-> right) q.push(current->right);
            }
            
        }

        return depth;
    }
};

// Helper function to create tree
TreeNode* createTree1() {
    // Tree: [3,9,20,null,null,15,7]
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    return root;
}

TreeNode* createTree2() {
    // Tree: [1,null,2]
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    return root;
}

int main() {
    Solution sol;
    
    // Test 1
    TreeNode* tree1 = createTree1();
    cout << "Test 1: [3,9,20,null,null,15,7]" << endl;
    cout << "Expected: 3, Got: " << sol.maxDepth(tree1) << endl << endl;
    
    // Test 2
    TreeNode* tree2 = createTree2();
    cout << "Test 2: [1,null,2]" << endl;
    cout << "Expected: 2, Got: " << sol.maxDepth(tree2) << endl << endl;
    
    // Test 3: Empty tree
    cout << "Test 3: []" << endl;
    cout << "Expected: 0, Got: " << sol.maxDepth(nullptr) << endl << endl;
    
    // Test 4: Single node
    TreeNode* tree4 = new TreeNode(1);
    cout << "Test 4: [1]" << endl;
    cout << "Expected: 1, Got: " << sol.maxDepth(tree4) << endl;
    
    return 0;
}