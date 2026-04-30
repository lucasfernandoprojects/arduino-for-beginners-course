#include <SoftwareSerial.h>
#include <DHT.h>
#include <DFRobot_RGBLCD1602.h>

// ===== WIFI =====
char ssid[] = "WIFI_NAME";
char password[] = "WIFI_PASSWORD";
char apiKey[] = "THINGSPEAK_WRITER_API_KEY";

// ===== WIFI MODULE =====
SoftwareSerial wifi(4, 5); // RX, TX

// ===== DHT11 =====
#define DHTPIN 3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ===== LCD =====
DFRobot_RGBLCD1602 lcd(0x60, 16, 2);

// ===== TIMER =====
unsigned long lastSend = 0;
const unsigned long interval = 30000; // 30 seconds

void setup() {
  Serial.begin(115200);
  wifi.begin(9600);

  dht.begin();

  // LCD init
  lcd.init();
  lcd.setColorWhite();
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Starting...");

  Serial.println("Starting...");

  // Ping
  wifi.print("|1|1|\r");
  waitResponse();

  // Connect WiFi
  lcd.clear();
  lcd.print("Connecting WiFi");

  Serial.println("Connecting WiFi...");
  wifi.print("|2|1|");
  wifi.print(ssid);
  wifi.print(",");
  wifi.print(password);
  wifi.print("|\r");

  waitResponse();

  lcd.clear();
  lcd.print("WiFi Connected");
  delay(1500);
}

void loop() {

  readSerial();

  // Send every 30 seconds
  if (millis() - lastSend >= interval) {
    lastSend = millis();
    sendData();
  }
}

// ===== SEND DATA =====
void sendData() {
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("DHT read failed ❌");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error");
    return;
  }

  // ===== SERIAL =====
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C | Hum: ");
  Serial.println(hum);

  // ===== LCD =====
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp, 1);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Hum : ");
  lcd.print(hum, 0);
  lcd.print(" %");

  // ===== THINGSPEAK =====
  String url = "api.thingspeak.com/update?api_key=";
  url += apiKey;
  url += "&field1=";
  url += String(temp, 1);
  url += "&field2=";
  url += String(hum, 0);

  Serial.println("Sending to ThingSpeak...");

  wifi.print("|3|1|http://");
  wifi.print(url);
  wifi.print("|\r");

  waitResponse();
}

// ===== HELPERS =====
void waitResponse() {
  unsigned long t = millis();
  while (millis() - t < 5000) {
    readSerial();
  }
}

void readSerial() {
  while (wifi.available()) {
    char c = wifi.read();
    Serial.print(c);
  }
}
