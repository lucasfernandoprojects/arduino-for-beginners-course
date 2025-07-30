// Lesson 8 - Serial Monitor (Arduino for Beginners)
// Control LEDs from Serial Monitor
// Valid commands:
// LED RED ON - Turn on the red LED
// LED BLUE ON - Turn on the blue LED
// LED RED OFF - Turn off the red LED
// LED BLUE OFF - Turn off the blue LED
// LED RED VALUE FROM 0 TO 255
// LED BLUE VALUE FROM 0 TO 255
// The last two commands set up the brightness of the red LED and blue LED.
// 0 means no brightness and 255 means full brightness.
// Any integer from 0 to 255 is valid.

const int redLedPin = 5;   // PWM pin
const int blueLedPin = 6;  // PWM pin

void setup() {
  pinMode(redLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter command (e.g., LED RED ON):");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim(); // Clean up input

    // Parse command
    int firstSpace = input.indexOf(' ');
    int secondSpace = input.indexOf(' ', firstSpace + 1);

    if (firstSpace > 0 && secondSpace > firstSpace) {
      String command = input.substring(0, firstSpace);
      String color = input.substring(firstSpace + 1, secondSpace);
      String value = input.substring(secondSpace + 1);

      command.toUpperCase();
      color.toUpperCase();
      value.toUpperCase();

      if (command == "LED" && (color == "RED" || color == "BLUE")) {
        int ledPin = (color == "RED") ? redLedPin : blueLedPin;

        if (value == "ON") {
          analogWrite(ledPin, 255); // Full brightness
          Serial.println("The command \"" + input + "\" is valid. System updated successfully.");
        } else if (value == "OFF") {
          analogWrite(ledPin, 0); // Off
          Serial.println("The command \"" + input + "\" is valid. System updated successfully.");
        } else {
          int brightness = value.toInt();
          if (String(brightness) == value && brightness >= 0 && brightness <= 255) {
            analogWrite(ledPin, brightness);
            Serial.println("The command \"" + input + "\" is valid. System updated successfully.");
          } else {
            Serial.println("The command \"" + input + "\" is invalid. Try again.");
          }
        }
      } else {
        Serial.println("The command \"" + input + "\" is invalid. Try again.");
      }
    } else {
      Serial.println("The command \"" + input + "\" is invalid. Try again.");
    }
  }
}
