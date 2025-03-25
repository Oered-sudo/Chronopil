#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Adafruit_SSD1306.h>
#include "constants.h"

// Déclarations des fonctions
void initDisplay(Adafruit_SSD1306 &display);
void displayTime(Adafruit_SSD1306 &display, RTC_DS3231 &rtc);
void displayCalendar(Adafruit_SSD1306 &display, RTC_DS3231 &rtc);

#endif // DISPLAY_MANAGER_H