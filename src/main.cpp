#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  pinMode(21, INPUT);
}

unsigned int i = 0;

void loop() {
  Serial.printf("Bonsoir: %d\n", i);
  i++;
  delay(1000);
}