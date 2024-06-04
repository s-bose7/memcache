#include "../include/map_item.h"
#include "../include/frequency_node.h"
#include "../include/key_node.h" 

// Constructor definition for MapItem
MapItem::MapItem(int value, FrequencyNode *parent, KeyNode *node) 
    : value(value), 
      parent(parent), 
      node(node) {
    // Initialize the MapItem object with the provided values
}
