#include "alarms.h"
#include "alarm_manager.h"
#include <EEPROM.h>
#include <vector>
#include <RTClib.h>

// Global list of alarms
std::vector<Alarm> alarms;

// Function to add a new alarm
void addAlarm(int hour, int minute, int intervalDays, DateTime limit) {
  Alarm newAlarm = {hour, minute, true, intervalDays, limit};
  alarms.push_back(newAlarm);
  Serial.print("Alarm added: ");
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(" every ");
  Serial.print(intervalDays);
  Serial.print(" days until ");
  Serial.print(limit.day());
  Serial.print("/");
  Serial.print(limit.month());
  Serial.print("/");
  Serial.println(limit.year());
}

// Function to set an alarm (placeholder for UI integration)
void setAlarm(int hour, int minute, int intervalDays, DateTime limit) {
  addAlarm(hour, minute, intervalDays, limit);
  Serial.println("Alarm set successfully.");
}

// Function to check and trigger alarms
void checkAlarms(RTC_DS3231 &rtc) {
  DateTime now = rtc.now();
  for (auto &alarm : alarms) {
    if (alarm.active && now <= alarm.limit) {
      if (now.hour() == alarm.hour && now.minute() == alarm.minute) {
        Serial.println("Alarm triggered!");
        // Add logic to trigger an action (e.g., sound, display message, etc.)
        alarm.active = false; // Deactivate the alarm for today

        // Reactivate the alarm for the next interval
        DateTime nextAlarmDate = now + TimeSpan(alarm.intervalDays, 0, 0, 0);
        if (nextAlarmDate <= alarm.limit) {
          alarm.active = true;
        }
      }
    }
  }
}

// Function to display all alarms (for debugging or UI purposes)
void displayAlarms() {
  Serial.println("Current Alarms:");
  for (const auto &alarm : alarms) {
    Serial.print("Time: ");
    Serial.print(alarm.hour);
    Serial.print(":");
    if (alarm.minute < 10) Serial.print("0"); // Add leading zero for single-digit minutes
    Serial.print(alarm.minute);
    Serial.print(", Interval: ");
    Serial.print(alarm.intervalDays);
    Serial.print(" days, Limit: ");
    Serial.print(alarm.limit.day());
    Serial.print("/");
    Serial.print(alarm.limit.month());
    Serial.print("/");
    Serial.print(alarm.limit.year());
    Serial.print(", Active: ");
    Serial.println(alarm.active ? "Yes" : "No");
  }
}