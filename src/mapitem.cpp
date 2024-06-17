#ifndef MAPITEM_CPP
#define MAPITEM_CPP

#include "../include/mapitem.h"


// Constructor definition for MapItem
template<typename T, typename V>
MapItem<T, V>::MapItem(V value, T* node) 
    : value(value), 
      node(node) {
    // Initialize the MapItem object with the provided values
}

#endif