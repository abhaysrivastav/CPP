# Kth Largest Element in an Array

## Problem
Given an integer array nums and an integer k, return the kth largest element in the array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

Example: nums = [3,2,1,5,6,4], k = 2 → 5

## Intuition
- Naive: Sort and pick index (ascending: n-k, descending: k-1).
- Better: Use min-heap to maintain top k largest elements.

## Approach
- Use min-heap (priority_queue with greater).
- For each num:
  - If heap.size() < k, push.
  - Else if num > heap.top(), pop and push.
- Return heap.top().

## Complexity
- Time: O(n log k)
- Space: O(k)

## Boilerplate Code
```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int num : nums) {
            if (pq.size() < k) pq.push(num);
            else if (num > pq.top()) {
                pq.pop();
                pq.push(num);
            }
        }
        return pq.top();
    }
};
```

## Tips & Tricks
- Min-heap for k largest: keeps smallest of top k.
- Max-heap for k smallest: keeps largest of bottom k.
- Handles duplicates and edges (k=1, k=n).
- For k close to n, sorting might be faster; for small k, heap is good.

## Related Problems
- Kth Smallest Element
- Top K Frequent Elements
- Find Median in Stream 
