
#ifndef ALARM_CLOCK
#define ALARM_CLOCK

#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;

typedef int ElementType;


class AlarmClock {

private:
    class Node {
    public:
        ElementType time;
        bool isAM;
        Node* next;
        bool ON;
        bool Sun;
        bool Mon;
        bool Tue;
        bool Wed;
        bool Thu;
        bool Fri;
        bool Sat;
        bool day[7];
        Node() : next(0) {}
        Node(ElementType time, bool ON, bool Sun, bool Mon, bool Tue, bool Wed, bool Thu, bool Fri,  bool Sat)
        : time(time), next(0), ON(ON), Sun(Sun), Mon(Mon), Tue(Tue), Wed(Wed), Thu(Thu), Fri(Fri), Sat(Sat) {
            if (time < 43200)
                isAM = true;
            else
                isAM = false;


        }
        void manageAlarm();
        bool checkRepeat();
    };

    typedef Node* NodePointer;
    NodePointer first;
    int mySize;
    int today;

public:
    AlarmClock();
    ~AlarmClock();
    bool empty() const;
    void insert(ElementType time, bool ON, bool Sun, bool Mon, bool Tue, bool Wed, bool Thu, bool Fri, bool Sat);
    void erase(int index);
    void display(ostream& out) const;
    NodePointer sort(AlarmClock::NodePointer head);
    NodePointer middle(NodePointer head, NodePointer tail) const;
    void notify();
    int convert(int hours, int minutes, int seconds, bool AM);
    void getToday();
    void turnOff(ElementType time);


    [[noreturn]] void update();
    //friend istream& operator>>(istream& in, AlarmClock& aList);
};

ostream& operator<<(ostream& out, const AlarmClock& aList);
istream& operator>>(istream& in, AlarmClock&aList);


#endif //ALARM_CLOCK
