#include <iostream>
#include "../include/LFUCache.h"
using namespace std;

int main() {
    // Create an LFUCache object with capacity 3
    LFUCache cache(3);

    // Test get and put operations
    cache.put(1, 1);
    cache.put(2, 2);
    cache.put(3, 3);
    cout << "Value for key 1: " << cache.get(1) << endl; // Expected: 1
    cout << "Value for key 2: " << cache.get(2) << endl; // Expected: 2
    cout << "Value for key 4: " << cache.get(4) << endl; // Expected: -1
    cache.put(4, 4); // Evicts key 3
    cout << "Value for key 3: " << cache.get(3) << endl; // Expected: -1 (evicted)
    cout << "Value for key 4: " << cache.get(4) << endl; // Expected: 4

    return 0;
}
