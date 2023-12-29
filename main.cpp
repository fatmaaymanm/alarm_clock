#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "alarm_clock.h"

using namespace std;


int main() {
    AlarmClock alarmClock;
    alarmClock.getToday();
    alarmClock.readFromFile();
    cout << alarmClock << endl;
}
