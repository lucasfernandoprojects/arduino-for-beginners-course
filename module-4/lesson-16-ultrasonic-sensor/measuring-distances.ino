#include <DFRobot_RGBLCD1602.h>

// LCD (use 0x6B if your module is V1.1)
DFRobot_RGBLCD1602 lcd(0x60, 16, 2);

// Ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 10;

long duration;
float distance;

const float MIN_DISTANCE = 5.0;    // cm
const float MAX_DISTANCE = 100.0;  // cm

void setup() {
  // Initialize LCD
  lcd.init();
  lcd.setColorWhite();
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Distance:");

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo time (timeout increased for safety)
  duration = pulseIn(echoPin, HIGH, 60000);

  lcd.setCursor(0, 1);
  lcd.print("                "); // Clear line
  lcd.setCursor(0, 1);

  // If no echo received
  if (duration == 0) {
    lcd.clear();
    lcd.print("No object found");
    delay(300);
    return;
  } else {
    // Convert to distance (cm)
    distance = duration * 0.034 / 2;

    // Check detection zone
    if (distance < MIN_DISTANCE || distance > MAX_DISTANCE) {
      lcd.clear();
      lcd.print("No object found");
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Distance:");
      lcd.setCursor(0, 1);
      lcd.print(distance, 1);
      lcd.print(" cm");
    }
  }

  delay(300);
}
