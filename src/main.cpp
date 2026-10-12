#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  pinMode(21, OUTPUT);
  pinMode(36, OUTPUT);
  digitalWrite(36, HIGH);
  pinMode(0, INPUT);
}

unsigned int i = 0;

void loop() {
  Serial.printf("Bonsoir: %d\n", i);
  i++;
  digitalWrite(21, i % 2);
  if (!digitalRead(0)) {
    Serial.println("prout");
  }
  delay(1000);
}