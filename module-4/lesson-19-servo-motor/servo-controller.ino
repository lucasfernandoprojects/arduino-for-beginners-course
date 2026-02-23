// Lesson #19 - Servo Control with Potentiometer + I2C LCD

#include <Wire.h>
#include <DFRobot_RGBLCD1602.h>
#include <Servo.h>

#define SERVO_PIN 2
#define POT_PIN A3

DFRobot_RGBLCD1602 lcd(0x60, 16, 2);
Servo myServo;

void setup() {
  myServo.attach(SERVO_PIN);

  lcd.init();
  lcd.display();
  lcd.setColorWhite();
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Servo Controller");
}

void loop() {
  // Read potentiometer (0–1023)
  int potValue = analogRead(POT_PIN);

  // Convert to servo angle (0–180)
  int angle = map(potValue, 0, 1023, 0, 180);

  // Move servo
  myServo.write(angle);

  // Display angle on LCD
  lcd.setCursor(0, 1);
  lcd.print("Angle: ");
  lcd.print(angle);
  lcd.print((char)223); // degree symbol
  lcd.print("   ");     // clear leftover digits

  delay(100);
}
