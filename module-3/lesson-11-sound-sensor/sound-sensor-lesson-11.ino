// Lesson 11 - Arduino for Beginners
// Use an analog sound sensor
// to turn on or off a LED

const int ledPin = 2;
const int buttonPin = 3;
const int soundPin = A5;

// Variables
bool ledState = false;                 // LED state (OFF at start)
bool lastButtonState = HIGH;           // Because of INPUT_PULLUP (HIGH = not pressed, LOW = pressed)
unsigned long lastClapTime = 0;
const int clapThreshold = 300;         // Adjust this based on your sound sensor
const unsigned long debounceDelay = 200; // ms - avoid multiple triggers for one clap

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  // Force LED OFF at startup
  ledState = false;
  digitalWrite(ledPin, LOW);

  // Sync lastButtonState with real button state to avoid false toggle at startup
  lastButtonState = digitalRead(buttonPin);

  Serial.begin(9600);
}

void loop() {
  // --- BUTTON CONTROL ---
  int buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && lastButtonState == HIGH) {
    // Button was pressed
    toggleLED();
  }
  lastButtonState = buttonState;

  // --- SOUND SENSOR (CLAP CONTROL) ---
  int soundValue = analogRead(soundPin);
  if (soundValue > clapThreshold) {
    unsigned long currentTime = millis();
    if (currentTime - lastClapTime > debounceDelay) {
      toggleLED();
      lastClapTime = currentTime;
    }
  }

  // Debugging - monitor sensor values
  Serial.println(soundValue);
}

// Function to toggle LED state
void toggleLED() {
  ledState = !ledState;
  digitalWrite(ledPin, ledState ? HIGH : LOW);
  Serial.print("LED is now ");
  Serial.println(ledState ? "ON" : "OFF");
}
