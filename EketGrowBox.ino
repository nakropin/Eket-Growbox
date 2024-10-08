// Eket Growbox Controller

#include <DHT.h>
#include <Wire.h>
#include <RTClib.h>

// Humidity sensor
const int humiditySensorPin = 7;
DHT dht(humiditySensorPin, DHT11);

// Relay for switching on lights
const int relayPin = 8;

// Mosfets for fans
const int circulationPin = 9;
const int exhaustPin = 10;
const int fanPin = 11;

// Bounds for Mosfets
const int airMax = 255;
const int airMin = 60;
const int circulationMin = 220;

// Real time clock
RTC_DS1307 rtc;

void setup() {
  Serial.begin(9600);

  if (!rtc.begin()) {
    Serial.println("RTC not found");
  }
  if (!rtc.isrunning()) {
    Serial.println("RTC doesn't work");
  } else {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    Serial.println("RTC works");
  }

  dht.begin();

  pinMode(relayPin, OUTPUT);
  pinMode(circulationPin, OUTPUT);
  pinMode(exhaustPin, OUTPUT);
  pinMode(fanPin, OUTPUT);

  // Initialize all outputs to LOW
  digitalWrite(relayPin, LOW);
  analogWrite(circulationPin, airMin);
  analogWrite(exhaustPin, airMin);
  digitalWrite(fanPin, LOW);

  // Set high PWM frequency for circulation pin
  setPwmFrequency(circulationPin, 1024);
  setPwmFrequency(exhaustPin, 1);
}

void loop() {
  DateTime now = rtc.now();
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Print current time and sensor readings
  printDateTime(now);
  printSensorReadings(humidity, temperature);

  // Control relay and fanPin based on time
  bool isLightOn = controlLightingAndFan(now);

  // Control humidity
  controlHumidity(humidity);

  delay(1000);
}

void printDateTime(DateTime now) {
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);
}

void printSensorReadings(float humidity, float temperature) {
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
  }
}

bool controlLightingAndFan(DateTime now) {
  int currentHour = now.hour();
  bool shouldBeOn = (currentHour >= 6 && currentHour < 24);

  digitalWrite(relayPin, shouldBeOn ? HIGH : LOW);
  digitalWrite(fanPin, shouldBeOn ? 150 : LOW);

  Serial.println(shouldBeOn);

  return shouldBeOn;
}

void controlHumidity(float humidity) {
  int exhaustPower, circulationPower;

  if (humidity > 70) {
    exhaustPower = airMax;
    circulationPower = map(humidity, 60, 100, circulationMin, 150);
  } else if (humidity > 60) {
    exhaustPower = map(humidity, 50, 60, circulationMin, airMax);
    circulationPower = circulationMin;
  } else if (humidity >= 40) {
    exhaustPower = airMin;
    circulationPower = circulationMin;
  } else {
    exhaustPower = airMin;
    circulationPower = circulationMin;
  }

  analogWrite(exhaustPin, exhaustPower);
  analogWrite(circulationPin, circulationPower);
}

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if (pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch (divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if (pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if (pin == 3 || pin == 11) {
    switch (divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}