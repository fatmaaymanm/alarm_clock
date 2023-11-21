//
// Created by Fatma on 11/5/2023.
//
#include <iomanip> // Include this for std::setw
#include <ctime>
#include "alarm_clock.h"
AlarmClock::AlarmClock() : first(0), mySize(0) {}

// Definition of empty()
bool AlarmClock::empty() {
    return mySize == 0;
}
//-- Definition of the destructor
inline AlarmClock::~AlarmClock() {
    AlarmClock::NodePointer prev = first, ptr;
    while (prev != 0)
    {
        ptr = prev->next;
        delete prev;
        prev = ptr;
    }
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


-----------------------------------------------------------------------------------------------------------------------------------

// notify function

void AlarmClock::notify() {
    time_t currentTime = time(0);
    tm* localTime = localtime(&currentTime);

    int currentHour = localTime->tm_hour;
    int currentMinute = localTime->tm_min;

    NodePointer current = first;
    while (current != nullptr) {
        int alarmHour = current->time / 100;     // Extract hours
        int alarmMinute = current->time % 100;   // Extract minutes

        // Adjust for PM if needed
        if (!current->isAM && alarmHour < 12) {
            alarmHour += 12;
        }

        if (currentHour == alarmHour && currentMinute == alarmMinute) {
            cout << "Alarm! Time: " << std::setw(2) << std::setfill('0') << alarmHour << ":"
                 << std::setw(2) << std::setfill('0') << alarmMinute
                 << " " << (current->isAM ? "AM" : "PM") << endl;
        }
        current = current->next;
    }
}

-----------------------------------------------------------------------------------------------------------------------------------

//-- Definition of the output operator
ostream& operator<<(ostream& out, const AlarmClock& aList) {
    aList.display(out);
    return out;
}

istream& operator>>(istream& in, AlarmClock& aList) {
    ElementType val;
    in >> val;
    aList.insert(val, aList.mySize); // Needed friend to access "mySize"
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

    currentTime = (time(nullptr) + 7200) % 86400;

    if (first == nullptr || first->next == nullptr)
        return first;

    NodePointer tail = first;

    while(tail->next){
        tail = tail->next;
    }

    NodePointer part1 = sort(first);
    NodePointer part2 = sort(middle(first, tail));

    NodePointer curr1 = part1, curr2 = part2;
    NodePointer si = nullptr, ei = nullptr;

    while(curr1 && curr2) {
        if (curr1->time - currentTime >= 0 && curr2->time - currentTime >= 0) {
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
    NodePointer ptr = first;
    int hours, minutes, seconds;
    for (int i = 0; i < mySize; ++i) {
        seconds = ptr->time;
        hours = seconds / 3600;
        seconds -= hours * 3600;
        minutes = seconds / 60;
        seconds -= minutes * 60;
        if (hours == 0 || hours == 12) {
            out << "12:" << minutes << ':' << seconds << "  " << (ptr->isAM ? "AM" : "PM") << endl;
        } else {
            out << hours % 12 << ':' << minutes << ':' << seconds << (ptr->isAM ? "AM" : "PM") << endl;
        }
        ptr = ptr->next;
    }
}

[[noreturn]] void AlarmClock::update() {
    while (true) {
        currentTime = (time(nullptr) + 7200) % 86400;
        if (currentTime == first->time) {
            notify();
        }
    }
}



