#include "../include/key_node.h"

// Constructor definition for KeyNode
KeyNode::KeyNode(int key) 
    : key(key),
      up(nullptr),
      down(nullptr) {
    // Initialize the KeyNode object with the provided key
}
