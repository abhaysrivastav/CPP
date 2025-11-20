preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]

Find the root 
Split the inorder arround it 
Recurse on subtrees
    - left subtree
        - preorder
        - inorder
    - right subtree
        - preorder
        - inorder

Take the root from preorder 
Find the root's posotion in inorder 
Split the inorder into left and right 
Split the preorder into left and right 
Recurse on left and right 


Question 1: How to Find Root Position?
Given inorder array and root value, how do you find its index?
Agar inorder traversal diya hai aur root diya hai to uski index nikalne ke liye , array traverse karna padega 


Why is this important?
Ye important isiliye hai kyuki ussi position se split hona hai . 


Question: What would be the indices for left and right preorder arrays?
left preorder array ki index hogi 0...i-1 , agar i_th element split element hai 
Aur right preorder array hoga i+1 to n-1 

Question: In preorder, after the root, how do you know where left subtree ends and right subtree begins?
pre-order me left subtree element nikalne ke liye , inorder ke left size ki help leni hogi , jo ki asaan hai , actually me jitne element tree ke left me honge inorder me utne elemnet preorder me gin liya jayega , aur baake ke element right me honge preorder 

Question: What are the base cases for this recursive function?


When should you return nullptr?
When entire subtree is empty -- If current subtree has no element to process return nullptr.

When should you create a leaf node ?

When I have root with no children  left_size=0 and right_size=0

We still need to create the node because we have leaf node

// Base case: Empty subtree
if (preorder array is empty) return nullptr;

// Otherwise: Create node with root value
TreeNode* root = new TreeNode(preorder[0]);

// Recurse on left and right
// If left_size == 0, left child will be nullptr (leaf)
// If right_size == 0, right child will be nullptr (leaf)

