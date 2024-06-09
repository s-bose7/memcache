#ifndef MAPITEM_CPP
#define MAPITEM_CPP

#include "../include/mapitem.h"


// Constructor definition for MapItem
template<typename K, typename V, typename T>
MapItem<K, V, T>::MapItem(V value, FrequencyNode<T>* parent, KeyNode<K>* node) 
    : value(value), 
      parent(parent), 
      node(node) {
    // Initialize the MapItem object with the provided values
}

#endif