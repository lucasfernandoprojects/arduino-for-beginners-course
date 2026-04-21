const int ledPin = 2;  // LED connected to D2
char receivedChar;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // start OFF

  Serial.begin(115200);  // Bluno default baud rate
}

void loop() {
  if (Serial.available()) {
    receivedChar = Serial.read();  // read incoming byte

    // Debug (optional)
    Serial.print("Received: ");
    Serial.println(receivedChar);

    if (receivedChar == 'A') {
      digitalWrite(ledPin, HIGH);  // turn LED ON
    }
    else if (receivedChar == 'B') {
      digitalWrite(ledPin, LOW);   // turn LED OFF
    }
  }
}
