#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

// 🔴 Replace with YOUR IP
const char* server = "http://172.20.10.7:5000/esp";

// 🔥 5 LED PINS
int pins[5] = {18, 19, 21, 22, 23};

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 5; i++) {
    pinMode(pins[i], OUTPUT);
  }

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;
    http.begin(server);

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String payload = http.getString();

      Serial.println(payload);

      if (payload.indexOf("\"motor\":1") != -1) {

        // 🔥 RANDOM GLOVE PATTERN
        for (int i = 0; i < 5; i++) {
          digitalWrite(pins[i], random(0, 2));
        }

      } else {

        // ❌ NO TREMOR → ALL OFF
        for (int i = 0; i < 5; i++) {
          digitalWrite(pins[i], LOW);
        }

      }
    }

    http.end();
  }

  delay(200);  // faster response, smoother flicker
}