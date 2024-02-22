#ifndef MAPITEM_H
#define MAPITEM_H

#include "KeyNode.h"
#include "FrequencyNode.h"

class MapItem {
public:
    /* int value: holds the value for a particular key */
    int value;
    /* FrequencyNode* parent: pointer to the parent frequency node */
    FrequencyNode *parent;
    /* KeyNode *node: pointer to the node that holds the key under parent */
    KeyNode *node;
    /* constructor */
    MapItem(int value, FrequencyNode *parent, KeyNode *node);
};

#endif
