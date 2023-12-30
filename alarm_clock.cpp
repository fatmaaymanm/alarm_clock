//
// Created by Fatma on 11/5/2023.
//
#include <iomanip> // Include this for std::setw
#include <ctime>
#include "alarm_clock.h"
#include <fstream>
#include <cstring>
#include <string>
AlarmClock::AlarmClock() : first(0), mySize(0) {}

// Definition of empty()
bool AlarmClock::empty() const {
    return mySize == 0;
}

//-- Definition of the destructor
AlarmClock::~AlarmClock() {
    AlarmClock::NodePointer prev = first, ptr;
    while (prev != 0)
    {
        ptr = prev->next;
        delete prev;
        prev = ptr;
    }
}
//Definition of insert()
void AlarmClock::insert(ElementType time, bool ON, bool Sun, bool Mon, bool Tue, bool Wed, bool Thu, bool Fri,  bool Sat) {
    if(time > 86399 || time < 0) {
        cerr << "Illegal time -- terminating execution";
        exit(1);
    }
    NodePointer newNode = new Node(time, ON, Sun, Mon, Tue, Wed, Thu, Fri, Sat);
    newNode->manageAlarm();
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
    writeToFile();
}


//-- Definition of erase()
void AlarmClock::erase(int index) {
    if (index < 0 || index >= mySize)
    {
        cerr << "Illegal location to delete -- " << index << endl;
        return;
    }
    mySize--;
    NodePointer ptr, predPtr = first;
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
        writeToFile();
    }
}


//-----------------------------------------------------------------------------------------------------------------------------------

// notify function

void AlarmClock::notify() {
     NodePointer ptr = first;
     int hours, minutes, seconds;
        //seconds = hours * 60 * 60 + minutes * 60 + remaining seconds
        // 10:50:20 = 10 * 60 * 60 + 50 * 60 + 20
        // 01:30:00
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

    }

//-----------------------------------------------------------------------------------------------------------------------------------

//-- Definition of the output operator
ostream& operator<<(ostream& out, const AlarmClock& aList) {
    aList.display(out);
    return out;
}

//istream& operator>>(istream& in, AlarmClock& aList) {
//    ElementType val;
//    in >> val;
//    aList.insert(val);
//    return in;
//}

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

