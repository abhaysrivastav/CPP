#include <iostream>
#include <vector>
using namespace std;

// Definition for singly-linked list
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* findMiddleNode(ListNode* head) {
        // Your implementation here using two pointers
        ListNode* slow=head;
        ListNode* fast=head;
    
        while (fast && fast->next)
        {
            /* code */
            slow=slow->next;
            fast=fast->next->next;
        }    
        return slow;    
    }
};

// Helper function to create linked list from vector
ListNode* createList(const vector<int>& nums) {
    if(nums.empty()) return nullptr;
    ListNode* head = new ListNode(nums[0]);
    ListNode* curr = head;
    for(int i = 1; i < nums.size(); i++) {
        curr->next = new ListNode(nums[i]);
        curr = curr->next;
    }
    return head;
}

// Helper function to print linked list
void printList(ListNode* head) {
    while(head) {
        cout << head->val;
        if(head->next) cout << " -> ";
        head = head->next;
    }
    cout << " -> NULL" << endl;
}

int main() {
    Solution sol;
    
    // Test case 1: [1,2,3,4,5] → Expected: [3,4,5]
    vector<int> nums1 = {1,2,3,4,5};
    ListNode* list1 = createList(nums1);
    cout << "Original: "; 
    printList(list1);
    
    ListNode* middle1 = sol.findMiddleNode(list1);
    cout << "Middle: ";
    printList(middle1);
    
    // Test case 2: [1,2,3,4,5,6] → Expected: [4,5,6]
    vector<int> nums2 = {1,2,3,4,5,6};
    ListNode* list2 = createList(nums2);
    cout << "\nOriginal: ";
    printList(list2);
    
    ListNode* middle2 = sol.findMiddleNode(list2);
    cout << "Middle: ";
    printList(middle2);
    
    return 0;
}