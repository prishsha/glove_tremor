#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

// 🔴 Replace with YOUR IP
const char* server = "http://IP:5000/esp";

#define MOTOR_PIN 18

void setup() {
  Serial.begin(115200);

  pinMode(MOTOR_PIN, OUTPUT);

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

      // simple check
      if (payload.indexOf("\"motor\":1") > 0) {
        digitalWrite(MOTOR_PIN, HIGH);
      } else {
        digitalWrite(MOTOR_PIN, LOW);
      }
    }

    http.end();
  }

  delay(500);
}