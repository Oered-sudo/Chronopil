#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LCDMenuLib2.h>

// Définition de l'écran OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 // Pas de broche de reset
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Boutons pour naviguer
#define BUTTON_UP_PIN 2
#define BUTTON_DOWN_PIN 3
#define BUTTON_LEFT_PIN 4
#define BUTTON_RIGHT_PIN 5
#define BUTTON_SELECT_PIN 6

// Définition des fonctions de menu
void mFunc_calendrier(uint8_t param);
void mFunc_alarm(uint8_t param);
void mFunc_settings(uint8_t param);

// Définition du menu avec LCDMenuLib2
LCDML_add(0, LCDML_0, 1, "Calendrier", mFunc_calendrier);
LCDML_add(1, LCDML_0, 2, "Alarmes", mFunc_alarm);
LCDML_add(2, LCDML_0, 3, "Parametres", mFunc_settings);

// Initialisation de l'objet menu
LCDML_create(0);

// Configuration initiale
void setup() {
  pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
  pinMode(BUTTON_LEFT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_SELECT_PIN, INPUT_PULLUP);

  Serial.begin(115200);

  // Initialisation de l'écran OLED
  if (!display.begin(0x3C, OLED_RESET)) { // Adresse I2C par défaut : 0x3C
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();

  // Initialisation du menu
  LCDML_setup(3, 1, 0, 0);
}

// Fonction pour afficher le menu
void displayMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println(F("Menu Principal:"));

  // Afficher le menu
  LCDML.loop();
  display.display();
}

// Fonction pour gérer les boutons
void handleButtons() {
  if (digitalRead(BUTTON_UP_PIN) == LOW) {
    LCDML.BT_setup();
    delay(200);
  }
  if (digitalRead(BUTTON_DOWN_PIN) == LOW) {
    LCDML.BT_down();
    delay(200);
  }
  if (digitalRead(BUTTON_SELECT_PIN) == LOW) {
    LCDML.BT_enter();
    delay(200);
  }
}

// Boucle principale
void loop() {
  handleButtons();
  displayMenu();
}

// Fonction pour le menu "Calendrier"
void mFunc_calendrier(uint8_t param) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F("Calendrier"));
  display.display();
  delay(2000);
  LCDML.FUNC_goBackToMenu();
}

// Fonction pour le menu "Alarmes"
void mFunc_alarm(uint8_t param) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F("Alarmes"));
  display.display();
  delay(2000);
  LCDML.FUNC_goBackToMenu();
}

// Fonction pour le menu "Paramètres"
void mFunc_settings(uint8_t param) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F("Paramètres"));
  display.display();
  delay(2000);
  LCDML.FUNC_goBackToMenu();
}