#include <M5Stack.h>
#include "utility/MPU9250.h"
#include "FastLED.h"

#define Neopixel_PIN 1
#define NUM_LEDS 7
CRGB leds[NUM_LEDS];

MPU9250 IMU;
unsigned long lastPrintTime;

void setup() {
  M5.begin();   //always call this first
  Wire.begin();

  // Neopixel initialization
  FastLED.addLeds<WS2811,Neopixel_PIN,GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  //print the screen header
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(GREEN, BLACK);
  M5.Lcd.setCursor(40,0);
  M5.Lcd.print("Raw MPU data");
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(WHITE, BLACK);

  //intialize, test and calibrate the MPU
  IMU.MPU9250SelfTest(IMU.SelfTest);
  IMU.calibrateMPU9250(IMU.gyroBias, IMU.accelBias);
  IMU.initMPU9250();
  IMU.initAK8963(IMU.magCalibration);
}

void loop() {
  IMU.readAccelData(IMU.accelCount);
  IMU.readGyroData(IMU.gyroCount);
  IMU.readMagData(IMU.magCount);

  //update the display only 10 times per second
  if (millis() > lastPrintTime + 100) {
    lastPrintTime = millis();
    M5.Lcd.setCursor(0,20); M5.Lcd.print("     x       y       z ");
    M5.Lcd.setCursor(0,40); M5.Lcd.printf("acc %6d %6d %6d  mg", IMU.accelCount[0], IMU.accelCount[1], IMU.accelCount[2]);
    M5.Lcd.setCursor(0,60); M5.Lcd.printf("gyr %6d %6d %6d  mg", IMU.gyroCount[0], IMU.gyroCount[1], IMU.gyroCount[2]);
    M5.Lcd.setCursor(0,80); M5.Lcd.printf("mag %6d %6d %6d  mg", IMU.magCount[0], IMU.magCount[1], IMU.magCount[2]);
  }

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}
