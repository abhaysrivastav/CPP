# 🧠 **LFU Cache Implementation - Complete Notes**

## 📋 **Problem Overview**
**Design a Least Frequently Used (LFU) Cache with O(1) operations**

### **Key Requirements:**
- `get(key)`: Return value if exists, else -1
- `put(key, value)`: Insert or update key-value pair
- **Eviction Rule**: Remove Least Frequently Used key when capacity full
- **Tiebreaker**: Among same frequency, remove Least Recently Used (LRU)
- **Time Complexity**: Both operations must be O(1)

---

## 🏗️ **Data Structure Design**

### **Four Essential Hash Maps:**

```cpp
unordered_map<int, int> keyValue;        // key → value (What is stored)
unordered_map<int, int> keyFreq;         // key → frequency (How often used)
unordered_map<int, list<int>> freqKeys;  // frequency → list of keys (Which keys have same frequency)
unordered_map<int, list<int>::iterator> keyPos;  // key → position (Where is key located for fast removal)
```

### **Additional State:**
```cpp
int capacity;  // Maximum cache size
int minFreq;   // Current minimum frequency for O(1) eviction
```

---

## 🎪 **Data Structure Roles Explained**

### **1. `keyValue` - Storage Layer**
**Purpose:** Store actual key-value pairs for quick retrieval
```cpp
keyValue = {1→10, 2→20, 3→30}
// get(1) → return keyValue[1] = 10
```

### **2. `keyFreq` - Frequency Tracking**
**Purpose:** Track access count for each key
```cpp
keyFreq = {1→2, 2→1, 3→1}
// Key 1 accessed 2 times, keys 2,3 accessed 1 time each
```

### **3. `freqKeys` - Frequency Grouping**
**Purpose:** Group keys by frequency + maintain LRU order within groups
```cpp
freqKeys = {
    1 → [3,2],    // Frequency 1: keys 3,2 (3 most recent, 2 least recent)
    2 → [1]       // Frequency 2: key 1
}
```

### **4. `keyPos` - Fast Removal**
**Purpose:** Store iterators for O(1) removal from frequency lists
```cpp
keyPos = {
    1 → iterator_pointing_to_1_in_freq2_list,
    2 → iterator_pointing_to_2_in_freq1_list,
    3 → iterator_pointing_to_3_in_freq1_list
}
```

---

## 🧪 **Complete Trace Example**

### **Scenario 1: Capacity = 3 (No Eviction)**
```cpp
LFUCache lfu(3);

Initial State: All maps empty, minFreq = 1
```

#### **Step 1: `put(1,10)`**
```cpp
keyValue = {1→10}
keyFreq = {1→1}
freqKeys = {1→[1]}
keyPos = {1→iterator_to_1}
minFreq = 1
```

#### **Step 2: `put(2,20)`**
```cpp
keyValue = {1→10, 2→20}
keyFreq = {1→1, 2→1}
freqKeys = {1→[2,1]}        // 2 most recent, 1 least recent
keyPos = {1→iter_to_1, 2→iter_to_2}
minFreq = 1
```

#### **Step 3: `get(1)` (Frequency Update)**
```cpp
keyValue = {1→10, 2→20}     // No change
keyFreq = {1→2, 2→1}        // Key 1 frequency: 1→2
freqKeys = {1→[2], 2→[1]}   // Key 1 moved from freq1 to freq2
keyPos = {1→new_iter, 2→iter_to_2}
minFreq = 1                 // Still 1 (key 2 has freq 1)
```

#### **Step 4: `put(3,30)`**
```cpp
keyValue = {1→10, 2→20, 3→30}
keyFreq = {1→2, 2→1, 3→1}
freqKeys = {1→[3,2], 2→[1]} // Key 3 added to freq1 (most recent)
keyPos = {1→iter, 2→iter, 3→iter_to_3}
minFreq = 1
```

---

### **Scenario 2: Capacity = 2 (With Eviction)**
```cpp
LFUCache lfu(2);
```

#### **Operations:**
```cpp
put(1,10) → put(2,20) → get(1) → put(3,30)
```

#### **Before `put(3,30)` (Capacity Full):**
```cpp
keyValue = {1→10, 2→20}
keyFreq = {1→2, 2→1}        // Key 1 has higher frequency
freqKeys = {1→[2], 2→[1]}   // Key 2 is LFU (freq=1)
keyPos = {1→iter, 2→iter}
minFreq = 1
```

