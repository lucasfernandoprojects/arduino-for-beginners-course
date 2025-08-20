// Lesson 6 - Learn Arduino coding (Arduino for Beginners)
// A simple alarm system using an ultrasonic sensor, LEDs, and a digital buzzer

// Pin definitions
const int redLED = 2;
const int blueLED = 3;
const int buzzer = 4;
const int echoPin = 5;
const int trigPin = 6;

// Variables
long duration;
int distance;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
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
  // Read the echo response
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  // Check if object is closer than 10 cm
  if (distance <= 10 && distance > 0) {
    triggerAlarm();
  }
  delay(100); // Wait before next check
}

void triggerAlarm() {
  unsigned long startTime = millis();
  while (millis() - startTime < 10000) { // Alarm for 10 seconds
    digitalWrite(redLED, HIGH);
    digitalWrite(blueLED, LOW);
    digitalWrite(buzzer, HIGH);
    delay(250);
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, HIGH);
    delay(250);
  }
  // Turn everything off after alarm
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(buzzer, LOW);
}
