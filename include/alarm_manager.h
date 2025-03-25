#ifndef ALARM_MANAGER_H
#define ALARM_MANAGER_H

#include <vector>
#include <RTClib.h>
#include <Adafruit_SSD1306.h>
#include "constants.h"

struct Alarm {
  int hour;         // Hour of the alarm
  int minute;       // Minute of the alarm
  bool active;      // Whether the alarm is active
  int intervalDays; // Interval in days between alarms
  DateTime limit;   // Limit date for the alarm
};

void addAlarm(int hour, int minute);
void checkAlarms(RTC_DS3231 &rtc, Adafruit_SSD1306 &display);

#endif // ALARM_MANAGER_H