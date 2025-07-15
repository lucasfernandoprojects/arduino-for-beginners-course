void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  delay(250);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);

  digitalWrite(4, HIGH);
  digitalWrite(7, HIGH);
  delay(250);
  digitalWrite(4, LOW);
  digitalWrite(7, LOW);

  digitalWrite(3, HIGH);
  digitalWrite(8, HIGH);
  delay(250);
  digitalWrite(3, LOW);
  digitalWrite(8, LOW);

  digitalWrite(2, HIGH);
  digitalWrite(9, HIGH);
  delay(250);
  digitalWrite(2, LOW);
  digitalWrite(9, LOW);

  digitalWrite(3, HIGH);
  digitalWrite(8, HIGH);
  delay(250);
  digitalWrite(3, LOW);
  digitalWrite(8, LOW);

  digitalWrite(4, HIGH);
  digitalWrite(7, HIGH);
  delay(250);
  digitalWrite(4, LOW);
  digitalWrite(7, LOW);

  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  delay(250);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}