#### **During `put(3,30)` - Eviction Process:**
```cpp
// Step 1: Capacity full, need eviction
// Step 2: Find LFU key = freqKeys[minFreq].back() = 2
// Step 3: Evict key 2 from all data structures

keyValue.erase(2)    → {1→10}
keyFreq.erase(2)     → {1→2}  
freqKeys[1].pop_back() → {1→[], 2→[1]}
keyPos.erase(2)      → {1→iter}
```

#### **After `put(3,30)` (New Key Inserted):**
```cpp
keyValue = {1→10, 3→30}     // Key 2 evicted, key 3 added
keyFreq = {1→2, 3→1}
freqKeys = {1→[3], 2→[1]}   // Key 3 in freq1, key 1 in freq2
keyPos = {1→iter, 3→iter}
minFreq = 1                 // Reset to 1 for new key
```

---

## 🔧 **Core Algorithm Implementation**

### **GET Operation:**
```cpp
int get(int key) {
    // 1. Check existence
    if (keyValue.find(key) == keyValue.end()) return -1;
    
    // 2. Update frequency
    updateFrequency(key);
    
    // 3. Return value
    return keyValue[key];
}
```

### **PUT Operation:**
```cpp
void put(int key, int value) {
    if (capacity == 0) return;
    
    // Case 1: Key exists - update value and frequency
    if (keyValue.find(key) != keyValue.end()) {
        keyValue[key] = value;
        updateFrequency(key);
        return;
    }
    
    // Case 2: New key - check capacity
    if (keyValue.size() >= capacity) {
        evictLFU();
    }
    
    // Insert new key with frequency 1
    keyValue[key] = value;
    keyFreq[key] = 1;
    freqKeys[1].push_front(key);
    keyPos[key] = freqKeys[1].begin();
    minFreq = 1;
}
```

### **UPDATE FREQUENCY Operation:**
```cpp
void updateFrequency(int key) {
    int oldFreq = keyFreq[key];
    
    // Remove from old frequency list
    freqKeys[oldFreq].erase(keyPos[key]);
    
    // Update minFreq if needed
    if (freqKeys[oldFreq].empty() && oldFreq == minFreq) {
        minFreq++;
    }
    
    // Add to new frequency list
    int newFreq = oldFreq + 1;
    freqKeys[newFreq].push_front(key);
    keyPos[key] = freqKeys[newFreq].begin();
    keyFreq[key] = newFreq;
}
```

### **EVICT LFU Operation:**
```cpp
void evictLFU() {
    // Get LRU key from minFreq group (back of list)
    int keyToEvict = freqKeys[minFreq].back();
    
    // Remove from all data structures
    freqKeys[minFreq].pop_back();
    keyValue.erase(keyToEvict);
    keyFreq.erase(keyToEvict);
    keyPos.erase(keyToEvict);
}
```

---

## 🎯 **Critical Line Analysis**

### **Most Important Line:**
```cpp
freqKeys[oldFreq].erase(keyPos[key]);
```

**What happens:**
1. **`keyPos[key]`** → Gets iterator pointing to key's position in frequency list
2. **`freqKeys[oldFreq]`** → Gets the list of keys with old frequency
3. **`.erase(iterator)`** → Removes key from old frequency list in O(1)

**Why critical:** This enables O(1) removal from middle of list, which is essential for frequency updates.

---

## 💡 **Key Insights & Mental Models**

### **🧠 Mental Model: "Office Department System"**
```cpp
keyValue  → Employee ID → Desk Number (where they sit)
keyFreq   → Employee ID → Performance Rating (how often promoted)  
freqKeys  → Performance Rating → List of employees (grouped by rating)
keyPos    → Employee ID → Exact seat location (for quick transfers)
```

### **🔄 Update Process: "Employee Promotion"**
```cpp
1. Remove from old department (freqKeys[oldFreq].erase)
2. Check if old department empty (update minFreq)  
3. Add to new department (freqKeys[newFreq].push_front)
4. Update all records (keyPos, keyFreq)
```

### **🚪 Eviction Process: "Firing Least Productive"**
```cpp
1. Find lowest performing department (minFreq)
2. Find least recent employee in that department (.back())
3. Remove from all company records (all 4 maps)
```

