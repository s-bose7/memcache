#ifndef NODELIST_H
#define NODELIST_H

class NodeList {
public:
    int key;
    NodeList *up;
    NodeList *down;

    NodeList(int key);
};

#endif
