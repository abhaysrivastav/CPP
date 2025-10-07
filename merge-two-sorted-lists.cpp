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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
       ListNode dummy;
       ListNode* tail=&dummy;     
       
       while ( list1 && list2)
       {
        /* code */
        if(list1->val < list2->val)
        {
            tail->next=list1;
            list1=list1->next;
        }else
        {
            tail->next=list2;
            list2=list2->next;
        }
        tail=tail->next;
       }     
       
       if(list1)
       {
            tail->next=list1;
       }else
       {
            tail->next=list2;
       }
       return dummy.next;       
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
    vector<int> nums1 = {1,2,4};
    vector<int> nums2 = {1,3,4};
    ListNode* list1 = createList(nums1);
    ListNode* list2 = createList(nums2);
    cout << "List1: "; printList(list1);
    cout << "List2: "; printList(list2);
    ListNode* merged = sol.mergeTwoLists(list1, list2);
    cout << "Merged: "; printList(merged);
    return 0;
}
