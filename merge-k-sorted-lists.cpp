#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Definition for singly-linked list
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


struct Compare {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val;
    }
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, Compare> pq;

        // Initialize the heap
        // push all k heads into the heap , if they are not null

        for(int i=0; i< lists.size(); i++)
        {
            if(lists[i]!=nullptr)
            {
                pq.push(lists[i]);
            }
        }

        // Create dummy head and tail pointer 
        ListNode* dummy = new ListNode(0);
        ListNode* tail = dummy;

        while(!pq.empty()) // Check if the heap is now empty 
        {
            ListNode* top = pq.top(); // Get the top node
            pq.pop();

            tail->next = top; // Linking to the result
            tail=tail->next;

            if(top->next!=nullptr)
                pq.push(top->next);
        }

        
        return dummy->next;
    }
};

// Helper function to create a linked list from a vector
ListNode* createList(vector<int> vals) {
    if (vals.empty()) return nullptr;
    ListNode* head = new ListNode(vals[0]);
    ListNode* curr = head;
    for (int i = 1; i < vals.size(); i++) {
        curr->next = new ListNode(vals[i]);
        curr = curr->next;
    }
    return head;
}

// Helper function to print a linked list
void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << "->";
        head = head->next;
    }
    cout << endl;
}

int main() {
    Solution sol;
    
    // Test 1: Example 1
    vector<ListNode*> lists1 = {
        createList({1, 4, 5}),
        createList({1, 3, 4}),
        createList({2, 6})
    };
    ListNode* result1 = sol.mergeKLists(lists1);
    cout << "Test 1: ";
    printList(result1);  // Expected: 1->1->2->3->4->4->5->6
    
    // Test 2: Empty lists
    vector<ListNode*> lists2 = {};
    ListNode* result2 = sol.mergeKLists(lists2);
    cout << "Test 2: ";
    printList(result2);  // Expected: (empty)
    
    // Test 3: Lists with empty list
    vector<ListNode*> lists3 = {createList({})};
    ListNode* result3 = sol.mergeKLists(lists3);
    cout << "Test 3: ";
    printList(result3);  // Expected: (empty)
    
    return 0;
}