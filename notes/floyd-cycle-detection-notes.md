# 🚨 **Floyd's Cycle Detection Algorithm - Complete Notes**

## 📋 **Problem Summary**
**Find the starting node of a cycle in a linked list. Return null if no cycle exists.**

---

## 🧠 **Core Algorithm: Floyd's Cycle Detection (Tortoise & Hare)**

### **Two Phases:**
1. **Phase 1:** Detect if cycle exists
2. **Phase 2:** Find cycle starting point

---

## 🎯 **Phase 1: Cycle Detection**

### **Logic:**
```cpp
ListNode* slow = head;  // Tortoise (1 step)
ListNode* fast = head;  // Hare (2 steps)

while(fast && fast->next) {
    slow = slow->next;      // Move 1 step
    fast = fast->next->next; // Move 2 steps
    
    if(slow == fast) {      // Meeting point found!
        // Cycle exists, go to Phase 2
    }
}
// No cycle found
```

### **Why It Works:**
- **Speed difference = 1 step per iteration**
- **In cycle, fast catches up to slow eventually**
- **If no cycle, fast reaches NULL**

---

## 🎯 **Phase 2: Find Cycle Start**

### **Mathematical Insight:**
```
Distance from head to cycle start = a
Distance from cycle start to meeting point = b
Cycle length = c

Mathematical relationship: a = c - b
Therefore: Moving 'a' steps from meeting point reaches cycle start!
```

### **Logic:**
```cpp
ListNode* ptr1 = head;        // Start from head
ListNode* ptr2 = meeting_point; // Start from meeting point

while(ptr1 != ptr2) {
    ptr1 = ptr1->next;  // Move 1 step
    ptr2 = ptr2->next;  // Move 1 step
}
return ptr1;  // Both meet at cycle start!
```

---

## 💻 **Complete Implementation Template**

```cpp
ListNode* detectCycle(ListNode* head) {
    if(!head || !head->next) return nullptr;  // Edge case
    
    ListNode* slow = head;
    ListNode* fast = head;
    
    // Phase 1: Detect cycle
    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        
        if(slow == fast) {  // Meeting point found!
            // Phase 2: Find cycle start
            ListNode* ptr1 = head;
            ListNode* ptr2 = slow;  // meeting point
            
            while(ptr1 != ptr2) {
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
            }
            return ptr1;  // Cycle start
        }
    }
    return nullptr;  // No cycle
}
```

---

## 🚨 **Common Implementation Mistakes**

### **❌ Mistake 1: Wrong Initial Loop Condition**
```cpp
while(slow != fast) {  // ❌ Initially slow == fast (both at head)
    // Loop won't execute!
}
```

### **✅ Correct Pattern:**
```cpp
while(fast && fast->next) {  // ✅ Safety checks first
    // Move pointers
    if(slow == fast) {       // ✅ Check meeting inside loop
        // Found cycle
    }
}
```

### **❌ Mistake 2: Missing Null Checks**
```cpp
while(slow != fast) {
    fast = fast->next->next;  // ❌ What if fast->next is NULL?
}
```

### **✅ Correct Safety:**
```cpp
while(fast && fast->next) {  // ✅ Check both fast and fast->next
    // Safe to move fast 2 steps
}
```

### **❌ Mistake 3: Wrong Phase 2 Starting Point**
```cpp
ListNode* ptr2 = fast;  // ❌ Use meeting point (slow), not fast
```

### **✅ Correct Phase 2:**
```cpp
ListNode* ptr2 = slow;  // ✅ Use meeting point
```

---

## 🎪 **Edge Cases Handled Automatically**

### **✅ Empty List:** `head = nullptr`
- Loop condition `fast && fast->next` prevents execution
- Returns `nullptr` correctly

### **✅ Single Node, No Cycle:** `[1]`
- `fast->next` is `nullptr`, loop doesn't execute
- Returns `nullptr` correctly

### **✅ Single Node, Self Cycle:** `[1] → points to itself`
- `slow=1, fast=1` after first iteration
- Meeting detected immediately
- Phase 2 returns node correctly

### **✅ Two Nodes with Cycle:** `[1,2]` with pos=0
- Algorithm handles correctly

### **✅ Large List, No Cycle:**
- Fast pointer reaches end, returns `nullptr`

### **✅ Complex Cycles:**
- Mathematical formula ensures correct start point

---

## 📊 **Complexity Analysis**

### **Time Complexity: O(n)**
- **Phase 1:** At most n iterations (cycle detection)
- **Phase 2:** At most n iterations (find start)
- **Total:** O(n)

### **Space Complexity: O(1)**
- Only using constant extra pointers
- No additional data structures needed

---

## 🎯 **Algorithm Variants & Applications**

### **Related Problems:**
1. **Linked List Cycle I:** Just detect if cycle exists (Phase 1 only)
2. **Happy Number:** Use same technique on number sequences
3. **Find Duplicate in Array:** Use cycle detection approach

### **Key Insight:**
**"Any sequence that eventually repeats can be solved using Floyd's algorithm"**

---

## 🧮 **Manual Trace Example**

```
Example: [3,2,0,-4] with pos=1

Structure: 3 → 2 → 0 → -4
               ↑         ↓
               ←←←←←←←←←←

Phase 1 Trace:
Initial: slow=3, fast=3
Step 1:  slow=2, fast=0
Step 2:  slow=0, fast=2
Step 3:  slow=-4, fast=-4  ← MEETING!

Phase 2 Trace:
ptr1=3 (head), ptr2=-4 (meeting)
Step 1: ptr1=2, ptr2=2  ← BOTH MEET!

Result: Cycle starts at node with value 2 ✅
```

---

## 💡 **Memory Tricks**

### **Phase 1:**
**"Fast and Slow race in cycle, fast wins by lapping slow"**

### **Phase 2:**
**"Reset one to start, equal speeds find the beginning"**

### **Loop Conditions:**
**"Check safety first, detect meeting inside"**

### **Mathematical Insight:**
**"Distance from head = Distance remaining in cycle"**

---

## 🔄 **Quick Reference Checklist**

- [ ] **Phase 1:** Use `fast && fast->next` condition
- [ ] **Phase 1:** Move slow 1 step, fast 2 steps
- [ ] **Phase 1:** Check `slow == fast` inside loop
- [ ] **Phase 2:** Reset one pointer to head
- [ ] **Phase 2:** Move both pointers 1 step each
- [ ] **Phase 2:** Return where they meet
- [ ] **Edge case:** Handle `nullptr` input
- [ ] **No cycle:** Return `nullptr` if loop exits normally

---

## 🌟 **Why This Algorithm is Beautiful**

1. **Elegant Mathematics:** Uses number theory principles
2. **Optimal Complexity:** Can't do better than O(n) time, O(1) space
3. **Handles All Cases:** No special edge case handling needed
4. **Widely Applied:** Used in many different problem domains
5. **Interview Favorite:** Tests multiple algorithmic concepts

---

