#include <DHT.h>
#include <Adafruit_Sensor.h>

#define DHTPIN 4
#define DHTTYPE DHT11

#ifndef LED_BUILTIN
  #define LED_BUILTIN 2
#endif

const int statusLedPin = LED_BUILTIN;
const unsigned long ledInterval = 500;
const unsigned long sensorInterval = 5000;

unsigned long previousLedMillis = 0;
unsigned long previousSensorMillis = 0;
bool ledState = LOW;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  pinMode(statusLedPin, OUTPUT);
  digitalWrite(statusLedPin, ledState);

  dht.begin();

  Serial.println("ESP32 DHT11 project started");
  Serial.println("Temperature will print every 5 seconds");
  Serial.println("Status LED will blink every 500 ms");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousLedMillis >= ledInterval) {
    previousLedMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(statusLedPin, ledState);
  }

  if (currentMillis - previousSensorMillis >= sensorInterval) {
    previousSensorMillis = currentMillis;

    float temperature = dht.readTemperature();

    if (isnan(temperature)) {
      Serial.println("Failed to read from DHT11 sensor");
    } else {
      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.println(" C");
    }
  }
}
