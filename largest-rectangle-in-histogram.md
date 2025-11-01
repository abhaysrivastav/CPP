# Largest Rectangle in Histogram - Complete Notes 📚

## � Problem Statement

Given an array of integers `heights` representing histogram bar heights (width = 1 each), find the **largest rectangle area** in the histogram.

**Example:**
```
Input: heights = [2,1,5,6,2,3]
Output: 10
```

---

## 💡 Core Concept

> **"Jab choti bar mile, tab pichli badi bars ko pop karo aur dekho ki woh left aur right mein kitni expand ho sakti hain!"**

---

## 🧠 Approach: Monotonic Stack

### 🎯 Golden Rule for Monotonic Increasing Stack:

> **"Jab bhi kabhi monotonic increasing elements stack mein maintain karna ho, toh while loop mein check karenge ki kahi element chota toh nahi hai. Agar chota NAHI hai toh push karo, warna pop karke process kar do!"**

```cpp
// Template for Monotonic Increasing Stack:
for (int i = 0; i < n; i++) {
    // While current element is SMALLER than stack top
    while (!st.empty() && arr[st.top()] > arr[i]) {
        // Pop and process
        int element = arr[st.top()];
        st.pop();
        // ... process element ...
    }
    // Push current element
    st.push(i);
}
```

### Algorithm Steps:

1. **Maintain a stack** of bar indices (not heights!)
2. **For each bar:**
   - If current bar is **shorter** → pop and calculate area
   - Right boundary = current index `i`
   - Left boundary = next element in stack (after pop)
   - Width = `right - left - 1`
3. **After loop:** Process remaining bars

---

## 📐 Width Calculation Formula (MOST IMPORTANT!)

```cpp
// During main loop (right boundary = i)
int width = st.empty() ? i : (i - st.top() - 1);

// After loop (right boundary = n)
int width = st.empty() ? n : (n - st.top() - 1);
```

**Special Case:** If stack is **empty** after pop → bar extends from start (index 0)

---

## 💻 Template Code

```cpp
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;      // Store indices, not heights!
        int maxArea = 0;
        int n = heights.size();
        
        // Step 1: Process each bar
        for (int i = 0; i < n; i++) {
            // Pop when current bar is shorter
            while (!st.empty() && heights[st.top()] > heights[i]) {
                int height = heights[st.top()];
                st.pop();
                
                // Calculate width
                int width = st.empty() ? i : (i - st.top() - 1);
                
                maxArea = max(maxArea, height * width);
            }
            
            // Push current index
            st.push(i);
        }
        
        // Step 2: Process remaining bars
        while (!st.empty()) {
            int height = heights[st.top()];
            st.pop();
            
            int width = st.empty() ? n : (n - st.top() - 1);
            
            maxArea = max(maxArea, height * width);
        }
        
        return maxArea;
    }
};
```

---

## �🎓 Key Learning Points

1. **Stack stores INDICES, not heights**
   - Need indices to calculate width
   - heights[st.top()] gives the height

2. **Pop BEFORE calculating width**
   - After pop, stack.top() = left boundary
   - This is intentional, not a bug!

3. **Width formula understanding**
   ```
   width = right - left - 1
   
   Where:
   - right = current index (or n)
   - left = stack.top() after pop (or -1 if empty)
   ```

4. **Monotonic stack property**
   - Stack maintains increasing heights
   - When pattern breaks (choti element mili), pop and process

---

## ⏱️ Complexity Analysis

### Time: **O(n)**
- Each element pushed once: n operations
- Each element popped once: n operations
- Total = 2n = O(n)

### Space: **O(n)**
- Worst case: stack holds all n elements (increasing heights)

---

## 🐛 Common Mistakes

❌ Store heights in stack → ✅ Store indices  
❌ `>=` in while condition → ✅ Use `>`  
❌ Forget `using namespace std;` → ✅ Add it  
❌ Calculate width before pop → ✅ Pop first, then calculate  

---

## 🎯 Quick Revision Checklist

```markdown
□ Stack stores indices (not heights)
□ Monotonic increasing: pop when current is smaller
□ Width = right - left - 1
□ Pop BEFORE width calculation
□ Handle empty stack case (? operator)
□ Process remaining elements after loop
□ Time: O(n), Space: O(n)
```

---

## 📝 Final Mantras

> **"Stack mein indices rakho, pop karke width nikalo!"**

> **"Monotonic increasing chahiye? Chota element aaye toh pop karo!"**

> **"Right = current, Left = stack top (after pop)"**

> **"O(n) time kyunki har element ek baar push, ek baar pop!"**

---

**Difficulty:** Hard  
**Pattern:** Monotonic Stack (Increasing)  
**LeetCode:** #84

4. Two similar while loops
First: Process during iteration (right = i)
Second: Process remaining (right = n)

5. Monotonic stack property
Stack maintains increasing heights
When pattern breaks, calculate areas