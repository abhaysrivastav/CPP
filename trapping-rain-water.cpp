/*
🌧️ Two Pointers Water Trapping - Complete Logic
हम दो pointers use करते हैं - left (array की शुरुआत से) और 
right (array के अंत से) - क्योंकि water trapping का fundamental 
rule यह है कि किसी भी position पर पानी का level उसके left और 
right के maximum heights के minimum के बराबर होता है। जब हमारे पास 
leftMax < rightMax होता है, तो हम जानते हैं कि left pointer के current 
position पर water level leftMax से limited है (क्योंकि right side में पहले से 
ही बड़ी height है), इसलिए हम safely leftMax - height[left] का water trap 
कर सकते हैं और left pointer को आगे बढ़ा सकते हैं। Opposite case में 
जब rightMax < leftMax होता है, तो right side water level को limit कर रही है, 
इसलिए हम right pointer को पीछे की तरफ move करते हैं। यह approach efficient है
क्योंकि हम हमेशा shorter boundary वाली side से move करते हैं - जो water level को
actually limit कर रही है - और इससे हमें guarantee मिलती है कि हम सभी possible 
water को accurately calculate कर रहे हैं बिना कोई position को miss किए। Key
insight यह है कि shorter side हमेशा water level determine करती है,
इसलिए उसी direction से pointer move करना logical है।
*/
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        // Step 1: Initialize two pointers and variables
        int left=0;
        int right=height.size()-1;
        int leftMax=0;
        int rightMax=0;
        int totalWater=0;           
        
        // Step 2: Main two pointers loop
        while (left<right)
        {
            /* code */
            if (leftMax<rightMax)
            {
                /* code */
                if(height[left]<leftMax)
                {             
                    totalWater=totalWater+(leftMax-height[left]);             
                }else
                {
                    leftMax=height[left];
                }
                left++;
            }else
            {
                if(height[right]<rightMax)
                {
                    totalWater=totalWater+(rightMax-height[right]);
                }else
                {
                    rightMax=height[right];
                }
                right--;
            }
        }     
        return totalWater;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1
    vector<int> height1 = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << "Test 1: height = [0,1,0,2,1,0,1,3,2,1,2,1]" << endl;
    cout << "Output: " << sol.trap(height1) << endl;
    cout << "Expected: 6" << endl << endl;
    
    // Test Case 2  
    vector<int> height2 = {4,2,0,3,2,5};
    cout << "Test 2: height = [4,2,0,3,2,5]" << endl;
    cout << "Output: " << sol.trap(height2) << endl;
    cout << "Expected: 9" << endl << endl;
    
    // Test Case 3 - Simple case
    vector<int> height3 = {3,0,2,0,4};
    cout << "Test 3: height = [3,0,2,0,4]" << endl;
    cout << "Output: " << sol.trap(height3) << endl;
    cout << "Expected: 7" << endl;
    
    return 0;
}
