#include <iostream>
using namespace std;
#include "alarm_clock.h"

int main() {

    AlarmClock alarmClock;
    alarmClock.getToday();
    cout << alarmClock;
    alarmClock.update();

}
