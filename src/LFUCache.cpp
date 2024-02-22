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
    // Implement logic to get value for given key from LFU cache
    return -1;
}

void LFUCache::put(int key, int value) {
    // Implement logic to put key-value pair into LFU cache
}
