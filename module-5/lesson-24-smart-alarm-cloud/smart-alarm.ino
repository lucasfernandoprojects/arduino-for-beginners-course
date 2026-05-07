#include <SoftwareSerial.h>
#include <DFRobot_RGBLCD1602.h>

// ===== WIFI =====
char ssid[] = "WI-FI NAME";
char password[] = "WI-FI PASSWORD";
char apiKey[] = "WRITE API KEY";

// ===== WIFI MODULE =====
SoftwareSerial wifi(4, 5); // RX, TX
String wifiBuffer = "";

// ===== LCD =====
DFRobot_RGBLCD1602 lcd(0x60, 16, 2);

// ===== ULTRASONIC =====
#define TRIG_PIN 8
#define ECHO_PIN 9

// ===== LEDS =====
#define RED_LED 2
#define BLUE_LED 3

// ===== STATE =====
bool alarmActive = false;
bool wifiConnected = false;

// ===== TIMER =====
unsigned long lastSend = 0;
const unsigned long interval = 60000; // 60 seconds

// =====================================================
// SETUP
// =====================================================
void setup() {
  Serial.begin(115200);
  wifi.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  lcd.init();
  lcd.setColorWhite();
  lcd.clear();

  lcd.print("Starting...");
  Serial.println("Starting...");

  // ===== PING =====
  wifi.print("|1|1|\r");
  waitResponse();

  // ===== CONNECT WIFI =====
  lcd.clear();
  lcd.print("Connecting WiFi");

  Serial.println("Connecting WiFi...");

  wifi.print("|2|1|");
  wifi.print(ssid);
  wifi.print(",");
  wifi.print(password);
  wifi.print("|\r");

  // DO NOT assume connection here
}

// =====================================================
// LOOP
// =====================================================
void loop() {

  readSerial(); // Always listen to module

  // Wait until WiFi is REALLY connected
  if (!wifiConnected) {
    return;
  }

  long distance = readDistance();

  Serial.print("Distance: ");
  Serial.println(distance);

  // ===== TRIGGER =====
  if (distance > 0 && distance <= 10 && !alarmActive) {
    triggerAlarm();
    lastSend = millis(); // reset timer
  }

  // ===== SEND 0 EVERY 60s =====
  if (!alarmActive && millis() - lastSend >= interval) {
    lastSend = millis();
    sendZero();
  }

  // ===== RESET WHEN OBJECT LEAVES =====
  if (distance > 20 && alarmActive) {
    alarmActive = false;

    lcd.clear();
    lcd.print("Monitoring...");
  }

  delay(300);
}

// =====================================================
// READ DISTANCE
// =====================================================
long readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2;

  return distance;
}

// =====================================================
// TRIGGER ALARM
// =====================================================
void triggerAlarm() {
  alarmActive = true;

  Serial.println("ALARM TRIGGERED!");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alarm triggered");

  sendOne();

  unsigned long startTime = millis();

  while (millis() - startTime < 10000) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);
    delay(300);

    digitalWrite(RED_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);
    delay(300);
  }

  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}

// =====================================================
// SEND 1
// =====================================================
void sendOne() {
  Serial.println("Sending 1 to ThingSpeak...");

  String url = "api.thingspeak.com/update?api_key=";
  url += apiKey;
  url += "&field1=1";

  wifi.print("|3|1|http://");
  wifi.print(url);
  wifi.print("|\r");

  waitResponse();
}

// =====================================================
// SEND 0
// =====================================================
void sendZero() {
  Serial.println("Sending 0 to ThingSpeak...");

  String url = "api.thingspeak.com/update?api_key=";
  url += apiKey;
  url += "&field1=0";

  wifi.print("|3|1|http://");
  wifi.print(url);
  wifi.print("|\r");

  waitResponse();
}

// =====================================================
// READ SERIAL + DETECT WIFI CONNECTION
// =====================================================
void readSerial() {
  while (wifi.available()) {
    char c = wifi.read();
    Serial.print(c);

    wifiBuffer += c;

    // Detect: |2|3|IP|
    if (!wifiConnected && wifiBuffer.indexOf("|2|3|") != -1) {

      wifiConnected = true;

      Serial.println("\nWiFi CONNECTED!");

      lcd.clear();
      lcd.print("WiFi Connected");
      delay(1500);

      lcd.clear();
      lcd.print("Monitoring...");
    }

    // Prevent overflow
    if (wifiBuffer.length() > 120) {
      wifiBuffer = "";
    }
  }
}

// =====================================================
// WAIT RESPONSE
// =====================================================
void waitResponse() {
  unsigned long t = millis();
  while (millis() - t < 5000) {
    readSerial();
  }
}
