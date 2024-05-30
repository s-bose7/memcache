# memcache

## Introduction

Caches act as temporary holding areas for frequently used data, bridging the gap between main storage (e.g., hard drive, application database) and processing units (e.g., CPU) or clients (e.g., web browsers making requests to servers). They aim to speed up access to frequently needed information by storing it closer to the processing unit, where it can be accessed much faster. Caching occurs at multiple levels between client machines and servers to optimize resource delivery.

![caching-network-proxy-application](https://github.com/s-bose7/LFU-Cache/assets/69990740/04fda769-ddf6-437a-8a6e-290652ee2db5)

## Features
- [x] Trivial opeations of a cache i.e. `put(key, value)`, `get(key)`, `remove(key)`.  
- [x] Efficient cache replacement algotithm(s).  
- [ ] Time-To-Live (TTL) for cache entries.
- [ ] Support heterogeneous data types.
- [ ] Cache resizing and dynamic capacity management.
- [ ] Data is stored sorted by key.
- [ ] Client can provide a custom comparison function to override the sort order.
- [ ] Logging for cache performance analysis.
- [ ] Benchmarking.
- [ ] Data Compression and Serialization for keys to improve memory usage.

Cache eviction algorithms and TTL optimize cache usage by removing inactive data, ensuring crucial information is readily available for faster application execution. These algorithms prioritize active data within limited cache space, leading to significant performance improvements in various software systems.

## Strategy and Considerations
Cache eviction policies vary widely (see [here](https://en.wikipedia.org/wiki/Cache_replacement_policies#Policies)). For this cache, we’re implementing LFRU (Least Frequently Recently Used), a hybrid of LFU (Least Frequently Used) and LRU (Least Recently Used).

Implementing LFRU in real cache systems is complex due to cache partitioning into privileged and unprivileged sections. Popular content moves to the privileged section. When full, LFRU evicts from the unprivileged section, shifts content between partitions, and inserts new content into the privileged section. LRU manages the privileged partition, while an approximated LFU (ALFU) handles the unprivileged section.

Our cache avoids multiple partitions. It’s designed to access the `Least-Frequent` and `Least-Recent` keys in O(1) time. If multiple `Least-Frequent` keys exist, we evict the `Least-Recent` one, ensuring efficiency.

Before 2010, LFU policies used data structures like heaps and hash tables, resulting in O(log n) operations. These weren't scalable for modern needs, like internet proxy servers handling thousands of requests per second. As internet users grew from 1.97 billion in 2010 to 6 billion in 2024, efficient scalability became crucial. The linked [whitepaper](http://dhruvbird.com/lfu.pdf) introduces a strategy for O(1) LFU operations.

## Cache Replacement Algorithm Overview

The constant O(1) runtime is achieved by utilizing a nested doubly linked list with a hash table to access elements by their keys.

The doubly linked list is used to link together nodes representing a set of nodes that have the same access frequency (squares). This set of nodes with the same access frequency forms a doubly linked list of such nodes (circles). Each circular node has a pointer to its parent frequency node, so that later on we can access frequencies directly for our computation. An additional hashmap is used to store elements by key which maps to its parent node, its value and some other metadata dictates by implementation choices. The LFU key would be the circle associated with the left-most square, and LRU key would be the bottom-most circle associated with the left-most square.

![lfu-data-structure](https://github.com/s-bose7/LFU-Cache/assets/69990740/5fcca4d4-e89d-4be3-9300-8aae715959c3)


This approach offers efficient cache eviction with a constant time complexity, making it suitable for high-throughput systems like proxy-servers, CDNs etc. 

## Build Process

### Step 1: Navigate to the Source Directory
```bash
$ cd /path/to/lfu-cache/src
```
### Step 2: Compile Source Files into Object Files
```bash
$ g++ -c KeyNode.cpp -o ../build/KeyNode.o
$ g++ -c FrequencyNode.cpp -o ../build/FrequencyNode.o
$ g++ -c MapItem.cpp -o ../build/MapItem.o
$ g++ -c LFUCache.cpp -o ../build/LFUCache.o
```

### Step 3: Link Object Files to Create Executable Binary
```bash
$ g++ ../build/LFUCache.o ../build/KeyNode.o ../build/FrequencyNode.o ../build/MapItem.o -o ../build/lfu_cache
```
### Step 4: Run the Program
```bash
$ cd ../build
$ ./lru_cache
```
