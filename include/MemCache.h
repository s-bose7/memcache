#ifndef MEMCACHE_H
#define MEMCACHE_H

#include <unordered_map>
#include <chrono>

#include "FrequencyNode.h"
#include "MapItem.h"

using namespace std;
using namespace std::chrono;

class MemCache {

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
     * EVICTION POLICY: 
     * It should invalidate and remove the LFU key.  
     * For this cache, when there is a tie (i.e., two or more keys with the same frequency), 
     * the least recently used (LRU) key would be invalidated.
    */
    void apply_eviction_policy();
    
    // Returns a FrequencyNode with provided frequency 
    FrequencyNode* get_new_freq_node(int freq, FrequencyNode* perv, FrequencyNode* next);
    
    // Insets a key as a child of a FrequencyNode
    // Inserted key will be the Most Recently Used (MRU) key of the cache.
    void put_keynode_as_nodelist(FrequencyNode* new_parent, KeyNode* child);
    
    // Removes the key as child node from provided FreqencyNode
    void rmv_keynode_as_nodelist(FrequencyNode* old_parent, KeyNode* child);

    // TTL support with a monotonic clock. 
    unordered_map<int, steady_clock::time_point> expiration;
    void remove_expired_keys();

public:
    /* constructor */
    MemCache(int capacity);
    /*
     * get(int key) Gets the value of the key 
     * if the key exists in the cache. Otherwise, returns -1.
    */
    int get(int key);
    /*
     * put(int key, int value, int ttl = -1) 
     * Update the value of the key if present, or inserts the key if not already present. 
     * When the cache reaches its capacity, apply eviction policy before inserting a new item.
    */
    void put(int key, int value, int ttl = -1);
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