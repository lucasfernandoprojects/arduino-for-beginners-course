// Lesson #20 - Small weather station

#include <Wire.h>
#include <DFRobot_RGBLCD1602.h>
#include <DHT.h> // DHT sensor library from Adafruit

#define DHTPIN 2
#define DHTTYPE DHT11

DFRobot_RGBLCD1602 lcd(0x60, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastReadTime = 0;
const unsigned long readInterval = 5000; // 5 seconds

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.display();
  lcd.setColorWhite();
  lcd.clear();

  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print("DHT11 Sensor");
}

void loop() {
  unsigned long now = millis();

  if (now - lastReadTime >= readInterval) {
    lastReadTime = now;

    float humidity = dht.readHumidity();
    float tempC = dht.readTemperature();
    float tempF = dht.readTemperature(true);

    // Check for read failure
    if (isnan(humidity) || isnan(tempC)) {
      Serial.println("Failed to read from DHT11");

      lcd.setCursor(0, 1);
      lcd.print("Sensor Error   ");
      return;
    }

    // ----- Serial Monitor -----
    Serial.print("Temp: ");
    Serial.print(tempC);
    Serial.print(" C | ");
    Serial.print(tempF);
    Serial.print(" F | Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    // ----- LCD Display -----
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(tempC, 1);
    lcd.print((char)223);
    lcd.print("C      ");

    lcd.setCursor(0, 1);
    lcd.print("H:");
    lcd.print(humidity, 0);
    lcd.print("%       ");
  }
}
