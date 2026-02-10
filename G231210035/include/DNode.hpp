#ifndef DNODE_HPP
#define DNODE_HPP

#include <iostream>
using namespace std;

class LinkedList; // ileri bildirim

class DNode {
public:
    LinkedList* data;
    DNode* next;
    DNode* prev;

    DNode(LinkedList* data = nullptr, DNode* next = nullptr, DNode* prev = nullptr);
};

#endif
