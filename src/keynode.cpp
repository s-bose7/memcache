#ifndef KEYNODE_CPP
#define KEYNODE_CPP

#include "../include/keynode.h"

// Constructor definition for KeyNode
template<typename K>
KeyNode<K>::KeyNode(K key,  FrequencyNode<KeyNode<K>> *parent) 
    : key(key),
      parent(parent),
      up(nullptr),
      down(nullptr) {
    // Initialize the KeyNode object with the provided key
}

#endif