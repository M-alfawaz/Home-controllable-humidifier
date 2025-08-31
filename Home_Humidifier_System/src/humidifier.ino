/* Home Controllable Humidifier – Arduino Uno
   Sensors: DHT11 (temp/humidity), analog humidity (A5), water level (A4)
   Actuator: Relay (humidifier), LCD 16x2
   Behavior: If humidity below target & water available → run humidifier 30s, then recheck.
*/

#include <LiquidCrystal.h>
#include <SimpleDHT.h>

// ----- LCD pins: RS, E, D4, D5, D6, D7 (adjust if your wiring differs)
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// ----- DHT11
const int PIN_DHT11 = 2;
SimpleDHT11 dht11;

// ----- Analog sensors
const int PIN_WATER = A4;   // water level sensor (0–1023)
const int PIN_AHUM  = A5;   // analog humidity sensor (0–1023)

// ----- Relay (humidifier)
const int PIN_RELAY = 6;    // HIGH = ON (change if your relay is active-LOW)

// ----- Tuning
const int TARGET_HUMIDITY = 50;     // % target (adjust as needed)
const int WATER_OK_THRESH = 60;     // analog threshold for enough water (0–1023 scale)
const unsigned long RUN_MS = 30000; // 30 seconds run time

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_WATER, INPUT);

  // start OFF
  digitalWrite(PIN_RELAY, LOW);
  lcd.clear();
  lcd.print("Humidifier Ready");
  delay(700);
}

void loop() {
  // ---- Read DHT11
  byte t = 0, h = 0;
  byte raw[40] = {0};
  if (dht11.r
