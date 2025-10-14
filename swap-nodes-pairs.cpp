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
    ListNode* swapPairs(ListNode* head) {
        // Handle edge cases
        if (!head || !head->next) return head;
        
        // Your implementation here
        ListNode dummy(0);
        dummy.next = head;
        ListNode* prev = &dummy;

        while (prev->next && prev->next->next)
        {
            /* code */
            ListNode* node1=prev->next;
            ListNode* node2=prev->next->next;

            prev->next=node2;
            node1->next=node2->next;
            node2->next=node1;

            prev=node1;
        }
        return dummy.next;        
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
    
    // Test case 1: [1,2,3,4]
    cout << "Test 1: [1,2,3,4]" << endl;
    vector<int> values1 = {1, 2, 3, 4};
    ListNode* test1 = createLinkedList(values1);
    cout << "Input:  ";
    displayList(test1);
    
    ListNode* result1 = solution.swapPairs(test1);
    cout << "Output: ";
    displayList(result1);
    cout << "Expected: [2,1,4,3]" << endl;
    
    // Test case 2: [] (empty list)
    cout << "\nTest 2: []" << endl;
    ListNode* test2 = nullptr;
    cout << "Input:  ";
    displayList(test2);
    
    ListNode* result2 = solution.swapPairs(test2);
    cout << "Output: ";
    displayList(result2);
    cout << "Expected: []" << endl;
    
    // Test case 3: [1] (single node)
    cout << "\nTest 3: [1]" << endl;
    vector<int> values3 = {1};
    ListNode* test3 = createLinkedList(values3);
    cout << "Input:  ";
    displayList(test3);
    
    ListNode* result3 = solution.swapPairs(test3);
    cout << "Output: ";
    displayList(result3);
    cout << "Expected: [1]" << endl;
    
    // Test case 4: [1,2,3] (odd length)
    cout << "\nTest 4: [1,2,3]" << endl;
    vector<int> values4 = {1, 2, 3};
    ListNode* test4 = createLinkedList(values4);
    cout << "Input:  ";
    displayList(test4);
    
    ListNode* result4 = solution.swapPairs(test4);
    cout << "Output: ";
    displayList(result4);
    cout << "Expected: [2,1,3]" << endl;
    
    // Test case 5: [1,2,3,4,5,6] (longer even)
    cout << "\nTest 5: [1,2,3,4,5,6]" << endl;
    vector<int> values5 = {1, 2, 3, 4, 5, 6};
    ListNode* test5 = createLinkedList(values5);
    cout << "Input:  ";
    displayList(test5);
    
    ListNode* result5 = solution.swapPairs(test5);
    cout << "Output: ";
    displayList(result5);
    cout << "Expected: [2,1,4,3,6,5]" << endl;
    
    return 0;
}