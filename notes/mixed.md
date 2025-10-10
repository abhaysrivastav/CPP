# Prefix Sum subarray
🧠 Optimized Solution - Conceptual Overview
Core Insight: Instead of recalculating subarray sums repeatedly (brute force O(n²)), we use prefix sums with a hash map to solve in O(n). The key intuition is: "If I know the cumulative sum up to current index and I've seen a specific cumulative sum before, then the difference between them gives me a subarray with target sum."

Data Structure Choice: Unordered Map stores <prefixSum, frequency> pairs because we need O(1) lookup to check if (currentPrefixSum - k) exists, and frequency handles duplicate prefix sums.

Mathematical Foundation: For subarray [j to i] with sum k: prefixSum[i] - prefixSum[j-1] = k, which rearranges to prefixSum[j-1] = prefixSum[i] - k. So at each index, we search for this required "previous prefix sum" in our hash map.

Intuition for New Problems: Use prefix sums when you need to find contiguous subarray properties (sum, product, etc.) and hash map when you need to remember previously seen states. The pattern is: "Process elements sequentially, maintain running computation, and check if current state minus target equals any previous state." This technique works for subarray sum equals K, maximum subarray length with sum K, or even problems involving differences/modulos.

🚀 Key Takeaway:
Transform "finding subarrays" into "finding two points with specific relationship" using cumulative computation + hash map lookup

## Sliding Window
🪟 Sliding Window - Complete Notes
🎯 What is Sliding Window?
Two pointers technique - ek window banate hain jo expand/contract hoti hai to find optimal solution.

📊 Types of Sliding Window
1. Fixed Size Window
Window size constant rehti hai
Example: "Find max sum of k consecutive elements"
2. Variable Size Window
Window size dynamically change hoti hai
Example: "Minimum window substring", "Longest substring with k unique chars"
```
#include <unordered_map>
using namespace std;

// Variable Size Sliding Window Template
string slidingWindow(string s, string target) {
    unordered_map<char, int> need, window;
    
    // Initialize what we need
    for(char c : target) need[c]++;
    
    int left = 0, right = 0;
    int valid = 0;  // How many requirements satisfied
    
    while(right < s.size()) {
        // Expand window
        char c = s[right];
        right++;
        
        // Update window data
        if(need.count(c)) {
            window[c]++;
            if(window[c] == need[c]) valid++;
        }
        
        // Contract window when condition met
        while(valid == need.size()) {
            // Update result here
            
            // Contract from left
            char d = s[left];
            left++;
            
            if(need.count(d)) {
                if(window[d] == need[d]) valid--;
                window[d]--;
            }
        }
    }
    
    return result;
}

```
🎪 Key Components
1. Data Structures
```
 unordered_map<char, int> need;    // What we want
unordered_map<char, int> window;  // What we currently have

```

# 📊 **Largest Rectangle in Histogram - Complete Notes**

## 🎯 **Problem Statement**
Given an array of integers `heights` representing histogram bar heights (width=1), find the area of the largest rectangle.

**Example:**
```
Input: heights = [2,1,5,6,2,3]
Output: 10

Visual:
    |   |
    | | |     |
| | | |   | |
| | | | | | |
2 1 5 6 2 3

Largest Rectangle (area = 10):
    |■■■|
    |■■■|     |
| | |■■■  | |
| | |■■■| | |
```

---

## 🧠 **Key Insights & Approaches**

### **1. Brute Force Analysis (O(n²) to O(n³))**
- **Fix boundaries** and find minimum height in range
- **Fix center bar** and expand left/right
- **Try all heights** and find consecutive segments
- **Problem**: Redundant calculations, not scalable

### **2. Stack-based Optimal Solution (O(n))**
- **Monotonic increasing stack** of indices
- **Pop when smaller height found** → calculate rectangle
- **Each element processed exactly once**

---

## 🔧 **Stack-based Algorithm**

### **Core Logic:**
```cpp
stack<int> st;  // Store indices (not values!)
int max_area = 0;

for(int i = 0; i < n; i++) {
    // Pop elements larger than current height
    while(!st.empty() && heights[st.top()] > heights[i]) {
        // Calculate rectangle for popped element
        int height_index = st.top(); st.pop();
        int height = heights[height_index];
        int right = i;                              // Current position
        int left = st.empty() ? -1 : st.top();      // Previous smaller
        int width = right - left - 1;
        int area = height * width;
        max_area = max(max_area, area);
    }
    st.push(i);  // Push current index
}

// ✅ CRITICAL: Process remaining stack elements
while(!st.empty()) {
    int height_index = st.top(); st.pop();
    int height = heights[height_index];
    int right = n;                              // End of array
    int left = st.empty() ? -1 : st.top();
    int width = right - left - 1;
    int area = height * width;
    max_area = max(max_area, area);
}
```

---

## 📊 **Step-by-Step Dry Run**

### **Input: heights = [2,1,5,6,2,3]**

