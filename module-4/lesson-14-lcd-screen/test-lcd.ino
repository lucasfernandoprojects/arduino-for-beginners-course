// Lesson 14 - Arduino for Beginners
// Use a LCD module
// to show messages

#include <DFRobot_RGBLCD1602.h>

DFRobot_RGBLCD1602 lcd(0x60, 16, 2);  // Use 0x6B if your module is V1.1

void setup() {
  lcd.init();                 // Initialize LCD
  lcd.display();              // Turn display on
  lcd.setColorWhite();        // White backlight

  lcd.clear();                // Clear screen
  lcd.setCursor(0, 0);        // First column, first row
  lcd.print("Lesson #14 -");  // Print message
  lcd.setCursor(0, 1);        // First column, second row
  lcd.print("LCD module");
}

void loop() {
}
