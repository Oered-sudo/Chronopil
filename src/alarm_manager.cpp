#include "alarms.h"
#include "alarm_manager.h"
#include <EEPROM.h>

std::vector<Alarm> alarms;

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

void setAlarm(int hour, int minute) {
  // Logique pour programmer une alarme
}

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