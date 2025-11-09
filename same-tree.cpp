#include <iostream>
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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // Base cases
        if(!p && !q) return true;
        if(!p || !q) return false;
        if(p->val != q->val) return false;
        
        // Recursive case
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

int main() {
    Solution sol;
    
    // Test Case 1: [1,2,3] and [1,2,3] - Same
    //    p:  1         q:  1
    //       / \           / \
    //      2   3         2   3
    TreeNode* p1 = new TreeNode(1);
    p1->left = new TreeNode(2);
    p1->right = new TreeNode(3);
    
    TreeNode* q1 = new TreeNode(1);
    q1->left = new TreeNode(2);
    q1->right = new TreeNode(3);
    
    cout << "Test Case 1: p=[1,2,3], q=[1,2,3]" << endl;
    cout << "Expected: true" << endl;
    cout << "Result: " << (sol.isSameTree(p1, q1) ? "true" : "false") << endl;
    cout << "---" << endl;
    
    // Test Case 2: [1,2] and [1,null,2] - Not Same
    //    p:  1         q:  1
    //       /               \
    //      2                 2
    TreeNode* p2 = new TreeNode(1);
    p2->left = new TreeNode(2);
    
    TreeNode* q2 = new TreeNode(1);
    q2->right = new TreeNode(2);
    
    cout << "Test Case 2: p=[1,2], q=[1,null,2]" << endl;
    cout << "Expected: false" << endl;
    cout << "Result: " << (sol.isSameTree(p2, q2) ? "true" : "false") << endl;
    cout << "---" << endl;
    
    // Test Case 3: [1,2,1] and [1,1,2] - Not Same
    //    p:  1         q:  1
    //       / \           / \
    //      2   1         1   2
    TreeNode* p3 = new TreeNode(1);
    p3->left = new TreeNode(2);
    p3->right = new TreeNode(1);
    
    TreeNode* q3 = new TreeNode(1);
    q3->left = new TreeNode(1);
    q3->right = new TreeNode(2);
    
    cout << "Test Case 3: p=[1,2,1], q=[1,1,2]" << endl;
    cout << "Expected: false" << endl;
    cout << "Result: " << (sol.isSameTree(p3, q3) ? "true" : "false") << endl;
    cout << "---" << endl;
    
    // Test Case 4: Empty trees
    TreeNode* p4 = nullptr;
    TreeNode* q4 = nullptr;
    
    cout << "Test Case 4: p=[], q=[]" << endl;
    cout << "Expected: true" << endl;
    cout << "Result: " << (sol.isSameTree(p4, q4) ? "true" : "false") << endl;
    
    return 0;
}