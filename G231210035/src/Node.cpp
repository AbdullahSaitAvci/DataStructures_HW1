/**
* Node.cpp
* Bağlı liste düğümü (Node) sınıfı. Her düğüm bir Shape nesnesi tutar ve bir sonraki düğüme işaret eder.
* Bilgisayar Mühendisliği 3. Sınıf (2/A)
* 1. Ödev 
* 23.11.2025
* Abdullah Sait AVCI
*/

#include "Node.hpp"

Node::Node(Shape* item, Node* nx) {
    this->item = item;
    next = nx;
}
