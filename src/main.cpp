#include <Arduino.h>

#define MOTOR_PIN 18

float freq = 6.0;
float t = 0;

float threshold = 0.6;   // tremor detection threshold

void setup() {
  Serial.begin(115200);
  pinMode(MOTOR_PIN, OUTPUT);
}

void loop() {
  Serial.println("TEST OUTPUT");
  delay(1000);
}