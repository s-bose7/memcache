#ifndef KEYNODE_H
#define KEYNODE_H

#include "frequencynode.h"

// Forward declaration of FrequencyNode
template<typename T>
class FrequencyNode;


template<typename K>
class KeyNode {
public:

    K key;

    // FrequencyNode* parent: Pointer to the parent frequency node.
    FrequencyNode<KeyNode<K>> *parent;
    
    // By analogy a keyNode should connected verticaly with it's parent FrequencyNode.    
    // KeyNode *up: pointer to the upper keyNode
    KeyNode<K> *up;
    // KeyNode *down: pointer to the lower keyNode 
    KeyNode<K> *down;

    // Constructor 
    KeyNode(K key,  FrequencyNode<KeyNode<K>> *parent);
};

#include "../src/keynode.cpp"
#endif
