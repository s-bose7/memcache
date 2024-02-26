# LFU-Cache

## Introduction

Caches act as temporary holding areas for frequently used data, bridging the gap between main storage (e.g., hard drive, application database) and processing units (e.g., CPU) or clients (e.g., web browsers making requests to servers). They aim to speed up access to frequently needed information by storing it closer to the processing unit, where it can be accessed much faster. Caching occurs at multiple levels between client machines and servers to optimize resource delivery.

![caching-network-proxy-application](https://github.com/s-bose7/LFU-Cache/assets/69990740/04fda769-ddf6-437a-8a6e-290652ee2db5)


Cache eviction algorithms optimize cache usage by removing inactive data, ensuring crucial information is readily available for faster application execution. These algorithms prioritize active data within limited cache space, leading to significant performance improvements in various software systems.

Before 2010, LFU (Least Frequently Used) cache eviction policies commonly relied on standard data structures like heaps and hash tables. While these offered logarithmic time complexity (O(log n)) for operations like insertion, access, and deletion, they wouldn't scale well in modern caching systems like internet proxy servers. With internet users growing from 1.97 billion in 2010 to an estimated 6 billion in 2024, these systems need to handle tens of thousands of requests per second efficiently. To address these scalability challenge, the whitepaper mentioned below proposes a brilliant strategy for LFU cache eviction, achieving a constant time complexity of O(1) for all operations.

[**Refer to this whitepaper to learn more about LFU cache eviction scheme**](http://dhruvbird.com/lfu.pdf)

## Algorithm Overview

The constant O(1) runtime is achieved by utilizing a nested doubly linked list with a hash table to access elements by their keys.

The doubly linked list is used to link together nodes representing a set of nodes that have the same access frequency (squares). This set of nodes with the same access frequency forms a doubly linked list of such nodes (circles). Each circular node has a pointer to its parent frequency node, so that later on we can access frequencies directly. An additional hashmap is used to store elements by key which maps to its value, parent node, and some other metadata dictates by the implementation. 

![lfu-data-structure](https://github.com/s-bose7/LFU-Cache/assets/69990740/5fcca4d4-e89d-4be3-9300-8aae715959c3)


This approach offers efficient cache eviction with a constant time complexity, making it suitable for high-throughput systems like internet proxy servers.
