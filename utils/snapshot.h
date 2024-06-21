#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <fstream>
#include <filesystem> 

#include "../include/memcache.h"

template<typename K, typename V>
bool create_binary_snapshot(const MemCache<K, V>& memcache, const string& snapshotFile){ 
    return false;
}


template<typename K, typename V>
bool load_binary_snapshot(MemCache<K, V>& memcache, const string& snapshotFile) {
    return false;
}

#endif