#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

class LFUCache
{
private:
    int capacity;
    int minFreq;

    unordered_map<int, int> keyValue;
    unordered_map<int, int> keyFreq;
    unordered_map<int, list<int>> freqKeys;
    unordered_map<int, list<int>::iterator> keyPos;


public:
    LFUCache(int capacity)
    {
        this->capacity=capacity;
        this->minFreq=1;
    }

    int get(int key)
    {
        if(keyValue.find(key) == keyValue.end())
        {
            return -1;
        }
        // key exist , so we need to update the freq
        updateFrequency(key);

        return keyValue[key];
    }
    void put(int key, int value)
    {
        if(capacity==0)
            return;

        // Key exist karti hai 
        if(keyValue.find(key)!=keyValue.end())
        {
            keyValue[key]=value;
            updateFrequency(key);
            return;
        }

        // New key insertion 
        if(keyValue.size()>=capacity)
        {
            evictLFU();
        }

        keyValue[key]=value;
        keyFreq[key]=1;
        freqKeys[1].push_front(key);
        keyPos[key]=freqKeys[1].begin();
        minFreq=1;        
    }

private:
    void updateFrequency(int key)
    {
        
        int oldFreq=keyFreq[key];  
        freqKeys[oldFreq].erase(keyPos[key]);

        if(freqKeys[oldFreq].empty() && oldFreq== minFreq)
        {
            minFreq++;
        }
        
        int newFreq=oldFreq+1;


        freqKeys[newFreq].push_front(key);
        keyPos[key]=freqKeys[newFreq].begin();
        keyFreq[key]=newFreq;
    }

    void evictLFU()
    {
        int keyToEvict= freqKeys[minFreq].back();

        freqKeys[minFreq].pop_back();
        keyValue.erase(keyToEvict);
        keyFreq.erase(keyToEvict);
        keyPos.erase(keyToEvict);
    }
};


int main()
{
    cout << "=== LFU Cache Testing ===" << endl;
    
    LFUCache lfu(2);
    
    cout << "1. put(1,1)" << endl;
    lfu.put(1,1);
    
    cout << "2. put(2,2)" << endl;
    lfu.put(2,2);
    
    cout << "3. get(1): " << lfu.get(1) << endl;  // Should return 1
    
    cout << "4. put(3,3) - This should evict key 2" << endl;
    lfu.put(3,3);
    
    cout << "5. get(2): " << lfu.get(2) << endl;  // Should return -1 (evicted)
    cout << "6. get(3): " << lfu.get(3) << endl;  // Should return 3
    cout << "7. get(1): " << lfu.get(1) << endl;  // Should return 1
    
    cout << "\n=== Test Complete ===" << endl;
    
    return 0;
}