#ifndef LFUCACHE_H
#define LFUCACHE_H

#include <unordered_map>

class LFUCache {
private:

public:
    LFUCache(int capacity);
    int get(int key);
    void put(int key, int value);
};

#endif
