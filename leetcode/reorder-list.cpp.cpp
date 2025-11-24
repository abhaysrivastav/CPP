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
    void reorderList(ListNode* head) {
        // Handle edge cases
        if(!head || !head->next) return;
        
        // Step 1: Find split point
        ListNode* splitPoint = findSplitPoint(head);
        
        // Step 2: Break into two parts
        ListNode* rightPart = splitPoint->next;
        splitPoint->next = nullptr;
        
        // Step 3: Reverse right part  
        ListNode* reversedRight = reverseLinkedList(rightPart);
        
        // Step 4: Merge parts alternately
        mergeAlternately(head, reversedRight);
    }

private:
    // Helper 1: Find where to split the list
    ListNode* findSplitPoint(ListNode* head) {
        // Your implementation here
        ListNode* slow=head;
        ListNode* fast=head;

        while (fast && fast->next)
        {
            slow=slow->next;
            fast=fast->next->next;
        }
        
        return slow;   
    }
    
    // Helper 2: Reverse a linked list
    ListNode* reverseLinkedList(ListNode* head) {
        // Your implementation here
        ListNode* prev=nullptr;
        ListNode* curr=head;
        
        while (curr!=nullptr) // Process all the nodes 
        {
            ListNode* next= curr->next; // Save the next node first
            curr->next=prev; // Reverse the list
            prev=curr; // move the previous forward 
            curr=next; // Move the curr forward 
        }
        return prev;
    }
    
    // Helper 3: Merge two lists alternately
    void mergeAlternately(ListNode* left, ListNode* right) {
      
        while (left && right)
        {
            ListNode* leftNext=left->next;
            ListNode* rightNext=right->next;
            
            left->next=right;
            right->next=leftNext;

            left=leftNext;
            right=rightNext;
        }        
    }
};

// Test helper functions
ListNode* createLinkedList(const vector<int>& values) {
    if(values.empty()) return nullptr;
    
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    
    for(int i = 1; i < values.size(); i++) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    
    return head;
}

void displayList(ListNode* head) {
    while(head) {
        cout << head->val;
        if(head->next) cout << " -> ";
        head = head->next;
    }
    cout << " -> NULL" << endl;
}

int main() {
    Solution solution;
    
    // Test case 1: [1,2,3,4]
    cout << "Test 1: [1,2,3,4]" << endl;
    vector<int> values1 = {1,2,3,4};
    ListNode* test1 = createLinkedList(values1);
    cout << "Original: ";
    displayList(test1);
    
    solution.reorderList(test1);
    cout << "Reordered: ";
    displayList(test1);
    
    // Test case 2: [1,2,3,4,5]
    cout << "\nTest 2: [1,2,3,4,5]" << endl;
    vector<int> values2 = {1,2,3,4,5};
    ListNode* test2 = createLinkedList(values2);
    cout << "Original: ";
    displayList(test2);
    
    solution.reorderList(test2);
    cout << "Reordered: ";
    displayList(test2);
    
    return 0;
}