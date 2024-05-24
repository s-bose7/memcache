# In-memory Cache

## Introduction

Caches act as temporary holding areas for frequently used data, bridging the gap between main storage (e.g., hard drive, application database) and processing units (e.g., CPU) or clients (e.g., web browsers making requests to servers). They aim to speed up access to frequently needed information by storing it closer to the processing unit, where it can be accessed much faster. Caching occurs at multiple levels between client machines and servers to optimize resource delivery.

![caching-network-proxy-application](https://github.com/s-bose7/LFU-Cache/assets/69990740/04fda769-ddf6-437a-8a6e-290652ee2db5)


Cache eviction algorithms and TTL optimize cache usage by removing inactive data, ensuring crucial information is readily available for faster application execution. These algorithms prioritize active data within limited cache space, leading to significant performance improvements in various software systems.

There are indeed a lot of cache eviction policies exist, you can learn them about [here](https://en.wikipedia.org/wiki/Cache_replacement_policies#Policies), for this cache, we'll be implementing a hybrid policy known as LFRU (Least Frequently Recently Used), which is a combination of LFU (Least Frequently Used) and LRU (Least Recently Used) replacement policy. Before 2010, LFU cache eviction policies commonly relied on standard data structures like heaps and hash tables. While these offered logarithmic time complexity (O(log n)) for operations like insertion, access, and deletion, they wouldn't scale well in modern caching systems like internet proxy servers or content delivery networks. With internet users growing from 1.97 billion in 2010 to an estimated 6 billion in 2024, these systems need to handle tens of thousands of requests per second efficiently. To address these scalability challenges, the whitepaper mentioned below proposes a brilliant strategy for LFU cache eviction, achieving a constant time complexity of O(1) for all operations.

[**Refer to this whitepaper to learn more about LFU cache eviction scheme**](http://dhruvbird.com/lfu.pdf)

## Strategy

In real caching systems implementing a LFRU replacement policy is not a cakewalk due to the complexity involved in partioning the cache into privileged and unprivileged sections. If content is popular, it is pushed into the privileged partition. When privileged parition reaches its limit, LFRU evicts content from the unprivileged partition; pushes content from the privileged to the unprivileged partition, and inserts new content into the privileged partition. LRU is used for the privileged partition and an approximated LFU (ALFU) algorithm for the unprivileged partition. In our cache there's no more than one partition, we will be constructing our cache data structure in such a way that at any given point in time, we can access the `Least-Frequent` and `Least-Recent` key in O(1) time. And if there's multiple `Least-Frequent` key exists, we will evict the LRU key rather than randomly drawing keys from the set of similar LFU keys.

## Algorithm Overview

The constant O(1) runtime is achieved by utilizing a nested doubly linked list with a hash table to access elements by their keys.

The doubly linked list is used to link together nodes representing a set of nodes that have the same access frequency (squares). This set of nodes with the same access frequency forms a doubly linked list of such nodes (circles). Each circular node has a pointer to its parent frequency node, so that later on we can access frequencies directly for our computation. An additional hashmap is used to store elements by key which maps to its parent node and some other metadata dictates by implementation choices. The LFU key would be the circle associated with the left-most square, and LRU key would be the bottom-most circle associated with the left-most square.

![lfu-data-structure](https://github.com/s-bose7/LFU-Cache/assets/69990740/5fcca4d4-e89d-4be3-9300-8aae715959c3)


This approach offers efficient cache eviction with a constant time complexity, making it suitable for high-throughput systems like proxy-servers CDNs etc.


## Features
[x] Trivial opeations of a cache i.e. put(key, value), get(key), remove(key).  
[x] Efficient cache replacement algotithm.  
[ ] Time-To-Live (TTL) association with each key.  
[ ] Multiple partition (Privileged and Unprivileged) of the cache for higher priority access.  