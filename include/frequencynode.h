#ifndef FREQUENCYNODE_H
#define FREQUENCYNODE_H

#include "../include/keynode.h"

template<typename T>
class FrequencyNode {
public:

    // int frequency: Access frequency of the node
    int frequency; 
    // int num_keys_local: Number of KeyNode associated with this FrequencyNode
    int num_keys_local; 

    // FrequencyNode<T> *prev: Previous pointer of this node
    FrequencyNode<T> *prev; 
    // FrequencyNode<T> *next: Next pointer of this node
    FrequencyNode<T> *next; 

    //  T *keynode_mru: Most Recently Used KeyNode pointer  
    T *keynode_mru;
    // T *keynode_lru: Least Recently Used KeyNode pointer  
    T *keynode_lru;
    
    // Constructor
    FrequencyNode();
};

#include "../src/frequencynode.cpp"
#endif
