#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // TODO: Implement the function
        // Hint: Use a helper function with indices to avoid copying arrays
        return buildHelper(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1);
    }
    
    // Helper function (you'll need this)
    TreeNode* buildHelper(vector<int>& preorder, int preStart, int preEnd,
                         vector<int>& inorder, int inStart, int inEnd) {
        // Step 1: Base case - empty subtree
        if(preStart > preEnd) return nullptr;
        
        // Step 2: Get root from preorder
        int rootValue = preorder[preStart];
        TreeNode* root = new TreeNode(rootValue);
        
        // Step 3: Find root index in inorder
        int rootIndex=-1;
        for(int i=inStart; i<=inEnd;i++)
        {
            if(inorder[i]==rootValue)
            {
                rootIndex=i;
                break;
            }
        }
        
        // Step 4: Calculate sizes for left and right subtrees
        int left_size=rootIndex-inStart;
        int right_size=inEnd-rootIndex;
        
        // Step 5: Recurse on left subtree
        root->left=buildHelper(preorder, preStart+1, preStart+left_size, inorder, inStart, rootIndex-1);
        
        // Step 6: Recurse on right subtree
        root->right=buildHelper(preorder, preStart+left_size+1 ,preEnd, inorder, rootIndex+1, inEnd );
        
        // Step 7: Return root
        return root;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
    vector<int> preorder1 = {3,9,20,15,7};
    vector<int> inorder1 = {9,3,15,20,7};
    
    TreeNode* root1 = sol.buildTree(preorder1, inorder1);
    // TODO: Add function to print tree or verify
    
    return 0;
}