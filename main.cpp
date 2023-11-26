#include <iostream>
using namespace std;
#include "alarm_clock.h"



int main() {

    AlarmClock alarmClock;
    cout << alarmClock.empty() << endl;

    cout << alarmClock;


    alarmClock.insert(41580);
    alarmClock.insert(41640);
    alarmClock.insert(41700);
    alarmClock.insert(41760);
    alarmClock.insert(41820);
    alarmClock.insert(41880);
    alarmClock.insert(41940);

    cout << alarmClock.empty() << endl;

    cout << alarmClock;

    alarmClock.erase(4);

    cout << alarmClock;

    alarmClock.update();

    return 0;
}
