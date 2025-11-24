#include <iostream>
#include <vector>
#include <queue>
using namespace std;

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        // 1. Handle empty tree
        if(!root) return {};
        
        // 2. Create result vector and queue
        vector<vector<int>> result;
        queue<TreeNode*> q; 
        q.push(root);
        
        while(!q.empty())
        {   
            vector<int> level;
            int size = q.size();      

            for(int i = 0; i < size; i++)
            {
                TreeNode* temp = q.front();
                q.pop();
                
                level.push_back(temp->val);  // ✅ vector uses push_back()
                
                if(temp->left != nullptr) q.push(temp->left);   // ✅ queue uses push()
                if(temp->right != nullptr) q.push(temp->right); // ✅ and temp->left, not q->left
            }
            result.push_back(level);  // ✅ vector uses push_back()
        }
        
        return result;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1: [3,9,20,null,null,15,7]
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left = new TreeNode(15);
    root1->right->right = new TreeNode(7);
    
    cout << "Test 1: [3,9,20,null,null,15,7]" << endl;
    vector<vector<int>> result1 = sol.levelOrder(root1);
    for(auto& level : result1) {
        cout << "[";
        for(int i = 0; i < level.size(); i++) {
            cout << level[i];
            if(i < level.size()-1) cout << ",";
        }
        cout << "] ";
    }
    cout << endl;
    
    // Test Case 2: [1]
    TreeNode* root2 = new TreeNode(1);
    cout << "Test 2: [1]" << endl;
    vector<vector<int>> result2 = sol.levelOrder(root2);
    for(auto& level : result2) {
        cout << "[";
        for(int i = 0; i < level.size(); i++) {
            cout << level[i];
            if(i < level.size()-1) cout << ",";
        }
        cout << "] ";
    }
    cout << endl;
    
    // Test Case 3: []
    TreeNode* root3 = nullptr;
    cout << "Test 3: []" << endl;
    vector<vector<int>> result3 = sol.levelOrder(root3);
    if(result3.empty()) {
        cout << "[]" << endl;
    }
    
    return 0;
}