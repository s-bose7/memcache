#ifndef MAPITEM_CPP
#define MAPITEM_CPP

#include "../include/mapitem.h"


// Constructor definition for MapItem
template<typename T, typename V>
MapItem<T, V>::MapItem(V value, FrequencyNode<T>* parent, T* node) 
    : value(value), 
      parent(parent), 
      node(node) {
    // Initialize the MapItem object with the provided values
}

#endif