#ifndef FREQUENCYNODE_H
#define FREQUENCYNODE_H

#include <unordered_map>
#include "NodeList.h"

class FrequencyNode {
public:
    int frequency;
    int localKeysLength;
    FrequencyNode *prev;
    FrequencyNode *next;
    NodeList *localKeysHead;
    NodeList *LRUNode;

    FrequencyNode();
};

#endif
