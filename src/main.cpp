#include <Arduino.h>
#include <FastLED.h>
#include <Button2.h>

#define NUM_LEDS 1
#define LED_PIN     40
CRGB leds[NUM_LEDS];

enum etats_t {
  ETAT_ROUGE,
  ETAT_VERT,
};

etats_t state = ETAT_VERT;

Button2 btn;

unsigned long debut_clignote = 0;
unsigned long debut_bip = 0;

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
  // pinMode(5, INPUT_PULLUP);

  digitalWrite(33, HIGH);
  digitalWrite(34, LOW);
  digitalWrite(35, HIGH);

  digitalWrite(36, HIGH);
  digitalWrite(2, HIGH);

  pinMode(0, INPUT);
  btn.begin(5);
  btn.setClickHandler([](Button2& b){
    state = ETAT_ROUGE;
    debut_clignote = millis();
  });
  btn.setDoubleClickHandler([](Button2& b){
    ledcAttach(39, 4000, 13);
    ledcWriteNote(39, NOTE_D, 4);
    debut_bip = millis();
  });
}

unsigned int i = 0;

void loop() {
  i++;
  digitalWrite(21, i % 2);
  if (!digitalRead(0)) {
    Serial.println("prout");
  }

  switch (state) {
    case ETAT_ROUGE:
      leds[0] = CRGB::Red;
      FastLED.show();
      break;
    case ETAT_VERT:
      leds[0] = CRGB::Green;
      FastLED.show();
      break;
  }

  if (state == ETAT_ROUGE && millis() - debut_clignote > 5000) {
    state = ETAT_VERT;
  }
  if (millis() - debut_bip > 1000 ) {
    ledcWrite(39, 0);
  }
  btn.loop();
}