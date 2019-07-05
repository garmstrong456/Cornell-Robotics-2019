//Calibrated line sensor demo
//
//This sketch will demonstrates how to get calibrated readings from your line
//sensor. 
//
//The line sensor should be connected to pins 2, 5 and 15. This will involve
//jumping one of the pins from the line sensor header to pin 02 on the M5.
//
//First it will give you 10 seconds to move the line sensor back and
//forth accross the line. Make sure each sensor sees the dark and light surface.
//
//Once the calibration is done it will display the raw values, calibrated values
//and the overall position on the line.

#include <M5Stack.h>
#include "FastLED.h"
#include <QTRSensors.h>

//Line sensor declarations
QTRSensors qtr;
const uint8_t SensorCount = 3;
uint16_t sensorValues[SensorCount];

//LED declarations
#define Neopixel_PIN 1
#define NUM_LEDS 7
CRGB leds[NUM_LEDS];

void setup() {
  M5.begin();

  M5.Lcd.setTextColor(CYAN); M5.Lcd.setTextSize(2); M5.Lcd.setCursor(40,0);
  M5.Lcd.println("Calibrated Line Data");
  M5.Lcd.setTextColor(WHITE, BLACK);

  FastLED.addLeds<WS2811,Neopixel_PIN,GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  fill_solid(leds, NUM_LEDS, CRGB::Blue); //set LEDS to blue while calibrating
  FastLED.show();

  //Initialize the line sensor
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]) {2,5,15}, SensorCount);

  delay(500);
  M5.Lcd.setCursor(0,25);
  M5.Lcd.println("Calibrating...");

  // 2.5ms RC read timeout (default * 10 reads per calibrate() call
  // = ~25ms per calibrate() call.
  //Call calibrate() 400 times to make the calibration take about 10 seconds.
  for (int i=0; i<400; i++) {
    qtr.calibrate();
  }

  //print done and flash the LED green to indicate calibration is over
  M5.Lcd.println("done");
  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.show();
  delay(1000);

  M5.Lcd.clear();
}

void loop() {
  uint16_t position = qtr.readLineBlack(sensorValues);

  M5.Lcd.setCursor(0,10);
  M5.Lcd.printf("position = %4d", position);
  M5.Lcd.setCursor(0,50);
  M5.Lcd.println("calibrated values:");
  M5.Lcd.printf("%4d, %4d, %4d", sensorValues[0], sensorValues[1], sensorValues[2]);

  qtr.read(sensorValues);
  M5.Lcd.setCursor(0,90);
  M5.Lcd.println("raw values:"); 
  M5.Lcd.printf("%4d, %4d, %4d", sensorValues[0], sensorValues[1], sensorValues[2]);
  
  FastLED.clear();
  FastLED.show();  
}
