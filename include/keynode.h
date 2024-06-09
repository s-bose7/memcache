#ifndef KEYNODE_H
#define KEYNODE_H

template<typename K>
class KeyNode {
public:
    /* int key: holds the key */
    K key;

    /* By analogy the keyNodes should connected verticaly with the FrequencyNodes 
     *
     * KeyNode *up: pointer to the upper keyNode 
     * KeyNode *down: pointer to the lower keyNode 
    */
    KeyNode<K> *up, *down;
    /* constructor */
    KeyNode(K key);
};

#include "../src/keynode.cpp"
#endif
