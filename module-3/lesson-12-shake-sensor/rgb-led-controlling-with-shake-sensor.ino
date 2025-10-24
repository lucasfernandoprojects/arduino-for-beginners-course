// Lesson 12 - Arduino for Beginners
// Use a tilt sensor (shake sensor)
// to change the colors of a RGB LED

#include <Adafruit_NeoPixel.h>

// Define pins
#define LED_PIN 2
#define SHAKE_SENSOR_PIN 3
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, LED_PIN, NEO_GRB + NEO_KHZ800);

// Variables
int option = 0;
int lastShakeState = HIGH;
int currentShakeState;

void setup() {
  pinMode(SHAKE_SENSOR_PIN, INPUT_PULLUP);
  pixel.begin();
  pixel.show();
  updateLED();
}

void loop() {
  // Read the current state of the shake sensor
  currentShakeState = digitalRead(SHAKE_SENSOR_PIN);
  // Check if the sensor changed from HIGH to LOW (shake detected)
  if (lastShakeState == HIGH && currentShakeState == LOW) {
    // Increment option, wrap around from 7 to 0
    option = (option + 1) % 8;
    updateLED();
    delay(50);
  }
  
  // Save the current state for next comparison
  lastShakeState = currentShakeState;
}

void updateLED() {
  // Set LED color based on option value
  switch(option) {
    case 0: // OFF
      pixel.setPixelColor(0, pixel.Color(0, 0, 0));
      break;
    case 1: // RED
      pixel.setPixelColor(0, pixel.Color(255, 0, 0));
      break;
    case 2: // GREEN
      pixel.setPixelColor(0, pixel.Color(0, 255, 0));
      break;
    case 3: // BLUE
      pixel.setPixelColor(0, pixel.Color(0, 0, 255));
      break;
    case 4: // RED + GREEN = YELLOW
      pixel.setPixelColor(0, pixel.Color(255, 255, 0));
      break;
    case 5: // RED + BLUE = MAGENTA
      pixel.setPixelColor(0, pixel.Color(255, 0, 255));
      break;
    case 6: // GREEN + BLUE = CYAN
      pixel.setPixelColor(0, pixel.Color(0, 255, 255));
      break;
    case 7: // RED + GREEN + BLUE = WHITE
      pixel.setPixelColor(0, pixel.Color(255, 255, 255));
      break;
  }
  
  pixel.show();
}
