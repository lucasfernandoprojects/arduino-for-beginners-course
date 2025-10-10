// Lesson 10 - Arduino for Beginners
// Use a light sensor (photoresistor)
// to turn on or off a LED

int ledPin = 2;    
int sensorPin = A5;
int sensorValue = 0;
int threshold = 500;   // Adjust this value based on your lighting conditions

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  Serial.begin(9600); // For debugging (optional)
}

void loop() {
  // Read the photoresistor value
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue); // Check values in Serial Monitor

  // If it’s dark, turn ON the LED, otherwise turn it OFF
  if (sensorValue < threshold) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(100); // Small delay to stabilize readings
}
