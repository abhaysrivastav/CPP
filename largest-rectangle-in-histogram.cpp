#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        int maxArea = 0;
        int n = heights.size();
        
        // Step 1: Process each bar
        for (int i = 0; i < n; i++) {
            while(!st.empty() && heights[st.top()] > heights[i])
            {
                int height=heights[st.top()];
                st.pop();

                int width= st.empty() ? i: (i-st.top()-1);
                
                //then I will take max area
                maxArea=max(maxArea,height*width);

            }
            st.push(i);
        }
        
        // Step 2: Process remaining bars
        while (!st.empty()) {
            // TODO: Pop and calculate
            int height=heights[st.top()];
            st.pop();
            int width= st.empty() ? n: (n-st.top()-1);
            maxArea=max(maxArea,height*width);
        }
        
        return maxArea;
    }
};
void runTests() {
    Solution sol;
    
    // Test 1: Example 1
    vector<int> test1 = {2, 1, 5, 6, 2, 3};
    cout << "Test 1: [2,1,5,6,2,3] → Expected: 10, Got: " 
         << sol.largestRectangleArea(test1) << endl;
    
    // Test 2: Example 2
    vector<int> test2 = {2, 4};
    cout << "Test 2: [2,4] → Expected: 4, Got: " 
         << sol.largestRectangleArea(test2) << endl;
    
    // Test 3: Single bar
    vector<int> test3 = {5};
    cout << "Test 3: [5] → Expected: 5, Got: " 
         << sol.largestRectangleArea(test3) << endl;
    
    // Test 4: Increasing heights
    vector<int> test4 = {1, 2, 3, 4, 5};
    cout << "Test 4: [1,2,3,4,5] → Expected: 9, Got: " 
         << sol.largestRectangleArea(test4) << endl;
    
    // Test 5: Decreasing heights
    vector<int> test5 = {5, 4, 3, 2, 1};
    cout << "Test 5: [5,4,3,2,1] → Expected: 9, Got: " 
         << sol.largestRectangleArea(test5) << endl;
    
    // Test 6: All same height
    vector<int> test6 = {3, 3, 3, 3};
    cout << "Test 6: [3,3,3,3] → Expected: 12, Got: " 
         << sol.largestRectangleArea(test6) << endl;
}

int main() {
    runTests();
    return 0;
}
