// Lesson 14 - Arduino for Beginners
// Use a LCD module
// to show messages (sliding effect)

#include <DFRobot_RGBLCD1602.h>

DFRobot_RGBLCD1602 lcd(0x60, 16, 2);

String message =
  "Like, subscribe and share this lesson with a friend who is trying to learn Arduino    ";

int position = 0;

void setup() {
  lcd.init();
  lcd.setColorWhite();
  lcd.clear();
}

void loop() {
  lcd.setCursor(0, 0);

  // Wrap substring manually for infinite scrolling
  String visibleText = "";

  for (int i = 0; i < 16; i++) {
    int index = (position + i) % message.length();
    visibleText += message[index];
  }

  lcd.print(visibleText);

  position = (position + 1) % message.length();

  delay(300); // Scroll speed
}
