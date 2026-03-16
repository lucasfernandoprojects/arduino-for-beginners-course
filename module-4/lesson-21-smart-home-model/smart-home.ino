// Lesson #20 - Arduino for Beginners series
// Smart home model from cardboard

#include <Wire.h>
#include <DFRobot_RGBLCD1602.h>
#include <DHT.h>
#include <Servo.h>

#define SERVO_PIN 2
#define DHTPIN 3
#define DHTTYPE DHT11
#define BUTTON_PIN 4
#define BUZZER_PIN 5
#define BLUE_LED 6
#define RED_LED 7
#define IR_SENSOR 8
#define POT_PIN A3

DFRobot_RGBLCD1602 lcd(0x60,16,2);
DHT dht(DHTPIN,DHTTYPE);
Servo myServo;

/* ---------- temperature mode ---------- */
bool showCelsius = true;

/* ---------- button debounce ---------- */
bool lastButtonReading;
bool buttonState;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

/* ---------- alarm ---------- */
bool alarmActive = false;
unsigned long alarmStart = 0;
const unsigned long alarmDuration = 10000;

/* ---------- LED blink ---------- */
bool ledState = false;
unsigned long lastBlink = 0;
const unsigned long blinkInterval = 300;

/* ---------- DHT averaging ---------- */
float tempSamples[10];
float humSamples[10];
int sampleIndex = 0;
bool samplesReady = false;

float avgTemp = 0;
float avgHum = 0;

unsigned long lastDHTRead = 0;
const unsigned long dhtInterval = 1000;

/* ---------- LCD ---------- */
unsigned long lastLCD = 0;
const unsigned long lcdInterval = 500;

/* ---------- startup protection ---------- */
unsigned long systemStart;

void setup()
{
  Serial.begin(9600);

  pinMode(BUTTON_PIN,INPUT_PULLUP);
  pinMode(BUZZER_PIN,OUTPUT);
  pinMode(BLUE_LED,OUTPUT);
  pinMode(RED_LED,OUTPUT);
  pinMode(IR_SENSOR,INPUT);

  digitalWrite(BUZZER_PIN,LOW);
  digitalWrite(BLUE_LED,LOW);
  digitalWrite(RED_LED,LOW);

  myServo.attach(SERVO_PIN);
  myServo.write(0);  // initialize servo position

  lcd.init();
  lcd.display();
  lcd.setColorWhite();
  lcd.clear();

  dht.begin();

  /* initialize button states to prevent false toggle */
  lastButtonReading = digitalRead(BUTTON_PIN);
  buttonState = lastButtonReading;
  showCelsius = true;

  lcd.setCursor(0,0);
  lcd.print("Smart Home");
  delay(2000);
  lcd.clear();

  systemStart = millis();
}

void loop()
{
  unsigned long now = millis();

  /* -------- servo control -------- */
  int potValue = analogRead(POT_PIN);
  int angle = map(potValue,0,1023,0,90);
  myServo.write(angle);

  /* -------- button toggle -------- */
  if(now - systemStart > 2000)   // ignore button during startup
  {
    bool reading = digitalRead(BUTTON_PIN);

    if(reading != lastButtonReading)
        lastDebounceTime = now;

    if((now-lastDebounceTime) > debounceDelay)
    {
        if(reading != buttonState)
        {
            buttonState = reading;

            if(buttonState == LOW)
                showCelsius = !showCelsius;
        }
    }

    lastButtonReading = reading;
  }

  /* -------- DHT sampling -------- */
  if(now-lastDHTRead >= dhtInterval)
  {
      lastDHTRead = now;

      float t = dht.readTemperature();
      float h = dht.readHumidity();

      if(!isnan(t) && !isnan(h))
      {
          tempSamples[sampleIndex] = t;
          humSamples[sampleIndex] = h;

          sampleIndex++;

          if(sampleIndex >= 10)
          {
              sampleIndex = 0;
              samplesReady = true;

              float tSum=0;
              float hSum=0;

              for(int i=0;i<10;i++)
              {
                  tSum += tempSamples[i];
                  hSum += humSamples[i];
              }

              avgTemp = tSum/10.0;
              avgHum  = hSum/10.0;

              Serial.print("Temp avg: ");
              Serial.print(avgTemp);
              Serial.print("C  Hum avg: ");
              Serial.println(avgHum);
          }
      }
  }

  /* -------- IR monitoring -------- */
  if(now-systemStart > 2000)   // ignore sensor during startup
  {
      int sensorState = digitalRead(IR_SENSOR);

      if(!alarmActive && sensorState == LOW)
      {
          alarmActive = true;
          alarmStart = now;
          Serial.println("Alarm triggered");
      }
  }

  /* -------- alarm behaviour -------- */
  if(alarmActive)
  {
      digitalWrite(BUZZER_PIN,HIGH);

      if(now-lastBlink >= blinkInterval)
      {
          lastBlink = now;
          ledState = !ledState;

          digitalWrite(RED_LED,ledState);
          digitalWrite(BLUE_LED,!ledState);
      }

      if(now-alarmStart >= alarmDuration)
      {
          alarmActive = false;

          digitalWrite(BUZZER_PIN,LOW);
          digitalWrite(RED_LED,LOW);
          digitalWrite(BLUE_LED,LOW);
      }
  }

  /* -------- LCD display -------- */
  if(now-lastLCD >= lcdInterval)
  {
      lastLCD = now;

      lcd.clear();

      if(alarmActive)
      {
          lcd.setCursor(0,0);
          lcd.print("Alarm Triggered");
          lcd.setCursor(0,1);
          lcd.print("Security Alert");
      }
      else if(samplesReady)
      {
          lcd.setCursor(0,0);

          if(showCelsius)
          {
              lcd.print("T:");
              lcd.print(avgTemp,1);
              lcd.print((char)223);
              lcd.print("C");
          }
          else
          {
              float tempF = avgTemp*9.0/5.0 + 32;
              lcd.print("T:");
              lcd.print(tempF,1);
              lcd.print((char)223);
              lcd.print("F");
          }

          lcd.setCursor(0,1);
          lcd.print("H:");
          lcd.print(avgHum,0);
          lcd.print("%");
      }
  }
}
