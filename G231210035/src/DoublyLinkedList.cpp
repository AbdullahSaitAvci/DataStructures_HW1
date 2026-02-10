/**
* DoublyLinkedList.cpp
* Çift yönlü bağlı liste sınıfı. Her düğüm bir LinkedList nesnesi tutar ve bir sonraki/önceki düğüme işaret eder.
* Bilgisayar Mühendisliği 3. Sınıf (2/A)
* 1. Ödev 
* 23.11.2025
* Abdullah Sait AVCI
*/

#include "DoublyLinkedList.hpp"
#include "LinkedList.hpp"

DNode* DoublyLinkedList::FindPreviousByPosition(int index) {
    if (index < 0 || index > size) {
        throw NoSuchElement("No Such Element");
    }

    DNode* prv = head;
    int i = 1;

    for (DNode* itr = head; itr->next != NULL && i != index; itr = itr->next, i++) {
        prv = prv->next;
    }
    return prv;
}

DoublyLinkedList::DoublyLinkedList() {
    head = NULL;
    size = 0;
}

int DoublyLinkedList::Count() const {
    return size;
}

bool DoublyLinkedList::isEmpty() const {
    return size == 0;
}

void DoublyLinkedList::add(LinkedList* item) {
    insert(size, item);
}

void DoublyLinkedList::insert(int index, LinkedList* item) {
    if (index < 0 || index > size) {
        throw NoSuchElement("Index out of range");
    }

    if (index == 0) {
        head = new DNode(item, head, NULL);
        if (head->next != NULL) {
            head->next->prev = head;
        }
    } else {
        DNode* prv = FindPreviousByPosition(index);
        prv->next = new DNode(item, prv->next, prv);
        if (prv->next->next != NULL) {
            prv->next->next->prev = prv->next;
        }
    }

    size++;
}

LinkedList* DoublyLinkedList::first() {
    if (isEmpty()) throw NoSuchElement("No Such Element");
    return head->data;
}

LinkedList* DoublyLinkedList::last() {
    if (isEmpty()) throw NoSuchElement("No Such Element");
    return FindPreviousByPosition(size)->data;
}

int DoublyLinkedList::indexOf(LinkedList* item) {
    int index = 0;
    for (DNode* itr = head; itr != NULL; itr = itr->next) {
        if (itr->data == item) return index;
        index++;
    }
    throw NoSuchElement("No Such Element");
}

void DoublyLinkedList::remove(LinkedList* item) {
    int index = indexOf(item);
    removeAt(index);
}

void DoublyLinkedList::removeAt(int index) {
    if (index < 0 || index >= size) {
        throw "Index out of Range";
    }

    DNode* del;

    if (index == 0) {
        del = head;
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        }
    } else {
        DNode* prv = FindPreviousByPosition(index);
        del = prv->next;
        prv->next = del->next;
        if (del->next != NULL) {
            del->next->prev = prv;
        }
    }

    size--;

    // İçindeki LinkedList'i de temizle
    if (del->data != NULL) {
        delete del->data;   // LinkedList destructor'ı Shape* listesini temizleyecek
    }
    delete del;
}

bool DoublyLinkedList::find(LinkedList* item) {
    for (DNode* itr = head; itr != NULL; itr = itr->next) {
        if (itr->data == item) return true;
    }
    return false;
}

LinkedList* DoublyLinkedList::elementAt(int index) {
    if (index < 0 || index >= size) {
        throw NoSuchElement("No Such Element");
    }
    if (index == 0) return head->data;
    return FindPreviousByPosition(index)->next->data;
}

void DoublyLinkedList::reverse() {
    for (DNode* itr = head; itr != NULL;) {
        DNode* tmp = itr->next;
        itr->next = itr->prev;
        itr->prev = tmp;
        if (tmp == NULL) {
            head = itr;
            break;
        }
        itr = tmp;
    }
}

void DoublyLinkedList::clear()
{
    while (size > 0) {
        removeAt(0);   // removeAt zaten LinkedList* ve içindeki tüm Shape*’leri siliyor
    }
}

ostream& operator<<(ostream& screen, DoublyLinkedList& rgt) {
    for (DNode* itr = rgt.head; itr != NULL; itr = itr->next) {
        screen << itr->data << " <-> ";  // burada LinkedList* adresi yazılır
    }
    screen << endl;
    return screen;
}

void DoublyLinkedList::printNodesFromPositionInReverseOrder(int index) {
    if (index < 0 || index >= size) {
        throw NoSuchElement("No Such Element");
    }

    for (DNode* itr = FindPreviousByPosition(index + 1); itr != NULL; itr = itr->prev) {
        cout << itr->data << " <-> ";
    }
    cout << endl;
}

void DoublyLinkedList::printReverseOrder() {
    if (!isEmpty()) {
        printNodesFromPositionInReverseOrder(size - 1);
    }
}

DoublyLinkedList::~DoublyLinkedList() {
    clear();
}
