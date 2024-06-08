#ifndef MAPITEM_H
#define MAPITEM_H

#include "key_node.h"
#include "frequency_node.h"

template<typename K, typename V>
class MapItem {
public:
    /* V value: holds the value for a particular key */
    V value;
    /* FrequencyNode* parent: pointer to the parent frequency node */
    FrequencyNode<K>* parent;
    /* KeyNode *node: pointer to the node that holds the key under parent */
    KeyNode<K>* node;
    /* constructor */
    // MapItem(); 
    MapItem(V value, FrequencyNode<K> *parent, KeyNode<K> *node);
};
#include "../src/map_item.cpp"
#endif
