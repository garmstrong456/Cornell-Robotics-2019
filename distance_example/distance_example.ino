#include <M5Stack.h>
#include "FastLED.h"
#include <NewPing.h>

#define Neopixel_PIN 1
#define NUM_LEDS 7
CRGB leds[NUM_LEDS];

#define TRIG_PIN 26
#define ECHO_PIN 13
#define MAX_DISTANCE 200
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  M5.begin();

  M5.Lcd.setTextColor(CYAN); M5.Lcd.setTextSize(2); M5.Lcd.setCursor(40,0);
  M5.Lcd.println("Ultrasonic Test");
  M5.Lcd.setTextColor(WHITE, BLACK);

  // Neopixel initialization
  FastLED.addLeds<WS2811, Neopixel_PIN, RGB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(10);
}

void loop() {
  delay(50);
  int distance = sonar.ping_cm();

  M5.Lcd.setCursor(0,50);
  M5.Lcd.printf("Distance = %3dcm", distance);

  int LEDs_lit = map(distance, 0, MAX_DISTANCE, 0, NUM_LEDS);
  FastLED.clear();
  for (int i=0;i<LEDs_lit;i++) {
    leds[i] = CRGB::Green;
  }
  FastLED.show();
}
