// Lesson #17 - Reading temperature with the LM35 sensor

#include <Wire.h>
#include <DFRobot_RGBLCD1602.h>

#define LM35_PIN A3
#define BUTTON_PIN 2

DFRobot_RGBLCD1602 lcd(0x60, 16, 2);

bool showCelsius = true;

// ---------- Button ----------
bool lastReading;
bool buttonState;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

// ---------- Startup lock ----------
unsigned long startTime;

// ---------- Averaging ----------
const int numSamples = 10;
int samples[numSamples];
int sampleIndex = 0;
long total = 0;
float smoothedTempC = 0;

unsigned long lastSampleTime = 0;
const unsigned long sampleInterval = 10;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  lcd.init();
  lcd.display();
  lcd.setColorWhite();
  lcd.clear();

  showCelsius = true;
  lastReading = digitalRead(BUTTON_PIN);
  buttonState = lastReading;
  startTime = millis();

  // Initialize sample buffer
  for (int i = 0; i < numSamples; i++) {
    samples[i] = analogRead(LM35_PIN);
    total += samples[i];
  }
}

void loop() {
  unsigned long now = millis();

  // ---------- Sample LM35 ----------
  if (now - lastSampleTime >= sampleInterval) {
    lastSampleTime = now;

    total -= samples[sampleIndex];
    samples[sampleIndex] = analogRead(LM35_PIN);
    total += samples[sampleIndex];

    sampleIndex = (sampleIndex + 1) % numSamples;

    float avgReading = total / (float)numSamples;
    float voltage = avgReading * (5.0 / 1023.0);
    smoothedTempC = voltage * 100.0;
  }

  float tempF = (smoothedTempC * 9.0 / 5.0) + 32.0;

  // ---------- Button (after startup) ----------
  if (now - startTime > 1000) {
    bool reading = digitalRead(BUTTON_PIN);

    if (reading != lastReading) {
      lastDebounceTime = now;
    }

    if ((now - lastDebounceTime) > debounceDelay) {
      if (reading != buttonState) {
        buttonState = reading;
        if (buttonState == LOW) {
          showCelsius = !showCelsius;
        }
      }
    }
    lastReading = reading;
  }

  // ---------- LCD Update ----------
  static unsigned long lastLCDUpdate = 0;
  if (now - lastLCDUpdate >= 500) {
    lastLCDUpdate = now;

    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");

    if (showCelsius) {
      lcd.print(smoothedTempC, 1);
      lcd.print((char)223);
      lcd.print("C");
    } else {
      lcd.print(tempF, 1);
      lcd.print((char)223);
      lcd.print("F");
    }

    Serial.print("Temp: ");
    Serial.print(smoothedTempC);
    Serial.print(" C | ");
    Serial.print(tempF);
    Serial.println(" F");
  }
}
