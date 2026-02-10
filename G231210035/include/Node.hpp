#ifndef NODE_HPP
#define NODE_HPP

#include "Shape.hpp"

class Node {
public:
    Shape* item;
    Node* next;

    Node(Shape* item = nullptr, Node* nx = nullptr);
};

#endif
