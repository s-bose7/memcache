#ifndef MAPITEM_H
#define MAPITEM_H

#include "keynode.h"
#include "frequencynode.h"

template<typename K, typename V, typename T>
class MapItem {
public:
    /* V value: holds the value for a particular key */
    V value;
    /* FrequencyNode* parent: pointer to the parent frequency node */
    FrequencyNode<T>* parent;
    /* KeyNode *node: pointer to the node that holds the key under parent */
    KeyNode<K>* node;
    /* constructor */
    // MapItem(); 
    MapItem(V value, FrequencyNode<T> *parent, KeyNode<K> *node);
};
#include "../src/mapitem.cpp"
#endif
