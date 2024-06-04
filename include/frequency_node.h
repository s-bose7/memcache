#ifndef FREQUENCYNODE_H
#define FREQUENCYNODE_H

#include <unordered_map>
#include "key_node.h"

class FrequencyNode {
public:
    /*
     * int frequency: Access frequency of the node
     * int local_keys_length: Number of key nodes associated with this frequency node
    */
    int frequency, local_keys_length;
    /*
     * As this is a doubly-linked-list it must have prev and next pointer 
     * FrequencyNode *prev: Previous pointer of this node
     * FrequencyNode *next: Next pointer of this node
    */
    FrequencyNode *prev, *next;
    /*
     * KeyNode *mrukeynode: Most  Recently Used key node pointer  
     * KeyNode *lrukeynode: Least Recently Used key node pointer
    */
    KeyNode *mrukeynode, *lrukeynode;
    
    /* constructor */
    FrequencyNode();
};

#endif
