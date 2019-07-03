#include <M5Stack.h>
#include "FastLED.h"

#define Neopixel_PIN 1
#define NUM_LEDS 7
CRGB leds[NUM_LEDS];

void setup() {
  M5.begin();   //This line should be at the beginning of every program

  FastLED.addLeds<WS2811,Neopixel_PIN,RGB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.clear();
}

void loop() {
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(BLUE, BLACK);
  M5.Lcd.setCursor(0,0);
  M5.Lcd.print("Hello world!");

  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
  
  delay(500);

  M5.Lcd.setTextColor(GREEN, BLACK);
  M5.Lcd.setCursor(0,0);
  M5.Lcd.print("Hello world!");

  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();

  delay(500);

}
