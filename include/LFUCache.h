#ifndef LFUCACHE_H
#define LFUCACHE_H

#include <unordered_map>
#include "FrequencyNode.h"
#include "MapItem.h"


class LFUCache {

private:
    /* Maximum size of the cache & a counter to track the size */
    int MAX_SIZE, curr_size; 
    /*  
     *  Head of the Frequency List
     *  HEAD.next will always be the Least Frequently Used Node 
    */
    FrequencyNode *HEAD;
    
    /* To store elements by key, maps to MapsItem */
    unordered_map<int, MapItem> bykey;    

public:
    /* constructor */
    LFUCache(int capacity);
    /*
     * get(int key) Gets the value of the key 
     * if the key exists in the cache. Otherwise, returns -1.
    */
    int get(int key);
    /*
     * put(int key, int value) 
     * Update the value of the key if present, or inserts the key if not already present. 
     * When the cache reaches its capacity, it should invalidate and remove the LRU key, 
     * before inserting a new item. 
     * For this cache, when there is a tie (i.e., two or more keys with the same frequency), 
     * the least recently used (LRU) key would be invalidated.
    */
    void put(int key, int value);
};

#endif
