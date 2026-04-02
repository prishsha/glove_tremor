#include <Arduino.h>

int pins[5] = {18, 19, 21, 22, 23};

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  // RANDOM PATTERN (like glove motors)
  for (int i = 0; i < 5; i++) {
    int state = random(0, 2);  // 0 or 1
    digitalWrite(pins[i], state);
  }

  delay(300);
}