#include <M5Stack.h>
#include "FastLED.h"
#include <QTRSensors.h>

#define Neopixel_PIN 1
#define NUM_LEDS 7
CRGB leds[NUM_LEDS];

QTRSensors qtr;
const uint8_t SensorCount = 3;
uint16_t sensorValues[SensorCount];

void setup() {
  M5.begin();

  M5.Lcd.setTextColor(CYAN); M5.Lcd.setTextSize(2); M5.Lcd.setCursor(40,0);
  M5.Lcd.println("Raw Line Sensor Data");
  M5.Lcd.setTextColor(WHITE, BLACK); M5.Lcd.setTextSize(1);

  FastLED.addLeds<WS2811,Neopixel_PIN,GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.show();
  
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){2, 5, 15}, SensorCount);
  delay(500);
}

void loop() {
  qtr.read(sensorValues);

  M5.Lcd.setCursor(0,25);
  M5.Lcd.println("  1    2    3");
  M5.Lcd.printf( "%4d %4d %4d", sensorValues[0], sensorValues[1], sensorValues[2]);

  FastLED.clear();
  FastLED.show();

  delay(250);
}
