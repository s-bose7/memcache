#ifndef MAPITEM_H
#define MAPITEM_H

#include "frequencynode.h"

template<typename T, typename V>
class MapItem {
public:
    /* V value: holds the value for a particular key */
    V value;
    /* FrequencyNode* parent: pointer to the parent frequency node */
    FrequencyNode<T>* parent;
    /* KeyNode *node: pointer to the node that holds the key under parent */
    T* node;
    /* constructor */
    // MapItem(); 
    MapItem(V value, FrequencyNode<T> *parent, T *node);
};
#include "../src/mapitem.cpp"
#endif
