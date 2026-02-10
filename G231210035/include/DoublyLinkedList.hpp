#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP

#include <iostream>
using namespace std;

#include "DNode.hpp"
#include "NoSuchElement.hpp"   

class DoublyLinkedList {
private:
    DNode* head;
    int size;

    DNode* FindPreviousByPosition(int index);

public:
    DoublyLinkedList();

    int  Count() const;
    bool isEmpty() const;

    void add(LinkedList* item);
    void insert(int index, LinkedList* item);

    LinkedList* first();
    LinkedList* last();

    int  indexOf(LinkedList* item);
    void remove(LinkedList* item);
    void removeAt(int index);

    bool find(LinkedList* item);

    LinkedList* elementAt(int index);

    void reverse();
    void clear();

    void printNodesFromPositionInReverseOrder(int index);
    void printReverseOrder();

    ~DoublyLinkedList();

    friend ostream& operator<<(ostream& screen, DoublyLinkedList& rgt);
};

#endif
