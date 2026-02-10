/**
* Iterator.cpp
* Bağlı liste üzerinde gezinmeyi sağlayan Iterator sınıfı. Düğümler arasında dolaşır ve Shape nesnelerine erişim sağlar.
* Bilgisayar Mühendisliği 3. Sınıf (2/A)
* 1. Ödev 
* 23.11.2025
* Abdullah Sait AVCI
*/

#include "Iterator.hpp"

Iterator::Iterator() {
    head = nullptr;
    current = nullptr;
    prev = nullptr;
}

Iterator::Iterator(Node* head) {
    this->head = head;
    this->current = head->next;  //İlk gerçek düğümü işaret et
    prev = nullptr;
}

bool Iterator::hasNext() {
    return current != nullptr;
}

Shape* Iterator::next() {
    if (current == nullptr) throw "NULL Reference";
    prev = current;
    current = current->next;
    return prev->item;
}

void Iterator::remove() {
    if (prev == nullptr) throw "NULL Reference";

    //prev düğümünü listeden kopar
    Node* itr = head;
    for (; itr->next != prev; itr = itr->next) {
        //boş döngü
    }

    Node* del = itr->next;
    itr->next = itr->next->next;

    delete del->item;   //Shape nesnesini de serbest bırak
    delete del;

    prev = nullptr;
}
