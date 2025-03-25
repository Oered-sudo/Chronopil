#include "password_manager.h"

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