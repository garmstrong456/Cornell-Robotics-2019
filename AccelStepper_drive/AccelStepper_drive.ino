// For TEC Bot 7.0 with Greg Armstrong's AccelStepper_control firmware installed

//This program makes the robot drive forward quickly for 3 seconds, then back
//up slowly for 6 seconds

#include <M5Stack.h>
#include "FastLED.h"

//LED definitions
#define Neopixel_PIN 1
#define NUM_LEDS 7
CRGB leds[NUM_LEDS];

//Motor definitions
int dashSpeed = 20000; //medium
int backingSpeed = 10000; //slow
int pauseTime = 3000; //delay between the start of drive commands


void setup() 
{
  M5.begin();   //Call this first every time
  
  //Set up the LCD screen
  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextColor(CYAN); M5.Lcd.setTextSize(2); M5.Lcd.setCursor(40, 0);
  M5.Lcd.println("Simple Drive");
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(0, 25);
  M5.Lcd.println();
  M5.Lcd.println("- Dash Forward for 3 seconds");
  M5.Lcd.println();
  M5.Lcd.println("- Back up for 6 seconds");
  M5.Lcd.println();
  M5.Lcd.println("- Change the LED colors.");
  M5.Lcd.println();
  M5.Lcd.println("- Repeat.");

  // Neopixel initialization
  FastLED.addLeds<WS2811,Neopixel_PIN,RGB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(10);

  //Initialize communication with the Nano
  // Serial2.begin(unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin, bool invert)
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  
  //give the firmware time to start up on Nano
  delay(1000); 
}

void loop() 
{
  //Set the LEDs to green
  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.show();

  //Send the drive forward command
  //drive speeds range from 0..64000
  //64000 may be too fast for the motors to turn, depending on the surface
  setDrive(10000, 10000);

  delay(pauseTime);

  //Set the LEDs to red
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();

  //Send the back up command
  setDrive(-10000, -10000, backingSpeed);
  delay(2*pauseTime);
}

void setDrive(int Xspeed, int Yspeed) {
  Serial2.printf("S1 %6d\r", Xdistance);
  Serial2.printf("S2 %6d\r", Ydistance);
}
