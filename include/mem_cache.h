#ifndef MEMCACHE_H
#define MEMCACHE_H

#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <mutex>
#include <iostream>

#include "map_item.h"
#include "key_node.h"
#include "frequency_node.h"

#include "../utils/memory_info.h"

using namespace std;
using namespace std::chrono;


// A mapping of key-value pairs with expiration and eviction polices
template<typename K, typename V>
class MemCache {

private:
    /* Maximum size of the cache & a counter to track the size */
    int MAX_SIZE, curr_size; 
    
    /*  
     *  Head of the Frequency List
     *  HEAD.next will always be the Least Frequently Used Node 
    */
    FrequencyNode<K> *HEAD;
    
    // To store elements by key, maps to MapsItem 
    unordered_map<K, MapItem<K, V>> bykey;    

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
    FrequencyNode<K>* get_new_frequency_node(
        int freq, 
        FrequencyNode<K>* prev, 
        FrequencyNode<K>* next
    );
    
    // Insets a key as a child of a FrequencyNode
    // Inserted key will be the Most Recently Used (MRU) key of that frequency.
    void put_keynode_in_frequencynode(
        FrequencyNode<K>* new_parent, 
        KeyNode<K>* child
    );
    
    // Removes the key as child node from provided FreqencyNode
    void remove_keynode_from_frequencynode(
        FrequencyNode<K>* parent, 
        KeyNode<K>* child
    );

    // A separte thread based TTL support with a monotonic clock. 
    unordered_map<K, steady_clock::time_point> expiration_map;
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
    K get(K key);
    /*
     * put(int key, int value, int ttl = -1) 
     * Update the value of the key if present, or inserts the key if not already present. 
     * When the cache reaches its capacity, apply eviction policy before inserting a new item.
    */
    void put(K key, V value, unsigned long ttl = 0);
    /*
     * exists(int key)
     * Check for existence of a particular key
     * returns true if found. Otherwise, returns false
    */
    bool exists(K key);
    /*
     * remove(int key)
     * Delete a particular key from the cache.
     * returns true if key found && removed. Otherwise, returns false
    */
    bool remove(K key);

    /* Clears the cache; Removes all the content.
     * Beware of its usage. 
    */
    bool clear();

    /*
     * resize(int new_capacity)
     * Resize the cache 
    */
    void resize(size_t new_capacity);

};
#include "../src/mem_cache.cpp"
#endif