#ifndef MEMCACHE_H
#define MEMCACHE_H

#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>
#include <algorithm>

#include "mapitem.h"
#include "keynode.h"
#include "frequencynode.h"

#include "../utils/memory_info.h"

using namespace std;
using namespace std::chrono;


// A mapping of key-value pairs with expiration and eviction polices
template<typename K, typename V>
class MemCache {

private:
    // Maximum size of the cache.
    int MAX_SIZE;
    // Counter to track the cache size.
    int curr_size; 
    
    /*  
     *  Head of the Frequency List
     *  HEAD.next will always be the Least Frequently Used Node 
    */
    FrequencyNode<KeyNode<K>> *HEAD;
    
    // To store elements by key, Key to MapItem 
    unordered_map<K, MapItem<KeyNode<K>, V>> bykey;    

    // Update the frequency of a particular key
    void update_frequency_of_the(K key);
    
    /*
     * EVICTION POLICY: 
     * It should invalidate and remove the LFU key.  
     * For this cache, when there is a tie (i.e., two or more keys with the same frequency), 
     * the least recently used (LRU) key would be invalidated.
    */
    void apply_eviction_policy();
    
    // Returns a FrequencyNode with provided frequency 
    FrequencyNode<KeyNode<K>>* get_new_frequency_node(
        int freq, 
        FrequencyNode<KeyNode<K>>* prev, 
        FrequencyNode<KeyNode<K>>* next
    );
    
    // Insets a key as a child of a FrequencyNode
    // Inserted key will be the Most Recently Used (MRU) key of that frequency.
    void put_keynode_in_frequencynode(
        FrequencyNode<KeyNode<K>>* new_parent, 
        KeyNode<K>* child
    );
    
    // Removes the key as child node from provided FreqencyNode
    void remove_keynode_from_frequencynode(
        FrequencyNode<KeyNode<K>>* parent, 
        KeyNode<K>* child
    );

    // Background Job: A separte thread based TTL support with a monotonic clock. 
    unordered_map<K, steady_clock::time_point> expiration_map;
    bool stop_t;
    thread thread_ttl;
    mutex cache_mutex;
    void run_ttl_thread();
    void apply_expiration_policy();

public:

    // Constructor
    MemCache(int capacity);
    // Destructor
    ~MemCache();

    /*
     * get(int key) Gets the value of the key 
     * if the key exists in the cache. Otherwise, returns -1.
    */
    K get(K key);

    /*
     * put(int key, int value, int ttl = -1) 
     * Update the value of the key if present, or inserts the key if not already present. 
     * When the cache reaches its capacity, apply eviction policy before inserting a new item.
    */
    void put(K key, V value, unsigned long ttl = 0);

    /*
     * exists(int key): Check for existence of a particular key.
     * returns true if found. Otherwise, returns false
    */
    bool exists(K key);

    /*
     * remove(int key): Delete a particular key from the cache.
     * Returns true if key found and removed. Otherwise, returns false
    */
    bool remove(K key);

    /* bool clear(): Clears the cache; Removes all the content.
     * Use with caution. 
    */
    bool clear();

    // resize(int new_capacity): Resize the cache. 
    void resize(size_t new_capacity);

};


#include "../src/memcache.cpp"
#endif