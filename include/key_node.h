#ifndef KEYNODE_H
#define KEYNODE_H

class KeyNode {
public:
    /* int key: 32 bit integer, holds the key */
    int key;

    /* By analogy the keyNodes should connected verticaly with the FrequencyNodes 
     *
     * KeyNode *up: pointer to the upper keyNode 
     * KeyNode *down: pointer to the lower keyNode 
    */
    KeyNode *up, *down;
    /* constructor */
    KeyNode(int key);
};

#endif
