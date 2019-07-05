#include <M5Stack.h>
#include "FastLED.h"
#include <ESP32Servo.h>

#define Neopixel_PIN 1
#define NUM_LEDS 7
CRGB leds[NUM_LEDS];

#define SERVO1_PIN 12
#define SERVO2_PIN 19
Servo servo1;
Servo servo2;

int pos = 0;
int sweepDirection = 1;

void setup() {
  M5.begin();

  M5.Lcd.setTextColor(GREEN, BLACK); M5.Lcd.setTextSize(2); M5.Lcd.setCursor(40,0);
  M5.Lcd.println("Sweep the Servos");
  M5.Lcd.setTextColor(WHITE, BLACK); M5.Lcd.setTextSize(1);

  servo1.setPeriodHertz(50);
  servo2.setPeriodHertz(50);
  servo1.attach(SERVO1_PIN, 1000, 2000);
  servo2.attach(SERVO2_PIN, 1000, 2000);

  FastLED.addLeds<WS2811,Neopixel_PIN,GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.clear();
  

}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) {
    servo1.write(pos);
    servo2.write(180 - pos);

    M5.Lcd.setCursor(0, 25);
    M5.Lcd.printf("Servo 1 pos: %3d, Servo2 pos: %3d", pos, 180 - pos);

    delay(20);

    FastLED.show();
  }

  for (pos = 180; pos >= 0; pos -= 1) {
    servo1.write(pos);
    servo2.write(180 - pos);

    M5.Lcd.setCursor(0, 25);
    M5.Lcd.printf("Servo 1 pos: %3d, Servo2 pos: %3d", pos, 180 - pos);

    delay(20);

    FastLED.show();
  }
}
