#include "../include/MapItem.h"
#include "../include/FrequencyNode.h"
#include "../include/KeyNode.h" 

// Constructor definition for MapItem
MapItem::MapItem(int value, FrequencyNode *parent, KeyNode *node) 
    : value(value), 
      parent(parent), 
      node(node) {
    // Initialize the MapItem object with the provided values
}
