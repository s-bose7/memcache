#include "../include/FrequencyNode.h"
#include "../include/MapItem.h"
#include "../include/MemCache.h"

using namespace std;

MemCache::MemCache(int capacity) {
    // Initialize LFU cache with given capacity
    this->MAX_SIZE = capacity;
    this->curr_size = 0;
    this->HEAD = new FrequencyNode();
}

int MemCache::get(int key) {
    if (exists(key)){
        MapItem& map_item = bykey.at(key);
        update_the_frequency(key);
        return map_item.value;
    }
    return -1;
}

void MemCache::update_the_frequency(int key){
    MapItem& map_item = bykey.at(key);
    
    FrequencyNode *cur_freq = map_item.parent;
    FrequencyNode *new_freq = cur_freq->next;

    if(new_freq->frequency != cur_freq->frequency + 1){
        new_freq = get_new_freq_node(cur_freq->frequency + 1, cur_freq, new_freq);
    }

    bykey.at(key).parent = new_freq;

    KeyNode *keynode_to_shift = map_item.node;
    rmv_keynode_as_nodelist(cur_freq, keynode_to_shift);
    put_keynode_as_nodelist(new_freq, keynode_to_shift);
}

bool MemCache::exists(int key) {
    if(bykey.count(key) == 0){
        return false;
    }
    return true;
}

void MemCache::put(int key, int value, int ttl) {
    if(exists(key)){
        // Update the value of the key 
        bykey.at(key).value = value;
        // Update the frequency of the key
        update_the_frequency(key);
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


void MemCache::rmv_keynode_as_nodelist(FrequencyNode* old_parent, KeyNode* child){
    if(old_parent->local_keys_length == 1) {
        // If the current frequency has only one key, remove it and delete the frequency node
        old_parent->prev->next = old_parent->next;
        old_parent->next->prev = old_parent->prev;
        delete old_parent;

    }else {
        // If the current frequency has more than one key, remove the key node from the current frequency
        if (child == old_parent->mrukeynode) {
            old_parent->mrukeynode = old_parent->mrukeynode->down;
        } else if (child == old_parent->lrukeynode) {
            old_parent->lrukeynode = old_parent->lrukeynode->up;
        } else {
            child->up->down = child->down;
            child->down->up = child->up;
        }
        old_parent->local_keys_length--;
    }
    child->up = child->down = nullptr;
}


bool MemCache::delete_key(int key) {
    return false;
}

void MemCache::remove_expired_keys(){
}
