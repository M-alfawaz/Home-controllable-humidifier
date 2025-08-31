#include <LiquidCrystal.h>
#include <SimpleDHT.h>

// LCD pins: RS, E, D4, D5, D6, D7  (adjust if different)
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// DHT11
int pinDHT11 = 2;
SimpleDHT11 dht11;

// Analog sensors
int water = A4;   // water level sensor (analog)
int H = A5;       // analog humidity sensor

// Relay output
int relay = 6;

// Working vars
int val = 0;
int out = 0;
unsigned long H_in = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(relay, OUTPUT);
  pinMode(water, INPUT);

  // Optional: start with humidifier OFF
  digitalWrite(relay, LOW);
}

void loop() {
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};

  // Read DHT11; if read fails, skip this cycle
  if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
    // read error; try again next loop
    delay(200);
    return;
  }

  // Read analog sensors
  val = analogRead(water);
  H_in = analogRead(H);
  out = (int)((unsigned long)(H_in * 100) / 1024); // convert to %

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("temp=");
  lcd.print((int)temperature);
  lcd.print("C  ");

  lcd.setCursor(0, 1);
  lcd.print("hum=");
  lcd.print((int)humidity);
  lcd.print("%  out=");
  lcd.print((unsigned)out);

  // Control logic (as in report):
  // If water level high (val > 60) and humidity okay → relay OFF
  // Else if water low and humidity differs → relay ON for 30s (per report description)
  if ( ((val > 60) && (humidity == out)) || (humidity > out) ) {
    digitalWrite(relay, LOW); // OFF
  } else if ( (val < 60) && (humidity != out) ) {
    digitalWrite(relay, HIGH); // ON
    delay(30000);              // run for 30 seconds
    digitalWrite(relay, LOW);  // then OFF and re-measure next loop
  }

  delay(100);
}
