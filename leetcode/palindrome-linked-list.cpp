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
    bool isPalindrome(ListNode* head) {
        // Your implementation here
        // Step 1: Find middle
        ListNode* middle=findMiddle(head);
        // Step 2: Reverse second half  
        ListNode* secondHalf = reverseList(middle);
        
        // Step 3: Compare first and second half
        ListNode* firstHalf=head;
        while (secondHalf)
        {
            /* code */
            if(firstHalf->val!=secondHalf->val)
            {
                return false;
            }
            firstHalf=firstHalf->next;
            secondHalf=secondHalf->next;
        }
        return true;  
    }
    
private:
    // Helper function: Find middle of linked list
    ListNode* findMiddle(ListNode* head) {
        // Your code from previous problem
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
    
    // Helper function: Reverse linked list
    ListNode* reverseList(ListNode* head) {
        // Your code from reverse problem
        ListNode* prev=nullptr;
        ListNode* curr=head;
       
        while (curr!=nullptr)
        {
            /* code */
            ListNode* next=curr->next;
            curr->next=prev;
            prev=curr;
            curr=next;
        }
        return prev;        
    }
};

// Helper functions for testing
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
    
    // Test case 1: [1,2,2,1] → Expected: true
    vector<int> nums1 = {1,2,2,1};
    ListNode* list1 = createList(nums1);
    cout << "List 1: ";
    printList(list1);
    cout << "Is Palindrome: " << (sol.isPalindrome(list1) ? "true" : "false") << endl;
    
    // Test case 2: [1,2] → Expected: false
    vector<int> nums2 = {1,2};
    ListNode* list2 = createList(nums2);
    cout << "\nList 2: ";
    printList(list2);
    cout << "Is Palindrome: " << (sol.isPalindrome(list2) ? "true" : "false") << endl;
    
    return 0;
}