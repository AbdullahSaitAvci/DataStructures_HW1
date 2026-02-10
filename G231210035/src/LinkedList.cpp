/**
* LinkedList.cpp
* Bağlı liste sınıfı. Her düğüm bir Shape nesnesi tutar ve bir sonraki düğüme işaret eder.
* Bilgisayar Mühendisliği 3. Sınıf (2/A)
* 1. Ödev 
* 23.11.2025
* Abdullah Sait AVCI
*/

#include "LinkedList.hpp"

Node* LinkedList::FindPrevByPosition(int position) {
    if (position < 0 || position > size())
        throw NoSuchElement("Index out of range");

    int  index = 0;
    Node* itr  = head;
    for (; itr != nullptr; itr = itr->next, index++) {
        if (position == index) return itr;
    }
    return nullptr;
}

LinkedList::LinkedList() {
    // dummy head node
    head = new Node(nullptr);
}

Iterator LinkedList::iterator() {
    Iterator itr(head);
    return itr;
}

bool LinkedList::isEmpty() const {
    return head->next == nullptr;
}

int LinkedList::size() const {
    int length = 0;
    for (Node* itr = head->next; itr != nullptr; itr = itr->next) {
        length++;
    }
    return length;
}

Shape* LinkedList::first() {
    if (isEmpty()) throw NoSuchElement("List is empty");
    return head->next->item;
}

Shape* LinkedList::last() {
    if (isEmpty()) throw NoSuchElement("List is empty");
    return FindPrevByPosition(size())->item;
}

void LinkedList::add(Shape* item) {
    insert(size(), item);
}

void LinkedList::insert(int index, Shape* item) {
    Node* prev = FindPrevByPosition(index);  // burası hatalı indexte NoSuchElement fırlatır
    prev->next = new Node(item, prev->next);
}

void LinkedList::remove(Shape* item) {
    int position = indexOf(item);           // burada da bulamazsa NoSuchElement fırlatır
    removeAt(position);
}

void LinkedList::removeAt(int index) {
    if (isEmpty()) throw NoSuchElement("List is empty");

    Node* prev = FindPrevByPosition(index); // index hatalıysa yine NoSuchElement
    Node* del  = prev->next;

    if (del == nullptr) throw NoSuchElement("Index out of range");

    prev->next = del->next;

    delete del->item;   // Shape nesnesini sil
    delete del;
}

bool LinkedList::find(Shape* item) const {
    for (Node* itr = head->next; itr != nullptr; itr = itr->next) {
        if (itr->item == item) return true;
    }
    return false;
}

int LinkedList::indexOf(Shape* item) {
    int index = 0;
    for (Node* itr = head->next; itr != nullptr; itr = itr->next, index++) {
        if (itr->item == item) return index;
    }
    throw NoSuchElement("No such element in list");
}

void LinkedList::clear() {
    while (!isEmpty()) {
        removeAt(0);
    }
}

LinkedList::~LinkedList() {
    clear();
    delete head;
}

ostream& operator<<(ostream& screen, LinkedList& right) {
    if (right.isEmpty()) {
        screen << "Empty list";
    } else {
        for (Node* itr = right.head->next; itr != nullptr; itr = itr->next) {
            screen << itr->item << " ";
        }
    }
    return screen;
}

