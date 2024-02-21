#ifndef MAPITEM_H
#define MAPITEM_H

#include "NodeList.h"
#include "FrequencyNode.h"

class MapItem {
public:
    int value;
    FrequencyNode *parent;
    NodeList *node;

    MapItem(int value, FrequencyNode *parent, NodeList *node);
};

#endif
