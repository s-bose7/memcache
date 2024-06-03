#include "../include/FrequencyNode.h"
#include "../include/MapItem.h"
#include "../include/MemCache.h"


MemCache::MemCache(int capacity) {
    // Initialize this cache with given capacity
    this->MAX_SIZE = capacity;
    this->curr_size = 0;
    this->HEAD = new FrequencyNode();
    this->thread_ttl = thread(&MemCache::run_ttl_thread, this);
}


MemCache::~MemCache(){
    lock_guard<mutex> lock(cache_mutex);
    this->stop_t = true;
    this->thread_ttl.join();
}


int MemCache::get(int key) {
    if (exists(key)){
        MapItem& map_item = bykey.at(key);
        update_frequency_of_the(key);
        return map_item.value;
    }
    return -1;
}


void MemCache::update_frequency_of_the(int key){
    MapItem& map_item = bykey.at(key);
    
    FrequencyNode *cur_freq = map_item.parent;
    FrequencyNode *new_freq = cur_freq->next;

    if(new_freq->frequency != cur_freq->frequency + 1){
        new_freq = get_new_freq_node(cur_freq->frequency + 1, cur_freq, new_freq);
    }

    bykey.at(key).parent = new_freq;

    KeyNode *keynode_to_shift = map_item.node;
    remove_keynode_as_nodelist(cur_freq, keynode_to_shift);
    put_keynode_as_nodelist(new_freq, keynode_to_shift);
}


bool MemCache::exists(int key) {
    if(bykey.count(key) == 0){
        return false;
    }
    return true;
}


void MemCache::put(int key, int value, int ttl) {
    if(ttl > 0){
        expiration_map[key] = steady_clock::now() + chrono::seconds(ttl);
    }
    if(exists(key)){
        // Update the value of the key 
        bykey.at(key).value = value;
        // Update the frequency of the key
        update_frequency_of_the(key);
        return;
    }
    if(this->curr_size == this->MAX_SIZE){
        apply_eviction_policy();
    }
    FrequencyNode *freq_node = HEAD->next;
    if(freq_node->frequency != 1){
        freq_node = get_new_freq_node(1, HEAD, freq_node);
    }
    KeyNode *key_node = new KeyNode(key);
    put_keynode_as_nodelist(freq_node, key_node);
    // Put a new entry into the Hash Table
    bykey.insert(make_pair(key, MapItem(value, freq_node, key_node)));
    ++this->curr_size;
}


void MemCache::apply_eviction_policy() {
    FrequencyNode *LFUNode = HEAD->next;
    if(LFUNode->local_keys_length == 1){
        // Invalidate LFU Key
        HEAD->next = LFUNode->next;
        LFUNode->next->prev = HEAD;
        bykey.erase(LFUNode->lrukeynode->key);
        delete LFUNode;

    }else{
        // Invalidate LRU Key
        KeyNode* LRUNode = LFUNode->lrukeynode;
        LFUNode->lrukeynode = LFUNode->lrukeynode->up;
        bykey.erase(LRUNode->key);
        delete LRUNode;
        LFUNode->local_keys_length--;
    }
    --this->curr_size;
}


FrequencyNode* MemCache::get_new_freq_node(int freq, FrequencyNode* prev, FrequencyNode* next) {
    FrequencyNode *new_freq_node = new FrequencyNode();
    new_freq_node->frequency = freq;
    new_freq_node->prev = prev;
    prev->next = new_freq_node;
    if(prev == next){
        new_freq_node->next = new_freq_node;
    }else{
        new_freq_node->next = next;
        next->prev = new_freq_node;
    }

    return new_freq_node;
}


void MemCache::put_keynode_as_nodelist(FrequencyNode* new_parent, KeyNode* child) {
    new_parent->local_keys_length++;
    if(!new_parent->mrukeynode && !new_parent->lrukeynode){
        new_parent->mrukeynode = new_parent->lrukeynode = child;
    }else{
        child->down = new_parent->mrukeynode;
        new_parent->mrukeynode->up = child;
        new_parent->mrukeynode = child;
    }
}


void MemCache::remove_keynode_as_nodelist(FrequencyNode* parent, KeyNode* child){
    if(parent->local_keys_length == 1) {
        // If the current frequency has only one key, remove it and delete the frequency node
        parent->prev->next = parent->next;
        parent->next->prev = parent->prev;
        delete parent;

    }else {
        // If the current frequency has more than one key, remove the key node from the current frequency
        if (child == parent->mrukeynode) {
            parent->mrukeynode = parent->mrukeynode->down;
        } else if (child == parent->lrukeynode) {
            parent->lrukeynode = parent->lrukeynode->up;
        } else {
            child->up->down = child->down;
            child->down->up = child->up;
        }
        parent->local_keys_length--;
    }
    child->up = child->down = nullptr;
}


bool MemCache::remove(int key) {
    bool key_removal_status = false;
    if(exists(key)){
        MapItem& map_item = bykey.at(key);
        remove_keynode_as_nodelist(
            map_item.parent, 
            map_item.node
        );
        bykey.erase(key);
        --this->curr_size;
        key_removal_status = true;
    }
    return key_removal_status;
}


void MemCache::run_ttl_thread(){
    int sleep_t = 5;
    while(!stop_t) {
        {
            lock_guard<mutex> lock(cache_mutex);
            apply_expiration_policy();
        }
        this_thread::sleep_for(chrono::seconds(sleep_t));
    }
}


void MemCache::apply_expiration_policy(){
    auto now = steady_clock::now();
    for(auto iter=expiration_map.begin(); iter!=expiration_map.end();){
        if(iter->second <= now){
            remove(iter->first);
            iter = expiration_map.erase(iter);
        }else{
            ++iter;
        }
    }
}


bool MemCache::clear(){
    std::lock_guard<std::mutex> lock(mutex);
    // Redifne everything
    HEAD = new FrequencyNode(); 
    curr_size = 0;
    bykey.clear();
    expiration_map.clear();
    return true;
}
