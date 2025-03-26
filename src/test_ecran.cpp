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

// Variables pour le calendrier
int selectedYear = 2025;
int selectedMonth = 1;
int selectedDay = 1;

// Nombre de jours dans chaque mois
const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Noms des mois
const char *monthNames[] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

// Fonction pour vérifier si une année est bissextile
bool isLeapYear(int year) {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Définition du menu avec LCDMenuLib2
LCDMenuLib2_menu LCDML_0 (255, 0, 0, NULL, NULL); // Root menu
LCDMenuLib2_menu LCDML_0_1 (0, 1, 0, mFunc_calendrier, NULL); // Calendrier
LCDMenuLib2_menu LCDML_0_2 (0, 2, 0, mFunc_alarm, NULL);      // Alarmes
LCDMenuLib2_menu LCDML_0_3 (0, 3, 0, mFunc_settings, NULL);   // Paramètres

// Initialisation de l'objet menu
LCDMenuLib2 LCDML(LCDML_0, 3, 1, NULL, NULL, NULL);

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
  LCDML.add(LCDML_0_1);
  LCDML.add(LCDML_0_2);
  LCDML.add(LCDML_0_3);
}

// Fonction pour afficher le menu
void displayMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println(F("Menu Principal:"));

  // Afficher les options du menu
  LCDML.display();
  display.display();
}

// Fonction pour gérer les boutons
void handleButtons() {
  if (digitalRead(BUTTON_UP_PIN) == LOW) {
    LCDML.INPUT_up();
    delay(200);
  }
  if (digitalRead(BUTTON_DOWN_PIN) == LOW) {
    LCDML.INPUT_down();
    delay(200);
  }
  if (digitalRead(BUTTON_SELECT_PIN) == LOW) {
    LCDML.INPUT_enter();
    delay(200);
  }
}

// Boucle principale
void loop() {
  handleButtons();
  displayMenu();
  LCDML.loop();
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