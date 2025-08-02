// Lesson 5 - Analog and Digital Pins (Arduino for Beginners)
// Fading in and out a RGB using only one communication wire

#include <Adafruit_NeoPixel.h>

#define PIN_LED 3     // Control pin (connect to DI of the RGB module)
#define NUM_LED 1     // Only 1 LED in this example

Adafruit_NeoPixel led = Adafruit_NeoPixel(NUM_LED, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup() {
  led.begin();          // Initialize the LED
  led.show();           // Turn off LED at start
  led.setBrightness(64); // Medium brightness (0-255)
}

void loop() {
  // Primary Colors (Red, Green, Blue)
  fadeInOut(255, 0, 0);     // Red
  fadeInOut(0, 255, 0);     // Green
  fadeInOut(0, 0, 255);     // Blue

  // Mixed Colors
  fadeInOut(255, 0, 255);   // Blue + Red (Purple)
  fadeInOut(0, 255, 255);   // Blue + Green (Cyan)
  fadeInOut(255, 255, 0);   // Red + Green (Yellow)
  fadeInOut(255, 255, 255); // Red + Green + Blue (White)
}

// Simple fade in/out function (hides complexity)
void fadeInOut(int red, int green, int blue) {
  // Fade IN (0 → full brightness)
  for (int brightness = 0; brightness <= 255; brightness++) {
    led.setPixelColor(0, red * brightness / 255, green * brightness / 255, blue * brightness / 255);
    led.show();
    delay(4); // ~2 sec fade (255 steps * 8ms ≈ 2000ms)
  }

  // Fade OUT (full brightness → 0)
  for (int brightness = 255; brightness >= 0; brightness--) {
    led.setPixelColor(0, red * brightness / 255, green * brightness / 255, blue * brightness / 255);
    led.show();
    delay(4); // ~2 sec fade
  }
}
