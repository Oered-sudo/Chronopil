#include "alarms.h"
#include "alarm_manager.h"
#include <EEPROM.h>

std::vector<Alarm> alarms;

void addAlarm(int hour, int minute) {
  alarms.push_back({hour, minute, true});
}

void setAlarm(int hour, int minute) {
  // Logique pour programmer une alarme
}

void checkAlarms(RTC_DS3231 &rtc, Adafruit_SSD1306 &display) {
  DateTime now = rtc.now();
  for (auto &alarm : alarms) {
    if (alarm.active && now.hour() == alarm.hour && now.minute() == alarm.minute) {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("Alarm Triggered!");
      display.display();
      alarm.active = false; // Désactiver l'alarme après déclenchement
    }
  }
}