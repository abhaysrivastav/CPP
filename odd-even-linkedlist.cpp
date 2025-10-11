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
    ListNode* oddEvenList(ListNode* head) {
        // Handle edge cases
        if (!head || !head->next) return head;
        
        // Your implementation here

        ListNode* odd=head;
        ListNode* even=head->next;

        ListNode* evenHead=even;

        while(even && even->next)
        {
            odd->next=even->next;
            even->next=even->next->next;

            odd=odd->next;
            even=even->next;
        }
        odd->next=evenHead;
        return head;        
    }
};

// Test helper functions
ListNode* createLinkedList(const vector<int>& values) {
    if (values.empty()) return nullptr;
    
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    
    for (int i = 1; i < values.size(); i++) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    
    return head;
}

void displayList(ListNode* head) {
    cout << "[";
    while (head) {
        cout << head->val;
        if (head->next) cout << ",";
        head = head->next;
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;
    
    // Test case 1: [1,2,3,4,5]
    cout << "Test 1: [1,2,3,4,5]" << endl;
    vector<int> values1 = {1, 2, 3, 4, 5};
    ListNode* test1 = createLinkedList(values1);
    cout << "Input:  ";
    displayList(test1);
    
    ListNode* result1 = solution.oddEvenList(test1);
    cout << "Output: ";
    displayList(result1);
    cout << "Expected: [1,3,5,2,4]" << endl;
    
    // Test case 2: [2,1,3,5,6,4,7]
    cout << "\nTest 2: [2,1,3,5,6,4,7]" << endl;
    vector<int> values2 = {2, 1, 3, 5, 6, 4, 7};
    ListNode* test2 = createLinkedList(values2);
    cout << "Input:  ";
    displayList(test2);
    
    ListNode* result2 = solution.oddEvenList(test2);
    cout << "Output: ";
    displayList(result2);
    cout << "Expected: [2,3,6,7,1,5,4]" << endl;
    
    // Test case 3: [1,2,3,4] (even length)
    cout << "\nTest 3: [1,2,3,4]" << endl;
    vector<int> values3 = {1, 2, 3, 4};
    ListNode* test3 = createLinkedList(values3);
    cout << "Input:  ";
    displayList(test3);
    
    ListNode* result3 = solution.oddEvenList(test3);
    cout << "Output: ";
    displayList(result3);
    cout << "Expected: [1,3,2,4]" << endl;
    
    // Test case 4: [1] (single node)
    cout << "\nTest 4: [1]" << endl;
    vector<int> values4 = {1};
    ListNode* test4 = createLinkedList(values4);
    cout << "Input:  ";
    displayList(test4);
    
    ListNode* result4 = solution.oddEvenList(test4);
    cout << "Output: ";
    displayList(result4);
    cout << "Expected: [1]" << endl;
    
    // Test case 5: [1,2] (two nodes)
    cout << "\nTest 5: [1,2]" << endl;
    vector<int> values5 = {1, 2};
    ListNode* test5 = createLinkedList(values5);
    cout << "Input:  ";
    displayList(test5);
    
    ListNode* result5 = solution.oddEvenList(test5);
    cout << "Output: ";
    displayList(result5);
    cout << "Expected: [1,2]" << endl;
    
    return 0;
}