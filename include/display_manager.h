#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>

// Déclarations des fonctions
void initDisplay(Adafruit_SSD1306 &display, RTC_DS3231 &rtc);
void displayTime(Adafruit_SSD1306 &display, RTC_DS3231 &rtc);
void displayCalendar(Adafruit_SSD1306 &display, RTC_DS3231 &rtc);
void handlePasswordSelector(Adafruit_SSD1306 &display, char *inputPassword, int &passwordIndex);
void checkAlarms();

#endif // DISPLAY_MANAGER_H