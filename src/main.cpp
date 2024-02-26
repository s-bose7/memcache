#include <iostream>
#include "../include/LFUCache.h"
using namespace std;

int main() {
    // Create an LFUCache object with capacity 3
    LFUCache cache(3);
    cache.put(1, 1);
    cache.put(2, 2);
    cache.put(3, 3);
    cache.put(4, 4);
    cout<<cache.get(4)<<endl;
    cout<<cache.get(3)<<endl;
    cout<<cache.get(2)<<endl;
    cout<<cache.get(1)<<endl;
    cache.put(5, 5);
    cout<<cache.get(1)<<endl;
    cout<<cache.get(2)<<endl;
    cout<<cache.get(3)<<endl;
    cout<<cache.get(4)<<endl;
    cout<<cache.get(5)<<endl;
    return 0;
}