#include "../include/FrequencyNode.h"


// Constructor definition for FrequencyNode
FrequencyNode::FrequencyNode() : frequency(0), local_keys_length(0),
                                prev(nullptr),
                                next(this), // Always points to itself initialiy
                                mrukeynode(nullptr),
                                lrukeynode(nullptr) {
    // Initialize the FrequencyNode object with default values
}

