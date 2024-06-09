#ifndef FREQUENCYNODE_CPP
#define FREQUENCYNODE_CPP

#include "../include/frequencynode.h"

// Constructor definition for FrequencyNode
template<typename T>
FrequencyNode<T>::FrequencyNode() : frequency(0), num_keys_local(0),
                                prev(nullptr),
                                next(this), // Always points to itself initialiy
                                keynode_mru(nullptr),
                                keynode_lru(nullptr) {
    // Initialize the FrequencyNode object with default values
}

#endif