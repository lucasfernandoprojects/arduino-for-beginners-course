// Lesson 9 - Learn Arduino coding (Arduino for Beginners)
// A simple system that uses a potentiometer (rotation sensor)
// to change the colors of a RGB LED

#include <Adafruit_NeoPixel.h>

// RGB LED on port 2
#define RGB_PIN 2
#define NUMPIXELS 1

// Potentiometer on pin A5
#define POT_PIN A5

// Create NeoPixel object
Adafruit_NeoPixel pixels(NUMPIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();       // Initialize NeoPixel
  pixels.clear();       // Make sure LED starts off
  pixels.show();
}

void loop() {
  int potValue = analogRead(POT_PIN);  // Read potentiometer (0–1023)

  // Small threshold to detect "fully left"
  if (potValue < 50) {
    // Turn LED off
    pixels.clear();
    pixels.show();
    return; // Exit loop early
  }

  // Map potentiometer range (50–1023) into 3 sections
  int section = map(potValue, 50, 1023, 0, 3);

  if (section == 0) {
    setColor(255, 0, 0);   // RED
  } else if (section == 1) {
    setColor(0, 255, 0);   // GREEN
  } else {
    setColor(0, 0, 255);   // BLUE
  }
}

// Helper function to set LED color
void setColor(int r, int g, int b) {
  pixels.setPixelColor(0, pixels.Color(r, g, b));
  pixels.show();
}
