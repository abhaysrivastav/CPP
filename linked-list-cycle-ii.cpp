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
    ListNode* detectCycle(ListNode* head) {
        // Your Floyd's Algorithm implementation here
        ListNode* slow=head;
        ListNode* fast=head;

        while(fast && fast->next)
        {
            slow=slow->next;
            fast=fast->next->next;

            if(slow==fast)
            {
                ListNode* ptr1=head;
                ListNode* ptr2=slow;

                while (ptr1!=ptr2)
                {
                    ptr1=ptr1->next;
                    ptr2=ptr2->next;
                }
                return ptr1;                
            }
        }
        return nullptr;        
    }
};

// Helper function to create linked list with cycle
ListNode* createListWithCycle(const vector<int>& nums, int pos) {
    if(nums.empty()) return nullptr;
    
    // Create nodes
    ListNode* head = new ListNode(nums[0]);
    ListNode* curr = head;
    ListNode* cycleStart = nullptr;
    
    // Track cycle start node
    if(pos == 0) cycleStart = head;
    
    // Create remaining nodes
    for(int i = 1; i < nums.size(); i++) {
        curr->next = new ListNode(nums[i]);
        curr = curr->next;
        if(i == pos) cycleStart = curr;
    }
    
    // Create cycle if pos != -1
    if(pos != -1 && cycleStart) {
        curr->next = cycleStart;
    }
    
    return head;
}

// Helper function to print result
void printResult(ListNode* result, const vector<int>& nums, int pos) {
    if(!result) {
        cout << "No cycle detected" << endl;
    } else {
        cout << "Cycle starts at node with value: " << result->val;
        if(pos != -1) {
            cout << " (expected: " << nums[pos] << ")" << endl;
        } else {
            cout << endl;
        }
    }
}

int main() {
    Solution sol;
    
    // Test case 1: [3,2,0,-4], pos = 1
    cout << "Test 1: [3,2,0,-4], pos = 1" << endl;
    vector<int> nums1 = {3,2,0,-4};
    ListNode* head1 = createListWithCycle(nums1, 1);
    ListNode* result1 = sol.detectCycle(head1);
    printResult(result1, nums1, 1);
    
    // Test case 2: [1,2], pos = 0  
    cout << "\nTest 2: [1,2], pos = 0" << endl;
    vector<int> nums2 = {1,2};
    ListNode* head2 = createListWithCycle(nums2, 0);
    ListNode* result2 = sol.detectCycle(head2);
    printResult(result2, nums2, 0);
    
    // Test case 3: [1], pos = -1 (no cycle)
    cout << "\nTest 3: [1], pos = -1 (no cycle)" << endl;
    vector<int> nums3 = {1};
    ListNode* head3 = createListWithCycle(nums3, -1);
    ListNode* result3 = sol.detectCycle(head3);
    printResult(result3, nums3, -1);
    
    return 0;
}