AlarmClock::NodePointer AlarmClock::sort(NodePointer head) {

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
            if (curr1->time - currentTime < curr2->time - currentTime) {
                if (si == nullptr) {
                    si = curr1;
                    ei = curr1;
                } else {
                    ei->next = curr1;
                    ei = curr1;
                }
                curr1 = curr1->next;
            } else if (curr1->time - currentTime == curr2->time - currentTime) {
                if (curr1->ON && !curr2->ON) {
                    if (si == nullptr) {
                        si = curr1;
                        ei = curr1;
                    } else {
                        ei->next = curr1;
                        ei = curr1;
                    }
                    curr1 = curr1->next;
                } else if (curr1->ON && curr2->ON) {
                    if ((curr1->day[today]) || curr1->checkRepeat()) {
                        if (si == nullptr) {
                            si = curr1;
                            ei = curr1;
                        } else {
                            ei->next = curr1;
                            ei = curr1;
                        }
                        curr1 = curr1->next;
                    } else if (curr2->day[today] || curr2->checkRepeat()) {
                        if (si == nullptr) {
                            si = curr2;
                            ei = curr2;
                        } else {
                            ei->next = curr2;
                            ei = curr2;
                        }
                        curr2 = curr2->next;
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
    for (;;) {
        int currentlyPrinting = -1;
        int currentTime = (time(nullptr) + 7200) % 86400;
        if (currentTime == first->time && first->ON) {
            if (first->day[today]) {
                currentlyPrinting = currentTime;
                notify();
                turnOff(currentTime);
                while (currentlyPrinting == currentTime)
                    currentTime = (time(nullptr) + 7200) % 86400;
                sort(first);
                writeToFile();
            } else if(first->checkRepeat()) {
                currentlyPrinting = currentTime;
                notify();
                turnOff(currentTime);
                while (currentlyPrinting == currentTime)
                    currentTime = (time(nullptr) + 7200) % 86400;
                first->ON = false;
                sort(first);
                writeToFile();
            } else {
                currentlyPrinting = currentTime;
                while (currentlyPrinting == currentTime)
                    currentTime = (time(nullptr) + 7200) % 86400;
                sort(first);
                writeToFile();
            }
        } else if (currentTime == first->time) {
            currentlyPrinting = currentTime;
            while (currentlyPrinting == currentTime)
                currentTime = (time(nullptr) + 7200) % 86400;
            sort(first);
            writeToFile();
        }
    }
}

int AlarmClock::convertToSeconds(int hours, int minutes, int seconds, bool AM)  {
    if(AM && hours == 12)
        return minutes * 60 + seconds;
    else if (AM || hours == 12)
        return hours * 3600 + minutes * 60 + seconds;
    else
        return 43200 + hours * 3600 + minutes * 60 + seconds;
}

void AlarmClock::getToday() {
    time_t t = time(nullptr);
    today = localtime(&t)->tm_wday;
}


void AlarmClock::Node::manageAlarm() {
    Sun ? day[0] = true : day[0] = false;
    Mon ? day[1] = true : day[1] = false;
    Tue ? day[2] = true : day[2] = false;
    Wed ? day[3] = true : day[3] = false;
    Thu ? day[4] = true : day[4] = false;
    Fri ? day[5] = true : day[5] = false;
    Sat ? day[6] = true : day[6] = false;
}

bool AlarmClock::Node::checkRepeat() {
    for (int i = 0; i < 7; ++i) {
        if (day[i])
            return false;
    }
    return true;
}

void AlarmClock::turnOff(ElementType time) {
    NodePointer ptr = first;
    while (ptr->time == time) {
        if (ptr->checkRepeat()) {
            ptr->ON = false;
        }
        ptr = ptr->next;
    }
}

void AlarmClock::writeToFile() {
    ofstream outputFile;
    outputFile.open("myAlarms.txt", ios::trunc);
    NodePointer ptr = first;
    while (ptr != nullptr) {
        outputFile << ptr->time << " " << (ptr->ON ? "1" : "0") << " " << (ptr->Sun ? "1" : "0") << " "
        << (ptr->Mon ? "1" : "0") << " " << (ptr->Tue ? "1" : "0") << " " << (ptr->Wed ? "1" : "0") << " "
        << (ptr->Thu ? "1" : "0") << " " << (ptr->Fri ? "1" : "0") << " " << (ptr->Sat ? "1" : "0") << endl;
        ptr = ptr->next;
    }
    outputFile.close();
}

void AlarmClock::readFromFile() {
    char alarm[22];
    char *p;
    int alarm_data[9];
    int i = 0;
    ifstream inputFile;
    inputFile.open("myAlarms.txt", ios::in);
    while (inputFile.good()) {
        inputFile.getline(alarm, 22);
        if (inputFile.eof())
            break;
        p = strtok(alarm, " ");
        while (p != nullptr) {
            alarm_data[i] = stoi(p);
            if (i == 9)
                break;
            p = strtok(nullptr, " ");
            i++;
        }
        i = 0;
        insert(alarm_data[0], alarm_data[1], alarm_data[2], alarm_data[3], alarm_data[4],
               alarm_data[5],alarm_data[6], alarm_data[7],alarm_data[8]);
    }
    inputFile.close();

}

void AlarmClock::getAlarmInfo(NodePointer ptr, int &hours, int &minutes, int &seconds, bool &AM, bool &Sun, bool &Mon,
                              bool &Tue, bool &Wed, bool &Thu, bool &Fri, bool &Sat) {
    seconds = ptr->time;
    hours = seconds / 3600;
    seconds -= hours * 3600;
    if (hours == 0 || hours == 12)
        hours = 12;
    else
        hours = hours % 12;
    minutes = seconds / 60;
    seconds -= minutes * 60;
    AM = ptr->isAM;
    Sun = ptr->Sun;
    Mon = ptr->Mon;
    Tue = ptr->Tue;
    Wed = ptr->Wed;
    Thu = ptr->Thu;
    Fri = ptr->Fri;
    Sat = ptr->Sat;
}

AlarmClock::NodePointer AlarmClock::getFirst() {
    return first;
}