| i | heights[i] | Action | Stack Before | Stack After | Area Calculated |
|---|------------|--------|--------------|-------------|-----------------|
| 0 | 2          | Push   | []           | [0]         | -               |
| 1 | 1          | Pop 0, Push | [0]     | [1]         | 2×1=2          |
| 2 | 5          | Push   | [1]          | [1,2]       | -               |
| 3 | 6          | Push   | [1,2]        | [1,2,3]     | -               |
| 4 | 2          | Pop 3,2, Push | [1,2,3] | [1,4]    | 6×1=6, 5×2=10  |
| 5 | 3          | Push   | [1,4]        | [1,4,5]     | -               |
| End| -         | Pop all| [1,4,5]      | []          | 3×2=6, 2×4=8, 1×6=6 |

**Maximum Area = 10** ✅

---

## 💡 **Key Formulas & Concepts**

### **Width Calculation:**
```cpp
width = right_boundary - left_boundary - 1
```

**Why `-1`?**
```
Indices: ... left [actual_rectangle] right ...
Width = (right-1) - (left+1) + 1 = right - left - 1
```

### **Boundary Detection:**
- **Right boundary**: Current index where height becomes smaller
- **Left boundary**: Previous smaller element from stack (or -1 if none)

### **When to Calculate Rectangle:**
- **During traversal**: When current height < stack.top() height
- **After traversal**: For remaining increasing elements in stack

---

## 🚨 **Critical Programming Insight**

### **🌟 Container Cleanup Rule:**
> **"जब भी additional container (stack/queue/map) use करते हैं, तो end में container को empty करने का logic add करना पड़ता है!"**

### **Why This Happens:**
- **Main algorithm** runs based on **conditions**
- When **condition fails**, elements remain **unprocessed** in container
- **Solution**: Manually process remaining elements after main loop

### **Common Examples:**
1. **Stack problems**: Process remaining stack elements
2. **BFS/Queue**: Handle remaining queue elements  
3. **Sliding window**: Process remaining window elements
4. **HashMap**: Handle remaining key-value pairs

```cpp
// General pattern:
Container container;

// Main algorithm
while(condition) {
    // Process based on condition
}

// ✅ CRITICAL: Handle remaining elements
while(!container.empty()) {
    // Process remaining elements
}
```

---

## 🎯 **Edge Cases & Handling**

### **1. Empty Stack After Pop**
```cpp
int left = st.empty() ? -1 : st.top();
```
**Meaning**: Left boundary is start of array (-1)

### **2. Single Element**
```cpp
heights = [5] → Area = 5×1 = 5
```

### **3. Increasing Sequence**
```cpp
heights = [1,2,3,4,5] → All elements remain in stack
Process remaining: 5×1 + 4×2 + 3×3 + 2×4 + 1×5 = Max(9)
```

### **4. Decreasing Sequence**
```cpp  
heights = [5,4,3,2,1] → Each element pops previous ones
Max area = 5×1 = 5
```

---

## 🔍 **Time & Space Complexity**

### **Time Complexity: O(n)**
- Each element **pushed once** and **popped at most once**
- Total operations ≤ 2n → O(n)

### **Space Complexity: O(n)**
- Stack can store at most **n elements** (increasing sequence)
- No additional space except result variables

---

## 🚀 **Similar Problems & Patterns**

### **1. Monotonic Stack Pattern:**
- **Next Greater Element**
- **Daily Temperatures**  
- **Trapping Rain Water**

### **2. Rectangle Problems:**
- **Maximal Rectangle in Binary Matrix**
- **Largest Square in Binary Matrix**

### **3. Stack + Area Calculation:**
- **Largest Rectangle under Skyline**
- **Container with Most Water** (different approach)

---

## 📝 **Implementation Template**

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        int max_area = 0;
        
        // Main loop
        for(int i = 0; i < heights.size(); i++) {
            while(!st.empty() && heights[st.top()] > heights[i]) {
                int h = heights[st.top()]; st.pop();
                int w = st.empty() ? i : i - st.top() - 1;
                max_area = max(max_area, h * w);
            }
            st.push(i);
        }
        
        // Process remaining elements
        while(!st.empty()) {
            int h = heights[st.top()]; st.pop();
            int w = st.empty() ? (int)heights.size() : (int)heights.size() - st.top() - 1;
            max_area = max(max_area, h * w);
        }
        
        return max_area;
    }
};
```

---

## 🎪 **Memory Aids**

### **"STACK = Structure That Awaits Container Cleanup"**

### **Algorithm Mantra:**
1. **Push increasing heights** (potential rectangles)
2. **Pop when decreasing** (calculate completed rectangles)  
3. **Empty remaining stack** (handle unprocessed rectangles)

### **Width Formula Memory:**
> **"Rectangle width = gap between boundaries, minus the boundaries themselves"**
> **`width = right - left - 1`**

---

**यह approach सभी histogram aur rectangle problems में fundamental building block है! 🚀**
