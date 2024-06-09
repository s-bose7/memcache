#ifndef KEYNODE_H
#define KEYNODE_H

template<typename K>
class KeyNode {
public:
    
    K key;

    // By analogy a keyNode should connected verticaly with it's parent FrequencyNode.
     
    // KeyNode *up: pointer to the upper keyNode
    KeyNode<K> *up;
    // KeyNode *down: pointer to the lower keyNode 
    KeyNode<K> *down;

    // Constructor 
    KeyNode(K key);
};

#include "../src/keynode.cpp"
#endif
