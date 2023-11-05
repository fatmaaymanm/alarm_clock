//
// Created by Fatma on 11/5/2023.
//

#include "alarm_clock.h"
LinkedList::LinkedList() : first(0), mySize(0) {}

//-- Definition of the destructor
inline LinkedList::~LinkedList() {
    LinkedList::NodePointer prev = first, ptr;
    while (prev != 0)
    {
        ptr = prev->next;
        delete prev;
        prev = ptr;
    }
}
