#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Fingerprint.h>
#include <EEPROM.h>
#include <Servo.h>
#include <RTClib.h>
#include "display_manager.h"
#include "security.h"
#include <vector>

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
Servo servoPillbox; // Nouveau servomoteur pour la boîte à pilules

// Structure pour représenter une alarme
struct Alarm {
  int hour;    // Heure de l'alarme
  int minute;  // Minute de l'alarme
  bool active; // Si l'alarme est active
};

// Liste des alarmes
std::vector<Alarm> alarms;

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
void setupIRSensor();
bool isPresenceDetected();
void closePillbox(); // Fonction pour fermer la boîte à pilules
void addAlarm(int hour, int minute);
void checkAlarms(RTC_DS3231 &rtc);
void displayAlarms(Adafruit_SSD1306 &display);

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
  setupIRSensor();

  // Ajouter des alarmes de test
  addAlarm(8, 30); // Alarme à 8h30
  addAlarm(14, 45); // Alarme à 14h45
}

void loop() {
  handleAlarms();
  handleButtons();
  displayTime(display, rtc);
  displayCalendar(display, rtc);
  handlePasswordSelector(display, inputPassword, passwordIndex);

  // Vérifier les alarmes
  checkAlarms(rtc);

  // Afficher les alarmes
  displayAlarms(display);

  // Exemple d'utilisation des fonctions de sécurité
  if (checkFingerprint()) {
    Serial.println("Fingerprint verified!");
  }

  // Fermer la boîte à pilules si nécessaire
  closePillbox();
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
  servoPillbox.attach(8); // Pin du servomoteur pour la boîte à pilules
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

void setupIRSensor() {
  // Logique pour configurer le capteur IR
}

bool isPresenceDetected() {
  // Logique pour détecter la présence avec le capteur IR
  return false;
}

void closePillbox() {
  // Exemple : fermer la boîte à pilules en déplaçant le servomoteur à 0°
  controlServo(servoPillbox, 0);
  delay(1000); // Attendre que le servomoteur atteigne la position
}

// Ajouter une nouvelle alarme
void addAlarm(int hour, int minute) {
  Alarm newAlarm = {hour, minute, true};
  alarms.push_back(newAlarm);
  Serial.print("Alarme ajoutée : ");
  Serial.print(hour);
  Serial.print(":");
  Serial.println(minute);
}

// Vérifier si une alarme doit être déclenchée
void checkAlarms(RTC_DS3231 &rtc) {
  DateTime now = rtc.now();
  for (auto &alarm : alarms) {
    if (alarm.active && now.hour() == alarm.hour && now.minute() == alarm.minute) {
      Serial.println("Alarme déclenchée !");
      // Ajoutez ici la logique pour déclencher une action (exemple : sonnerie, affichage, etc.)
      alarm.active = false; // Désactiver l'alarme après déclenchement
    }
  }
}

// Afficher les alarmes sur l'écran OLED
void displayAlarms(Adafruit_SSD1306 &display) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Alarmes :"));

  int y = 10; // Position verticale pour afficher les alarmes
  for (const auto &alarm : alarms) {
    display.setCursor(0, y);
    display.print(alarm.hour);
    display.print(":");
    if (alarm.minute < 10) display.print("0"); // Ajouter un zéro pour les minutes < 10
    display.print(alarm.minute);
    display.print(alarm.active ? " (Active)" : " (Inactive)");
    y += 10; // Espacement entre les lignes
  }

  display.display();
}