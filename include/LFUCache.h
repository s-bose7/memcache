#ifndef LFUCACHE_H
#define LFUCACHE_H

#include <unordered_map>
#include "FrequencyNode.h"
#include "MapItem.h"

using namespace std;

class LFUCache {

private:
    /* Maximum size of the cache & a counter to track the size */
    int MAX_SIZE, curr_size; 
    
    /*  
     *  Head of the Frequency List
     *  HEAD.next will always be the Least Frequently Used Node 
    */
    FrequencyNode *HEAD;
    
    // To store elements by key, maps to MapsItem 
    unordered_map<int, MapItem> bykey;    

    // Update the frequency of a particular key
    void update_the_frequency(int key);
    
    /*
     * Eviction policy: it should invalidate and remove the LRU key.  
     * For this cache, when there is a tie (i.e., two or more keys with the same frequency), 
     * the least recently used (LRU) key would be invalidated.
    */
    void apply_eviction_policy();

    FrequencyNode* get_new_freq_node(int freq, FrequencyNode* perv, FrequencyNode* next);
    void put_keynode_as_nodelist(FrequencyNode* parent, KeyNode* child);

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
     * When the cache reaches its capacity, apply eviction policy before inserting a new item.
    */
    void put(int key, int value);
    /*
     * exists(int key)
     * Check for existence of a particular key
     * returns true if found. Otherwise, returns false
    */
    bool exists(int key);
    /*
     * delete_key(int key)
     * Delete a particular key from the cache.
     * returns true if key found && removed. Otherwise, returns false
    */
    bool delete_key(int key);
};

#endif