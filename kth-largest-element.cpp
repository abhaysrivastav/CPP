#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // Min-heap
        priority_queue<int, vector<int>, greater<int>> pq;
        for(int num : nums) {
            if(pq.size()< k)
            {
                pq.push(num);
            }else if( num > pq.top())
            {
                pq.pop();
                pq.push(num);               
            }
        }
        return pq.top();
    }
};

int main() {
    Solution sol;
    vector<int> nums = {3,2,1,5,6,4};
    cout << "Test 1 - Kth largest (k=2): " << sol.findKthLargest(nums, 2) << " (expected 5)" << endl;
    cout << "Test 1 - Kth largest (k=1): " << sol.findKthLargest(nums, 1) << " (expected 6)" << endl;
    cout << "Test 1 - Kth largest (k=6): " << sol.findKthLargest(nums, 6) << " (expected 1)" << endl;
    
    vector<int> nums2 = {3,2,3,1,2,4,5,5,6};
    cout << "Test 2 - Kth largest (k=4): " << sol.findKthLargest(nums2, 4) << " (expected 4)" << endl;
    
    vector<int> nums3 = {1};
    cout << "Test 3 - Kth largest (k=1): " << sol.findKthLargest(nums3, 1) << " (expected 1)" << endl;
    return 0;
}