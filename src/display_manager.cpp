#include "display_manager.h"

void initDisplay(Adafruit_SSD1306 &display) {
  if (!display.begin(SSD1306_I2C_ADDRESS, OLED_RESET)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();
}

void displayTime(Adafruit_SSD1306 &display, RTC_DS3231 &rtc) {
  DateTime now = rtc.now();
  display.setCursor(0, 10);
  display.print(now.hour(), DEC);
  display.print(':');
  display.print(now.minute(), DEC);
  display.print(':');
  display.print(now.second(), DEC);
  display.display();
}

void displayCalendar(Adafruit_SSD1306 &display, RTC_DS3231 &rtc) {
  DateTime now = rtc.now();
  display.setCursor(0, 20);
  display.print(now.day(), DEC);
  display.print('/');
  display.print(now.month(), DEC);
  display.print('/');
  display.print(now.year(), DEC);
  display.display();
}

void handlePasswordSelector(Adafruit_SSD1306 &display, char *inputPassword, int &passwordIndex) {
  if (digitalRead(BUTTON_UP_PIN) == LOW) {
    inputPassword[passwordIndex]++;
    if (inputPassword[passwordIndex] > '9') inputPassword[passwordIndex] = '0';
    delay(200);
  }
  if (digitalRead(BUTTON_DOWN_PIN) == LOW) {
    inputPassword[passwordIndex]--;
    if (inputPassword[passwordIndex] < '0') inputPassword[passwordIndex] = '9';
    delay(200);
  }
  if (digitalRead(BUTTON_RIGHT_PIN) == LOW) {
    passwordIndex++;
    if (passwordIndex > 3) passwordIndex = 0;
    delay(200);
  }
  if (digitalRead(BUTTON_LEFT_PIN) == LOW) {
    passwordIndex--;
    if (passwordIndex < 0) passwordIndex = 3;
    delay(200);
  }
  display.setCursor(0, 30);
  display.print("Password: ");
  display.print(inputPassword);
  display.display();
}

void checkAlarms() {
  // Logique pour vérifier et gérer les alarmes
}