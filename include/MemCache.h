#ifndef MEMCACHE_H
#define MEMCACHE_H

#include <unordered_map>
#include <chrono>
#include <thread>
#include <mutex>

#include "FrequencyNode.h"
#include "MapItem.h"

using namespace std;
using namespace std::chrono;

// A mapping of key-value pairs with expiration and eviction polices
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
    void update_frequency_of_the(int key);
    
    /*
     * EVICTION POLICY: 
     * It should invalidate and remove the LFU key.  
     * For this cache, when there is a tie (i.e., two or more keys with the same frequency), 
     * the least recently used (LRU) key would be invalidated.
    */
    void apply_eviction_policy();
    
    // Returns a FrequencyNode with provided frequency 
    FrequencyNode* get_new_frequency_node(int freq, FrequencyNode* perv, FrequencyNode* next);
    
    // Insets a key as a child of a FrequencyNode
    // Inserted key will be the Most Recently Used (MRU) key of that frequency.
    void put_keynode_in_frequencynode(FrequencyNode* new_parent, KeyNode* child);
    
    // Removes the key as child node from provided FreqencyNode
    void remove_keynode_from_frequencynode(FrequencyNode* parent, KeyNode* child);

    // A separte thread based TTL support with a monotonic clock. 
    unordered_map<int, steady_clock::time_point> expiration_map;
    bool stop_t;
    thread thread_ttl;
    mutex cache_mutex;
    void run_ttl_thread();
    void apply_expiration_policy();

public:
    /* Constructor */
    MemCache(int capacity);
    /* Destructor */
    ~MemCache();

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
     * remove(int key)
     * Delete a particular key from the cache.
     * returns true if key found && removed. Otherwise, returns false
    */
    bool remove(int key);

    /* Clears the cache; Removes all the content.
     * Beware of its usage. 
    */
    bool clear();

    /*
     * resize(int new_capacity)
     * Resize the cache 
    */
    void resize(int new_capacity);

};

#endif