#include <Arduino.h>

void setup() {
  pinMode(21, OUTPUT);
}

bool a = false;

void loop() {
  a = !a;
  digitalWrite(21, a);
  delay(499); // 0.5s
}