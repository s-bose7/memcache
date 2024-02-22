#include "../include/MapItem.h"
#include "../include/FrequencyNode.h"

// Constructor definition for FrequencyNode
MapItem::MapItem(int value, FrequencyNode *parent, KeyNode *node) : value(value), 
                                                                    parent(parent), 
                                                                    node(node) {
    // Initialize the Item object with the provided values
}
