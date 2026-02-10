#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "Node.hpp"

class Iterator {
private:
    Node* head;
    Node* current;
    Node* prev;

public:
    Iterator();
    Iterator(Node* head);

    bool hasNext();
    Shape* next();
    void remove();
};

#endif
