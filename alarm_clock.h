
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
        Node() : next(0) {}
        Node(ElementType time) : time(time), next(0) {
            if (time < 43200)
                isAM = true;
            else
                isAM = false;
        }
    };

    typedef Node* NodePointer;
    NodePointer first;
    int mySize;
public:
    AlarmClock();
    ~AlarmClock();
    bool empty() const;
    void insert(ElementType time);
    void erase(int index);
    void display(ostream& out) const;
    int nodeCount();
    NodePointer sort(AlarmClock::NodePointer head);
    NodePointer middle(NodePointer head, NodePointer tail) const;
    void notify();

    [[noreturn]] void update();
    const AlarmClock& operator=(const AlarmClock& rightSide);
    AlarmClock operator>(const AlarmClock& rightHandSide);
    friend istream& operator>>(istream& in, AlarmClock& aList);
};

ostream& operator<<(ostream& out, const AlarmClock& aList);
istream& operator>>(istream& in, AlarmClock&aList);


#endif //ALARM_CLOCK
