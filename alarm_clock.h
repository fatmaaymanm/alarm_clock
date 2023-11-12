
#ifndef ALARM_CLOCK
#define ALARM_CLOCK

#include <iostream>
using namespace std;

typedef int ElementType;


class AlarmClock {

private:
    class Node {
    public:
        ElementType time;
        bool isAM;
        Node* next;
        Node() : next(0) {}
        Node(ElementType time, bool isAM) : time(time), isAM(isAM), next(0) {}
    };

    typedef Node* NodePointer;
    NodePointer first;
    int mySize;
public:
    AlarmClock();
    AlarmClock(const AlarmClock& origList);
    ~AlarmClock();
    bool empty();
    void insert(ElementType time);
    void erase(ElementType time);
    void display(ostream& out) const;
    int nodeCount();
    bool ascendingOrder();
    NodePointer sort(AlarmClock::NodePointer head);
    NodePointer middle(NodePointer head, NodePointer tail) const;
    void notify();
    void update();
    const AlarmClock& operator=(const AlarmClock& rightSide);
    AlarmClock operator>(const AlarmClock& rightHandSide);
};

ostream& operator<<(ostream& out, const AlarmClock& aList);
istream& operator>>(istream& in, AlarmClock&aList);


#endif //ALARM_CLOCK
