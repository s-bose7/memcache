#ifndef FREQUENCYNODE_CPP
#define FREQUENCYNODE_CPP

#include "../include/frequencynode.h"

// Constructor definition for FrequencyNode
template<typename T>
FrequencyNode<T>::FrequencyNode() : frequency(0), local_keys_length(0),
                                prev(nullptr),
                                next(this), // Always points to itself initialiy
                                mrukeynode(nullptr),
                                lrukeynode(nullptr) {
    // Initialize the FrequencyNode object with default values
}

#endif