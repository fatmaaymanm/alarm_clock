//
// Created by Fatma on 11/5/2023.
//
#include <iomanip> // Include this for std::setw
#include <ctime>
#include "alarm_clock.h"
AlarmClock::AlarmClock() : first(0), mySize(0) {}

// Definition of empty()
bool AlarmClock::empty() const {
    return mySize == 0;
}

//-- Definition of the destructor
/*inline*/ AlarmClock::~AlarmClock() {
    AlarmClock::NodePointer prev = first, ptr;
    while (prev != 0)
    {
        ptr = prev->next;
        delete prev;
        prev = ptr;
    }
}
//Definition of insert()
void AlarmClock::insert(ElementType time) {
   NodePointer newNode = new Node(time);
   if (first == NULL) {
    first = newNode;
    mySize++;
    return;
  }
 NodePointer current = first;
  while (current->next != NULL) {
    current = current->next;
  }
 current->next = newNode;
  mySize++;
  sort(first);
}


//-- Definition of erase()
void AlarmClock::erase(int index) {
    if (index < 0 || index >= mySize)
    {
        cerr << "Illegal location to delete -- " << index << endl;
        return;
    }
    mySize--;
    AlarmClock::NodePointer ptr,
        predPtr = first;
    if (index == 0)
    {
        ptr = first;
        first = ptr->next;
        delete ptr;
    } else {
        for (int i = 1; i < index; i++)
            predPtr = predPtr->next;
        ptr = predPtr->next;
        predPtr->next = ptr->next;
        delete ptr;
    }
}


//-----------------------------------------------------------------------------------------------------------------------------------

// notify function

void AlarmClock::notify() {
     NodePointer ptr = first;
     int hours, minutes, seconds;

        seconds = ptr->time;
        hours = seconds / 3600;
        seconds -= hours * 3600;
        minutes = seconds / 60;
        seconds -= minutes * 60;
        if (hours == 0 || hours == 12) {
            cout <<" It's the alarm time!! "<< "12:" << setw(2) << setfill('0') << minutes <<  ':' << setw(2) << setfill('0')
            << seconds << "  " << (ptr->isAM ? "AM" : "PM") << endl;
        } else {
            cout <<" It's the alarm time!! " << setw(2) << setfill('0') << hours % 12 << ':' << setw(2) << setfill('0')
            << minutes << ':' << setw(2) << setfill('0') << seconds << "  " << (ptr->isAM ? "AM" : "PM") << endl;
        }

    sort(first);

    }

//-----------------------------------------------------------------------------------------------------------------------------------

//-- Definition of the output operator
ostream& operator<<(ostream& out, const AlarmClock& aList) {
    aList.display(out);
    return out;
}

istream& operator>>(istream& in, AlarmClock& aList) {
    ElementType val;
    in >> val;
    aList.insert(val);
    return in;
}

AlarmClock::NodePointer AlarmClock::middle(NodePointer head, NodePointer tail) const {
    NodePointer slow = head;
    NodePointer fast = head;

    while(fast != tail && fast->next != tail){
        slow = slow->next;
        fast = fast->next->next;
    }
    NodePointer afterMiddle = slow->next;
    slow->next = nullptr;
    return afterMiddle;
}

AlarmClock::NodePointer AlarmClock::sort(AlarmClock::NodePointer head) {

    int currentTime = (time(nullptr) + 7200) % 86400;

    if (head == nullptr || head->next == nullptr)
        return head;

    NodePointer tail = head;

    while(tail->next){
        tail = tail->next;
    }


    NodePointer afterMiddle = middle(head, tail);
    NodePointer part1 = sort(head);
    NodePointer part2 = sort(afterMiddle);

    NodePointer curr1 = part1, curr2 = part2;
    NodePointer si = nullptr, ei = nullptr;

    while(curr1 && curr2) {
        if ((curr1->time - currentTime >= 0 && curr2->time - currentTime >= 0)
        || (curr1->time - currentTime < 0 && curr2->time - currentTime < 0)) {
            if (curr1->time - currentTime <= curr2->time - currentTime) {
                if (si == nullptr) {
                    si = curr1;
                    ei = curr1;
                } else {
                    ei->next = curr1;
                    ei = curr1;
                }
                curr1 = curr1->next;
            } else {
                if (si == nullptr) {
                    si = curr2;
                    ei = curr2;
                } else {
                    ei->next = curr2;
                    ei = curr2;
                }
                curr2 = curr2->next;
            }
        } else {
            if (curr1->time - currentTime > curr2->time - currentTime) {
                if (si == nullptr) {
                    si = curr1;
                    ei = curr1;
                } else {
                    ei->next = curr1;
                    ei = curr1;
                }
                curr1 = curr1->next;
            } else {
                if (si == nullptr) {
                    si = curr2;
                    ei = curr2;
                } else {
                    ei->next = curr2;
                    ei = curr2;
                }
                curr2 = curr2->next;
            }
        }
    }

    while(curr1){
        ei->next = curr1;
        ei = curr1;
        curr1 = curr1->next;
    }

    while(curr2){
        ei->next = curr2;
        ei = curr2;
        curr2 = curr2->next;
    }

    first = si;
    return first;
}

void AlarmClock::display(ostream &out) const {

    if (empty()) {
        cerr << "**** List is empty ****" << endl;
        return;
    }
    NodePointer ptr = first;
    int hours, minutes, seconds;
    for (int i = 0; i < mySize; ++i) {
        seconds = ptr->time;
        hours = seconds / 3600;
        seconds -= hours * 3600;
        minutes = seconds / 60;
        seconds -= minutes * 60;
        if (hours == 0 || hours == 12) {
            out << "12:" << setw(2) << setfill('0') << minutes <<  ':' << setw(2) << setfill('0')
            << seconds << " " << (ptr->isAM ? "AM" : "PM") << endl;
        } else {
            out << setw(2) << setfill('0') << hours % 12 << ':' << setw(2) << setfill('0')
            << minutes << ':' << setw(2) << setfill('0') << seconds << " " << (ptr->isAM ? "AM" : "PM") << endl;
        }
        ptr = ptr->next;
    }
}

[[noreturn]] void AlarmClock::update() {
    int currentlyPrinting = -1;
    for (;;) {
        sort(first);
        int currentTime = (time(nullptr) + 7200) % 86400;
        if (currentTime == first->time && currentlyPrinting != currentTime) {
            currentlyPrinting = currentTime;
            notify();
            continue;
        } else {
            currentlyPrinting = -1;
        }
    }
}



