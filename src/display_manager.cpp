#include "display_manager.h"

enum MenuState {
  MAIN_MENU,
  SET_ALARM,
  VIEW_ALARMS,
  UNLOCK_PILLBOX
};

MenuState currentMenu = MAIN_MENU;
int selectedOption = 0;

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

void displayAlarms(Adafruit_SSD1306 &display) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Alarms:"));

  int y = 10; // Vertical position for displaying alarms
  for (const auto &alarm : alarms) {
    display.setCursor(0, y);
    display.print(alarm.hour);
    display.print(":");
    if (alarm.minute < 10) display.print("0"); // Add leading zero for minutes < 10
    display.print(alarm.minute);
    display.print(" every ");
    display.print(alarm.intervalDays);
    display.print(" days until ");
    display.print(alarm.limit.day());
    display.print("/");
    display.print(alarm.limit.month());
    display.print("/");
    display.print(alarm.limit.year());
    display.print(alarm.active ? " (Active)" : " (Inactive)");
    y += 10; // Line spacing
  }

  display.display();
}

void loop() {
  handleButtons();
  displayMenu();
}

void handleButtons() {
  if (digitalRead(BUTTON_UP_PIN) == LOW) {
    selectedOption--;
    if (selectedOption < 0) selectedOption = 2;
    delay(200);
  }
  if (digitalRead(BUTTON_DOWN_PIN) == LOW) {
    selectedOption++;
    if (selectedOption > 2) selectedOption = 0;
    delay(200);
  }
  if (digitalRead(BUTTON_RIGHT_PIN) == LOW) {
    switch (selectedOption) {
      case 0:
        currentMenu = SET_ALARM;
        break;
      case 1:
        currentMenu = VIEW_ALARMS;
        break;
      case 2:
        currentMenu = UNLOCK_PILLBOX;
        break;
    }
    delay(200);
  }
  if (digitalRead(BUTTON_LEFT_PIN) == LOW) {
    currentMenu = MAIN_MENU;
    delay(200);
  }
}

void displayMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  switch (currentMenu) {
    case MAIN_MENU:
      display.setCursor(0, 0);
      display.println(F("Main Menu"));
      display.setCursor(0, 10);
      display.println(selectedOption == 0 ? "> Set Alarm" : "  Set Alarm");
      display.setCursor(0, 20);
      display.println(selectedOption == 1 ? "> View Alarms" : "  View Alarms");
      display.setCursor(0, 30);
      display.println(selectedOption == 2 ? "> Unlock Pillbox" : "  Unlock Pillbox");
      break;

    case SET_ALARM:
      display.setCursor(0, 0);
      display.println(F("Set Alarm"));
      display.setCursor(0, 10);
      display.println(F("Use buttons to set time"));
      break;

    case VIEW_ALARMS:
      display.setCursor(0, 0);
      display.println(F("View Alarms"));
      displayAlarms(display);
      break;

    case UNLOCK_PILLBOX:
      display.setCursor(0, 0);
      display.println(F("Unlocking..."));
      unlockPillbox();
      delay(5000);
      lockPillbox();
      currentMenu = MAIN_MENU;
      break;
  }

  display.display();
}