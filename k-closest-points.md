# K Closest Points to Origin

## Problem
Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane and an integer k, return the k closest points to the origin (0, 0). Distance is Euclidean. Return in any order.

Example: points = [[1,3],[-2,2]], k = 1 → [[-2,2]]

## Intuition
- Naive: Compute distances, sort, take first k.
- Better: Use max-heap to maintain k closest (largest distance at top).

## Approach
- Use max-heap (priority_queue) with pair<distance, point>.
- For each point, compute dist = x² + y² (long long).
- If heap.size() < k, push {dist, point}.
- Else if dist < heap.top().first, pop and push.
- Extract points from heap into result.

## Complexity
- Time: O(n log k)
- Space: O(k)

## Boilerplate Code
```cpp
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<pair<long long, vector<int>>> pq;
        for (auto& p : points) {
            long long dist = (long long)p[0] * p[0] + (long long)p[1] * p[1];
            // Heap logic
        }
        // Extract
        return res;
    }
};
```

## Tips & Tricks
- Use squared distance to avoid sqrt and overflow (long long).
- Max-heap keeps largest of smallest k.
- Handle k=0: Check !pq.empty() before pq.top().
- Order doesn't matter; any k closest is fine.
- For k close to n, sorting might be simpler.

## Related Problems
- Kth Largest Element
- Top K Frequent Elements
- Find K Pairs with Smallest Sums



