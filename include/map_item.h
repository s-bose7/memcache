#ifndef MAPITEM_H
#define MAPITEM_H

#include "key_node.h"
#include "frequency_node.h"

class MapItem {
public:
    /* int value: holds the value for a particular key */
    int value;
    /* FrequencyNode* parent: pointer to the parent frequency node */
    FrequencyNode *parent;
    /* KeyNode *node: pointer to the node that holds the key under parent */
    KeyNode *node;
    /* constructor */
    // MapItem(); 
    MapItem(int value, FrequencyNode *parent, KeyNode *node);
};

#endif
