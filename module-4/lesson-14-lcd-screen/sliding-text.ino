// Lesson 14 - Arduino for Beginners
// Use a LCD module
// to show messages (sliding effect)

#include <DFRobot_RGBLCD1602.h>

DFRobot_RGBLCD1602 lcd(0x60, 16, 2);  // Use 0x6B if needed

// Message to scroll
String message = "Like, subscribe and share this lesson with a friend who is trying to learn Arduino   ";

int position = 0;

void setup() {
  lcd.init();
  lcd.setColorWhite();
  lcd.clear();
}

void loop() {
  lcd.setCursor(0, 0);

  // Extract 16 characters starting from 'position'
  String visibleText = message.substring(position, position + 16);
  lcd.print(visibleText);

  position++;

  // Restart when we reach the end
  if (position > message.length() - 16) {
    position = 0;
  }

  delay(300); // Controls scroll speed
}
