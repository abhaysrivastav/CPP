# Search in Rotated Sorted Array

## Problem
Given a sorted array that has been rotated at an unknown pivot, find the index of a target element. If not found, return -1. Assume no duplicates.

Example: [4,5,6,7,0,1,2], target=0 → 4

## Intuition
- Rotated sorted array has two sorted halves.
- Use modified binary search: Determine which half is sorted, check if target is in that range, adjust pointers accordingly.
- Key: Compare mid with left/right to identify sorted half.

## Approach
1. Set left=0, right=n-1
2. While left <= right:
   - Mid = left + (right-left)/2
   - If nums[mid] == target, return mid
   - If nums[left] <= nums[mid] (left sorted):
     - If target in [nums[left], nums[mid]], right = mid-1
     - Else left = mid+1
   - Else (right sorted):
     - If target in [nums[mid], nums[right]], left = mid+1
     - Else right = mid-1
3. Return -1

## Complexity
- Time: O(log n)
- Space: O(1)

## Boilerplate Code
```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return mid;
            // Check sorted half and adjust
        }
        return -1;
    }
};
```

## Tips & Tricks
- Always check nums[mid] == target first.
- Use left + (right - left)/2 for mid to avoid overflow.
- Handle edge cases: array size 1, target at pivot, not found.
- If duplicates allowed, need extra checks (but assume no here).
- Visualize: Draw array, mark mid, see which half is sorted.

## Related Problems
- Standard Binary Search
- Find Minimum in Rotated Sorted Array
- Search in Rotated Sorted Array II (with duplicates) 