#include <iostream>
using namespace std;
#include "alarm_clock.h"



int main() {

    AlarmClock alarmClock;
    cout << alarmClock.empty() << endl;

    cout << alarmClock;


    alarmClock.insert(41580);
    alarmClock.insert(0);
    alarmClock.insert(120);
    alarmClock.insert(60);
    alarmClock.insert(180);
    alarmClock.insert(41640);
    alarmClock.insert(41700);
    alarmClock.insert(41760);
    alarmClock.insert(41820);
    alarmClock.insert(41880);
    alarmClock.insert(41940);
    alarmClock.insert(40740);
    alarmClock.insert(48900);
    alarmClock.insert(43199);
    alarmClock.insert(43200);
    alarmClock.insert(48060);
    alarmClock.insert(48120);

    cout << alarmClock.empty() << endl;

    cout << alarmClock;

    alarmClock.erase(4);

    cout << alarmClock;

    alarmClock.update();

    return 0;
}
