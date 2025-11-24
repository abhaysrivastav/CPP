#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>

class Solution
{
public:
    int largestRectangleArea(std::vector<int>& heights)
    {
        // 
        std::stack<int> st;
        int main_area=0;

        for(int i=0; i<heights.size();i++)
        {
            // Pop the element and calculate the area
            while (!st.empty() && heights[st.top()]>heights[i])
            {
                int height_index=st.top();
                st.pop();

                int height=heights[height_index];
                int rightIndex=i;
                int leftIndex=st.empty() ? -1: st.top();
                int width= rightIndex-leftIndex-1;
                int area=height*width;

                main_area=std::max(main_area, area);
            }            
            st.push(i);            
        }
        
            while(!st.empty()) {
                int height_index = st.top();
                st.pop();
                
                int height = heights[height_index];
                int rightIndex = heights.size();
                int leftIndex = st.empty() ? -1 : st.top();
                int width = rightIndex - leftIndex - 1;
                int area = height * width;
                
                main_area = std::max(main_area, area);
            }
        return main_area;
    }
};

int main() {
    Solution sol;
    
    // Test case 1
    std::vector<int> heights1 = {2,1,5,6,2,3};
    std::cout << "Test 1: " << sol.largestRectangleArea(heights1) << std::endl;  // Expected: 10
    
    // Test case 2  
    std::vector<int> heights2 = {2,4};
    std::cout << "Test 2: " << sol.largestRectangleArea(heights2) << std::endl;  // Expected: 4
    
    return 0;
}