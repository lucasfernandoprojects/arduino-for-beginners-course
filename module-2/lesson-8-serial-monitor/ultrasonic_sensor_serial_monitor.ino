// Lesson 8 - Serial Monitor (Arduino for Beginners)
// HC-SR04 Ultrasonic Sensor Pins
const int trigPin = 2;
const int echoPin = 3;

void setup() {
  // Initialize the serial monitor
  Serial.begin(9600);

  // Set up the pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long duration;
  float distanceCm;

  // Clear the trigPin by setting it LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Trigger the sensor by setting the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, and calculate duration of the echo pulse
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters (speed of sound in the air is 343m/s)
  distanceCm = duration * 0.0343 / 2;

  // Print the result to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  // Small delay before the next measurement (to avoid errors)
  delay(500);
}
