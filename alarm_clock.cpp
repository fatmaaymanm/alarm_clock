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



