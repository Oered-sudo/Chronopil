#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <Adafruit_SSD1306.h>
#include "constants.h"

void handlePasswordSelector(Adafruit_SSD1306 &display, char *inputPassword, int &passwordIndex);

#endif // PASSWORD_MANAGER_H