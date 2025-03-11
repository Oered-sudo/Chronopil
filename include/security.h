#include "alarms.h"
#include <EEPROM.h>

#ifndef SECURITY_H
#define SECURITY_H

void setupSecurity();
bool checkFingerprint();
bool checkSecurityCode();

#endif // SECURITY_H
