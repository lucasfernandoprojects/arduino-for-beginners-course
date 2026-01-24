// Lesson #15 - Simple infrared alarm system

// Pin definitions
const int IR_SENSOR_PIN = 2;   // Infrared sensor signal
const int RED_LED_PIN  = 3;   // Red LED
const int BLUE_LED_PIN = 4;   // Blue LED

void setup() {
  // Configure pins
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);

  // Make sure LEDs start OFF
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);
}

void loop() {
  // Read the infrared sensor
  int sensorState = digitalRead(IR_SENSOR_PIN);

  // Sensor is ACTIVE LOW
  if (sensorState == LOW) {
    // Object detected - trigger alarm
    triggerAlarm();
  }

  // Small delay to avoid noisy readings
  delay(50);
}

void triggerAlarm() {
  // Blink LEDs alternately for 4 seconds
  for (int i = 0; i < 10; i++) {   // 10 × 0.4 = 4s total
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, LOW);
    delay(200);

    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, HIGH);
    delay(200);
  }

  // Turn both LEDs OFF after alarm
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);
}
