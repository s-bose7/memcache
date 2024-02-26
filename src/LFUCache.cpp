#include "../include/LFUCache.h"
#include "../include/FrequencyNode.h"
#include "../include/MapItem.h"

using namespace std;

LFUCache::LFUCache(int capacity) {
    // Initialize LFU cache with given capacity
    this->MAX_SIZE = capacity;
    this->curr_size = 0;
    this->HEAD = new FrequencyNode();
}

int LFUCache::get(int key) {
    if (exists(key)){
        MapItem& map_item = bykey.at(key);
        update_the_frequency(key);
        return map_item.value;
    }
    return -1;
}

void LFUCache::update_the_frequency(int key){
    MapItem& map_item = bykey.at(key);
    
    FrequencyNode *curr_freq = map_item.parent;
    FrequencyNode *new_freq = curr_freq->next;

    if(new_freq->frequency != curr_freq->frequency + 1){
        new_freq = get_new_freq_node(curr_freq->frequency + 1, curr_freq, new_freq);
    }

    bykey.at(key).parent = new_freq;

    KeyNode *keynode_to_shift = map_item.node;
    if(curr_freq->local_keys_length == 1) {
        // If the current frequency has only one key, remove it and delete the frequency node
        curr_freq->prev->next = curr_freq->next;
        curr_freq->next->prev = curr_freq->prev;
        delete curr_freq;

    }else {
        // If the current frequency has more than one key, remove the key node from the current frequency
        if (keynode_to_shift == curr_freq->mrukeynode) {
            curr_freq->mrukeynode = curr_freq->mrukeynode->down;
        } else if (keynode_to_shift == curr_freq->lrukeynode) {
            curr_freq->lrukeynode = curr_freq->lrukeynode->up;
        } else {
            keynode_to_shift->up->down = keynode_to_shift->down;
            keynode_to_shift->down->up = keynode_to_shift->up;
        }
        curr_freq->local_keys_length--;
    }
    keynode_to_shift->up = keynode_to_shift->down = nullptr;
    put_keynode_as_nodelist(new_freq, keynode_to_shift);
}

bool LFUCache::exists(int key) {
    if(bykey.count(key) == 0){
        return false;
    }
    return true;
}

void LFUCache::put(int key, int value) {
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
    bykey.insert(make_pair(key, MapItem(value, freq_node, key_node)));
    ++this->curr_size;
}


void LFUCache::apply_eviction_policy() {
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

FrequencyNode* LFUCache::get_new_freq_node(int freq, FrequencyNode* prev, FrequencyNode* next) {
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

void LFUCache::put_keynode_as_nodelist(FrequencyNode* parent, KeyNode* child) {
    parent->local_keys_length++;
    if(!parent->mrukeynode && !parent->lrukeynode){
        parent->mrukeynode = parent->lrukeynode = child;
    }else{
        child->down = parent->mrukeynode;
        parent->mrukeynode->up = child;
        parent->mrukeynode = child;
    }
}

bool LFUCache::delete_key(int key) {
    return false;
}
