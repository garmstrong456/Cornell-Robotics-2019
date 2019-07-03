// For TEC Bot 7.0 with grbl 1.1 loaded on the Nano V3 co-processor
// Grbl settings changed from default using the Universal Gcode sender as follows:
// $100=32 -- For the x axis (left motor) set to 1/16th micro stepping, this makes 100 steps equal to 1 full rotation of the wheel
// $101=32 -- Same, but for the Y axis (right motor)
// $110=64000 -- Fastest stable tested speed for 1/16th micro stepping.  Can go faster by selecting different micro stepping (hardware switch)
// $111=64000 -- Same for Y
// $120=1000 -- Acceleratin that reliably prevents skipping steps...could push higher
// $121=1000 -- Same for Y
// 1/16th micro stepping is selected on the blue hardware switch by switching the 3rd switch on. (Off, Off, On)

// This program sends instructions to grbl and is set with enough time between commands so that grbl doesn't get behind.
// It is also possible to send much smaller step sizes in a loop.  When grble gets two back to back travel commands, it smoothly
// accellerates to the new command...so smooth driving can be achieved easily instead of start stop start stop.

// Grbl also keeps the x and y axis coordinated so they start and stop at the same time.  This makes it easy to do smooth turns for example.

// The FastLED library is used instead of the Neopixel library because the Neopixel library conflicts with the m5Stack library somehow

// This example makes the robot back up 4 revolutions and then drive forward quickly 4 revolutions...then repeat.

#include <M5Stack.h>
#include "FastLED.h"

//LED definitions
#define Neopixel_PIN 1
#define NUM_LEDS 7
CRGB leds[NUM_LEDS];

//Motor definitions
//Max dash speed is about 64000 ticks/min
int dashSpeed = 20000; //medium
int backingSpeed = 10000; //slow
int driveDistance = 400; //positive numbers are FWD. 100 = 1 full revolution
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
  M5.Lcd.println("- Drive Forward 4 revolutions");
  M5.Lcd.println();
  M5.Lcd.println("- Back up 4 revolutions.");
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
  
  //give grbl time to start up on Nano
  delay(1000); 
}

void loop() 
{
  //Set the LEDs to green
  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.show();

  //Send the drive forward command
  //driveDistance: 100 = 1 full rotation
  //speed: units/minute (0 - 64000)
  setDrive(driveDistance, driveDistance, dashSpeed);

  delay(pauseTime);

  //Set the LEDs to red
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();

  //Send the back up command
  setDrive(-driveDistance, -driveDistance, backingSpeed);
  delay(2*pauseTime);
}

void setDrive(int Xdistance, int Ydistance, int rate) {
  Serial2.printf("$J = G21 G91 X%d Y%d F%d", Xdistance, Ydistance, rate);
  Serial2.print("\r\n\r\n");
}
