#include "servo_manager.h"

void controlServo(Servo &servo, int angle) {
  servo.write(angle);
}