---

## ⚡ **Performance Analysis**

### **Time Complexity: O(1) for all operations**
- **get()**: Hash map lookup + list operations
- **put()**: Hash map operations + list operations  
- **updateFrequency()**: Direct iterator access
- **evictLFU()**: Direct minFreq access

### **Space Complexity: O(capacity)**
- Each key stored in exactly 4 data structures
- Total space: 4 × capacity = O(capacity)

---

## 🔍 **Common Pitfalls & Solutions**

### **❌ Pitfall 1: Iterator Invalidation**
```cpp
// Wrong: Iterator becomes invalid after erase
auto it = freqKeys[freq].begin();
freqKeys[freq].erase(it);
keyPos[key] = it;  // ❌ it is now invalid!

// Right: Get new iterator after insertion
freqKeys[newFreq].push_front(key);
keyPos[key] = freqKeys[newFreq].begin();  // ✅ Fresh iterator
```

### **❌ Pitfall 2: minFreq Update Logic**
```cpp
// Wrong: Always increment minFreq
if (freqKeys[oldFreq].empty()) {
    minFreq++;  // ❌ Wrong if oldFreq != minFreq
}

// Right: Only if oldFreq was minFreq
if (freqKeys[oldFreq].empty() && oldFreq == minFreq) {
    minFreq++;  // ✅ Correct condition
}
```

### **❌ Pitfall 3: Capacity Edge Cases**
```cpp
// Wrong: Forget to handle capacity = 0
void put(int key, int value) {
    // Direct insertion without checking
}

// Right: Handle edge case
void put(int key, int value) {
    if (capacity == 0) return;  // ✅ Early return
    // ... rest of logic
}
```

---

## 🎪 **Interview Tips & Variations**

### **Follow-up Questions:**
1. **"What if we need LRU instead of LFU?"** → Remove frequency tracking, keep only recency
2. **"What if we need both LFU and LRU caches?"** → Combine both strategies  
3. **"How to handle concurrent access?"** → Add locks/atomic operations
4. **"What if keys are strings?"** → Template the implementation

### **Code Interview Strategy:**
1. **Start with clear data structure design**
2. **Implement get() first** (simpler logic)
3. **Then implement updateFrequency()** (core algorithm)
4. **Finally implement put() and evictLFU()**
5. **Test with provided examples**

---

## 🚀 **Complete Implementation Template**

```cpp
class LFUCache {
private:
    int capacity, minFreq;
    unordered_map<int, int> keyValue;
    unordered_map<int, int> keyFreq;
    unordered_map<int, list<int>> freqKeys;
    unordered_map<int, list<int>::iterator> keyPos;

public:
    LFUCache(int capacity) : capacity(capacity), minFreq(1) {}
    
    int get(int key) {
        if (keyValue.find(key) == keyValue.end()) return -1;
        updateFrequency(key);
        return keyValue[key];
    }
    
    void put(int key, int value) {
        if (capacity == 0) return;
        
        if (keyValue.find(key) != keyValue.end()) {
            keyValue[key] = value;
            updateFrequency(key);
            return;
        }
        
        if (keyValue.size() >= capacity) evictLFU();
        
        keyValue[key] = value;
        keyFreq[key] = 1;
        freqKeys[1].push_front(key);
        keyPos[key] = freqKeys[1].begin();
        minFreq = 1;
    }
    
private:
    void updateFrequency(int key) {
        int oldFreq = keyFreq[key];
        freqKeys[oldFreq].erase(keyPos[key]);
        
        if (freqKeys[oldFreq].empty() && oldFreq == minFreq) {
            minFreq++;
        }
        
        int newFreq = oldFreq + 1;
        freqKeys[newFreq].push_front(key);
        keyPos[key] = freqKeys[newFreq].begin();
        keyFreq[key] = newFreq;
    }
    
    void evictLFU() {
        int keyToEvict = freqKeys[minFreq].back();
        freqKeys[minFreq].pop_back();
        keyValue.erase(keyToEvict);
        keyFreq.erase(keyToEvict);
        keyPos.erase(keyToEvict);
    }
};
```

---

**🏆 Mastery Achievement Unlocked: Advanced Data Structure Design!**

**Key Takeaway:** *"Complex problems require coordinated simple data structures working together!"*