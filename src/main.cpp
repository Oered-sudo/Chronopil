#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Fingerprint.h>
#include <EEPROM.h>
#include <Servo.h>
#include <RTClib.h>
#include "display_manager.h"
#include "security.h"

// Déclarations des constantes et des variables
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SSD1306_I2C_ADDRESS 0x3C // Adresse I2C de l'écran OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define FINGERPRINT_RX_PIN 2
#define FINGERPRINT_TX_PIN 3
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);

#define BATTERY_PIN A0
#define MOTOR_PIN_1 4
#define MOTOR_PIN_2 5
#define MOTOR_PIN_3 6
#define MOTOR_PIN_4 7
#define MOTOR_PIN_5 12

// Déclarations des pins des boutons
#define BUTTON_UP_PIN 8
#define BUTTON_DOWN_PIN 9
#define BUTTON_LEFT_PIN 10
#define BUTTON_RIGHT_PIN 11
#define BUTTON_STOP_PIN 12
#define BUTTON_OFF_PIN 13

// Déclarations des pins pour le capteur à ultrasons
#define ULTRASONIC_TRIG_PIN 16
#define ULTRASONIC_ECHO_PIN 17

// Déclarations des servomoteurs
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

// Déclarations des fonctions
void setupMotors();
void setupFingerprintSensor();
void checkBatteryLevel();
void displayMenu();
void handleAlarms();
void lockMechanism();
void unlockMechanism();
void setupButtons();
void handleButtons();
void setupServos();
void controlServo(Servo &servo, int angle);
void setupUltrasonicSensor();
long readUltrasonicDistance();

RTC_DS3231 rtc;
char password[5] = "0000"; // Mot de passe initial
char inputPassword[5] = "";
int passwordIndex = 0;

void setup() {
  Serial.begin(115200);
  initDisplay(display, rtc);
  setupMotors();
  setupSecurity();
  checkBatteryLevel();
  displayMenu();
  setupButtons();
  setupServos();
  setupUltrasonicSensor();
}

void loop() {
  handleAlarms();
  handleButtons();
  displayTime(display, rtc);
  displayCalendar(display, rtc);
  handlePasswordSelector(display, inputPassword, passwordIndex);

  // Exemple d'utilisation des fonctions de sécurité
  if (checkFingerprint()) {
    Serial.println("Fingerprint verified!");
  }

  // Enregistrer une nouvelle empreinte digitale avec l'ID 1
  if (enrollFingerprint(1)) {
    Serial.println("Fingerprint enrolled!");
  }

  // Supprimer une empreinte digitale avec l'ID 1
  deleteFingerprint(1);
}

void setupMotors() {
  pinMode(MOTOR_PIN_1, OUTPUT);
  pinMode(MOTOR_PIN_2, OUTPUT);
  pinMode(MOTOR_PIN_3, OUTPUT);
  pinMode(MOTOR_PIN_4, OUTPUT);
}

void setupFingerprintSensor() {
  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }
}

void checkBatteryLevel() {
  int batteryLevel = analogRead(BATTERY_PIN);
  // Logique pour afficher le niveau de batterie sur l'écran
}

void displayMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Menu de programmation"));
  display.display();
}

void handleAlarms() {
  // Logique pour gérer les alarmes
}

void lockMechanism() {
  // Logique pour verrouiller mécaniquement
}

void unlockMechanism() {
  // Logique pour déverrouiller mécaniquement
}

void setupButtons() {
  pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
  pinMode(BUTTON_LEFT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_STOP_PIN, INPUT_PULLUP);
  pinMode(BUTTON_OFF_PIN, INPUT_PULLUP);
}

void handleButtons() {
  if (digitalRead(BUTTON_UP_PIN) == LOW) {
    // Action pour le bouton UP
  }
  if (digitalRead(BUTTON_DOWN_PIN) == LOW) {
    // Action pour le bouton DOWN
  }
  if (digitalRead(BUTTON_LEFT_PIN) == LOW) {
    // Action pour le bouton LEFT
  }
  if (digitalRead(BUTTON_RIGHT_PIN) == LOW) {
    // Action pour le bouton RIGHT
  }
  if (digitalRead(BUTTON_STOP_PIN) == LOW) {
    // Action pour le bouton STOP
  }
  if (digitalRead(BUTTON_OFF_PIN) == LOW) {
    // Action pour le bouton OFF
  }
}

void setupServos() {
  servo1.attach(4); // Pin du servo 1
  servo2.attach(5); // Pin du servo 2
  servo3.attach(6); // Pin du servo 3
  servo4.attach(7); // Pin du servo 4
}

void controlServo(Servo &servo, int angle) {
  servo.write(angle);
}

void setupUltrasonicSensor() {
  pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
  pinMode(ULTRASONIC_ECHO_PIN, INPUT);
}

long readUltrasonicDistance() {
  // Envoie une impulsion de 10 microsecondes sur le pin Trig
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);

  // Mesure la durée de l'impulsion sur le pin Echo
  long duration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH);

  // Calcul de la distance en centimètres
  long distance = duration * 0.034 / 2;

  return distance;
}