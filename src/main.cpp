#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 1
#define LED_PIN     40
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  pinMode(21, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(36, OUTPUT);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);  //0-255
  leds[0] = CRGB::Yellow3; FastLED.show(); 
  

  //moteur 
  pinMode(33, OUTPUT); // nSLEEP
  pinMode(34, OUTPUT); // in 1
  pinMode(35, OUTPUT); // in 2
  pinMode(5, INPUT_PULLUP);

  digitalWrite(33, HIGH);
  digitalWrite(34, LOW);
  digitalWrite(35, HIGH);

  digitalWrite(36, HIGH);
  digitalWrite(2, HIGH);


  pinMode(0, INPUT);
}

unsigned int i = 0;

enum etats_t {
  ETAT_CLIGNOTAGE,
  ETAT_NON,
};

etats_t state = ETAT_NON;

unsigned debut_clignote = 0;

void loop() {
  i++;
  digitalWrite(21, i % 2);
  if (!digitalRead(0)) {
    Serial.println("prout");
  }
  switch (state) {
    case ETAT_CLIGNOTAGE:
     if (((millis() - debut_clignote) / 250) % 2) {
       leds[0] = CRGB::Black;
     } else {
      leds[0] = CRGB::Red;
     }
      FastLED.show();
      break;
    case ETAT_NON:
      leds[0] = CRGB::Green;
      FastLED.show();
      break;
  }

  if (state == ETAT_NON && !digitalRead(5)) {
    state = ETAT_CLIGNOTAGE;
    debut_clignote = millis();
  }
  else if (state == ETAT_CLIGNOTAGE && digitalRead(5) && millis() - debut_clignote > 5000) {
    state = ETAT_NON;
  }
  delay(100);
}