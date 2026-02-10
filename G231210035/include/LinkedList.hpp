#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "Node.hpp"
#include "Iterator.hpp"
#include "NoSuchElement.hpp"

#include <iostream>
using namespace std;



class LinkedList {
private:
    Node* head;

    Node* FindPrevByPosition(int position);

public:
    LinkedList();

    Iterator iterator();

    bool isEmpty() const;
    int  size() const;

    Shape* first();
    Shape* last();

    void add(Shape* item);
    void insert(int index, Shape* item);

    void remove(Shape* item);
    void removeAt(int index);
    

    bool  find(Shape* item) const;
    int   indexOf(Shape* item);

    void clear();

    ~LinkedList();

    friend ostream& operator<<(ostream& screen, LinkedList& right);
};

#endif
