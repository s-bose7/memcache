#ifndef MAPITEM_H
#define MAPITEM_H

#include "frequencynode.h"

template<typename T, typename V>
class MapItem {
public:
    
    // V value: Holds the value for a particular key
    V value;

    // FrequencyNode* parent: Pointer to the parent frequency node.
    FrequencyNode<T>* parent;
    
    // T *node: Pointer to the node that holds the key under parent.
    T* node;
    
    // Constructor 
    MapItem(V value, FrequencyNode<T> *parent, T *node);
};
#include "../src/mapitem.cpp"
#endif
