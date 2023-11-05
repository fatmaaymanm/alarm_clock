
#ifndef ALARM_CLOCK
#define ALARM_CLOCK

#include <iostream>
using namespace std;

typedef int ElementType;

class AlarmClock {
private:
    class Node {
    public:
        ElementType hours;
        ElementType minutes;
        ElementType seconds;
        bool isAM;
        Node* next;
        Node() : next(0) {}
        Node(ElementType hours, ElementType minutes, ElementType seconds, bool isAM) :
        hours(hours), minutes(minutes), seconds(seconds), isAM(isAM), next(0){}
    };

    typedef Node* NodePointer;
    NodePointer first;
    int mySize;

public:
    AlarmClock();
    AlarmClock(const AlarmClock& origList);
    ~AlarmClock();
    bool empty();
    void insert(ElementType hours, ElementType minutes, ElementType seconds, bool isAM);
    void erase(ElementType hours, ElementType minutes, ElementType seconds, bool isAM);
    void display(ostream& out) const;
    int nodeCount();
    bool ascendingOrder();
    void sort();
    void notify();
    const AlarmClock& operator=(const AlarmClock& rightSide);
    AlarmClock operator>(const AlarmClock& rightHandSide);
};

ostream& operator<<(ostream& out, const AlarmClock& aList);
istream& operator>>(istream& in, AlarmClock&aList);


#endif //ALARM_CLOCK
