# memcache

## Introduction
MemCache is a fast in-memory cache provides a mapping of arbitrary string keys to string values.

Caches act as temporary holding areas for frequently used data, bridging the gap between main storage (e.g., hard drive, application database) and processing units (e.g., CPU) or clients (e.g., web browsers making requests to servers). They aim to speed up access to frequently needed information by storing it closer to the processing unit, where it can be accessed much faster. Caching occurs at multiple levels between client machines and servers to optimize resource delivery.

![caching-network-proxy-application](https://github.com/s-bose7/memcache/assets/69990740/04fda769-ddf6-437a-8a6e-290652ee2db5)

## Features
- [x] Trivial opeations of a cache i.e. `put(key, value)`, `get(key)`, `remove(key)`. 
- [ ] All cache operations are atomic. 
- [x] Efficient cache replacement algotithm(s).  
- [x] Time-To-Live (TTL) for cache entries.
- [ ] Support heterogeneous data types.
- [x] Cache resizing and dynamic capacity management.
- [ ] Users can create a transient snapshot to get a consistent view of data.
- [ ] Automatic data compression to improve memory usage.
- [ ] Data is stored sorted by key to provide an ordered mapping service. 
- [ ] Users can provide a custom comparison function to override the sort order.

Cache eviction algorithms and TTL optimize cache usage by removing inactive data, ensuring crucial information is readily available for faster application execution. These algorithms prioritize active data within limited cache space, leading to significant performance improvements in various software systems.

## Strategy and Considerations
Cache eviction policies vary widely (see [here](https://en.wikipedia.org/wiki/Cache_replacement_policies#Policies)). For this cache, we’re implementing LFRU (Least Frequently Recently Used), a hybrid of LFU (Least Frequently Used) and LRU (Least Recently Used).

Implementing LFRU in real cache systems is complex due to cache partitioning into privileged and unprivileged sections. Popular content moves to the privileged section. When full, LFRU evicts from the unprivileged section, shifts content between partitions, and inserts new content into the privileged section. LRU manages the privileged partition, while an approximated LFU (ALFU) handles the unprivileged section.

Our cache avoids multiple partitions. It’s designed to access the `Least-Frequent` and `Least-Recent` keys in O(1) time. If multiple `Least-Frequent` keys exist, we evict the `Least-Recent` one, ensuring efficiency.

Before 2010, LFU policies used data structures like heaps and hash tables, resulting in O(log n) operations. These weren't scalable for modern needs, like internet proxy servers handling thousands of requests per second. As internet users grew from 1.97 billion in 2010 to 6 billion in 2024, efficient scalability became crucial. The linked [whitepaper](http://dhruvbird.com/lfu.pdf) introduces a strategy for O(1) LFU operations.

## Cache Replacement Algorithm Overview

The constant O(1) runtime is achieved by utilizing a nested doubly linked list with a hash table to access elements by their keys.

The doubly linked list is used to link together nodes representing a set of nodes that have the same access frequency (squares). This set of nodes with the same access frequency forms a doubly linked list of such nodes (circles). Each circular node has a pointer to its parent frequency node, so that later on we can access frequencies directly for our computation. An additional hashmap is used to store elements by key which maps to its parent node, its value and some other metadata dictates by implementation choices. The LFU key would be the left-most square, and LRU key would be the bottom-most circle associated with the left-most square.

![lfu-data-structure](https://github.com/s-bose7/LFU-Cache/assets/69990740/5fcca4d4-e89d-4be3-9300-8aae715959c3)


This approach offers efficient cache eviction with a constant time complexity, making it suitable for high-throughput systems like proxy-servers, CDNs etc. 

## Build Process

#### Generate build files
```bash
$ mkdir -p build && cd build
$ cmake ..
```
#### Compile the project
```bash
$ make     
```
#### Running tests
Project compilation will generate test executables automatically.
```bash
$ ./runTests 
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from MemCacheTest
[ RUN      ] MemCacheTest.InsertionAndRetrieval
[       OK ] MemCacheTest.InsertionAndRetrieval (0 ms)
[----------] 1 test from MemCacheTest (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.
$
```
To rerun the tests:
```bash
$ make clean && make 
$ ./runTests
```
See [here](https://www.gnu.org/software/make/manual/make.html#How-Make-Works) for more on `make` commands.

## Getting the Source
```bash
$ git clone --recurse-submodules https://github.com/s-bose7/memcache.git
```

## Performance