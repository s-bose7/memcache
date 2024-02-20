# LFU-Cache

#### - Caches are like temporary holding areas for frequently used data, acting as a bridge between your main storage (like a hard drive, your application's database) and your processing unit (like a CPU) or your clients (web browsers making request to your server). Their goal is to speed up access to frequently needed information by storing it closer to the processing unit, where it can be accessed much faster. Caching is done at multiple levels between the client machine and server to optimize resource delivery.
#### - Cache eviction algorithms optimize cache usage by removing inactive data, ensuring crucial information is readily available for faster application execution. These algorithms prioritize active data within limited cache space, leading to significant performance improvements in various software systems.
#### - Before 2010, LFU cache eviction policies commonly relied on standard data structures like heaps and hash tables. While these offered logarithmic time complexity (O(log n)) for operations like insertion, access, and deletion, they wouldn't scale well in modern caching systems like internet proxy servers. With internet users growing from 1.97 billion in 2010 to an estimated 6 billion in 2024, these systems need to handle tens of thousands of requests per second efficiently. To address this scalability challenge, the whitepaper mentioned below proposes a brilliant strategy for LFU cache eviction, achieving a constant time complexity of O(1) for all operations. which I think is truly amezing.    


## Algorithm overview:
#### The constant O(1) runtime achieved by utilizing 2 containers (preferably linked-list and/or hashset) and another HashTable to access elements by its key.
#### A doubly linked list is used to link together nodes which represent a SET OF NODES that have the same access frequency (Rectangular boxes), This SET OF NODES that have the same access frequency is actually a doubly linked list of such nodes or one can use a standard SET for ease of implementation (Oval boxes).

#### <img width="981" alt="lfu-backbone-linked-lists" src="https://github.com/s-bose7/LFU-Cache/assets/69990740/517a4584-36cb-4008-b4bd-ff791e37e733">

##### [**Refer to this whitepaper to learn more about LFU cache eviction scheme**](http://dhruvbird.com/lfu.pdf)
