#ifndef MAPITEM_CPP
#define MAPITEM_CPP

#include "../include/map_item.h"


// Constructor definition for MapItem
template<typename K, typename V>
MapItem<K, V>::MapItem(V value, FrequencyNode<K>* parent, KeyNode<K>* node) 
    : value(value), 
      parent(parent), 
      node(node) {
    // Initialize the MapItem object with the provided values
}

#endif