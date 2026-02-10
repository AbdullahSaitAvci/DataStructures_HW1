/**
* DNode.cpp
* Çift yönlü bağlı liste düğümü (Node) sınıfı. Her düğüm bir Shape nesnesi tutar ve bir sonraki düğüme işaret eder.
* Bilgisayar Mühendisliği 3. Sınıf (2/A)
* 1. Ödev 
* 23.11.2025
* Abdullah Sait AVCI
*/

#include "DNode.hpp"
#include "LinkedList.hpp"

DNode::DNode(LinkedList* data, DNode* next, DNode* prev) {
    this->data = data;
    this->next = next;
    this->prev = prev;
}
