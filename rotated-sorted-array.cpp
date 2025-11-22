#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int  left = 0  ;
        int right = nums.size()-1;
        
        while(left <= right)
        {
            int mid = left + (right-left)/2;

            if(nums[mid] == target) return mid;
             
            if(nums[left] < nums[mid]) // left side is sorted
            {
                if(target >= nums[left] && target <= nums[mid])
                {
                    right=mid-1;
                }else
                {
                    left=mid+1;
                }
            }else //right side is sorted 
            {
                if(target >=nums[mid] && target<=nums[right]) 
                {
                    left=mid+1;
                }else
                {
                    right=mid-1;
                }
            }
        }
        return -1;  // Target not found
    }
};
int main() {
    Solution sol;
    vector<int> nums = {4,5,6,7,0,1,2};
    cout << sol.search(nums, 5) << endl;  // Should print 1
    cout << sol.search(nums, 0) << endl;  // Should print 4
    cout << sol.search(nums, 3) << endl;  // Should print -1
    return 0;
}