#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        // Max-heap: pair<distance, point>
        priority_queue<pair<long long, vector<int>>> pq;
        for (auto& p : points) {
            long long dist = (long long)p[0]*p[0] + (long long)p[1]*p[1];
            
            if(pq.size() < k){
                pq.push({ dist, {p[0], p[1]}});
            }else if(!pq.empty() && dist < pq.top().first)
            {
                pq.pop();
                pq.push({dist,{p[0], p[1]}});
            }
        }
        // Extract k points
        vector<vector<int>> res;
        while(!pq.empty())
        {
            res.push_back(pq.top().second);
            pq.pop();
        }

        return res;
    }
};

int main() {
    Solution sol;
    
    // Test 1: Original example
    vector<vector<int>> points1 = {{1, 3}, {-2, 2}};
    int k1 = 1;
    auto res1 = sol.kClosest(points1, k1);
    cout << "Test 1 (k=1): ";
    for (auto& p : res1) cout << "[" << p[0] << "," << p[1] << "] ";
    cout << endl;
    
    // Test 2: Example 2
    vector<vector<int>> points2 = {{3,3},{5,-1},{-2,4}};
    int k2 = 2;
    auto res2 = sol.kClosest(points2, k2);
    cout << "Test 2 (k=2): ";
    for (auto& p : res2) cout << "[" << p[0] << "," << p[1] << "] ";
    cout << endl;
    
    // Test 3: k=0
    vector<vector<int>> points3 = {{1,2},{3,4}};
    int k3 = 0;
    auto res3 = sol.kClosest(points3, k3);
    cout << "Test 3 (k=0): " << res3.size() << " points" << endl;
    
    // Test 4: k = all points
    vector<vector<int>> points4 = {{0,0},{1,1}};
    int k4 = 2;
    auto res4 = sol.kClosest(points4, k4);
    cout << "Test 4 (k=all): ";
    for (auto& p : res4) cout << "[" << p[0] << "," << p[1] << "] ";
    cout << endl;
    
    // Test 5: Single point
    vector<vector<int>> points5 = {{0,0}};
    int k5 = 1;
    auto res5 = sol.kClosest(points5, k5);
    cout << "Test 5 (single): ";
    for (auto& p : res5) cout << "[" << p[0] << "," << p[1] << "] ";
    cout << endl;
    
    return 0;
}