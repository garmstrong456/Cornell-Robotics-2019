#include <M5Stack.h>

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(3);
}

bool blinkState = false, blinkState2 = false;
uint32_t lastBlinkTime = 0, lastBlinkTime2 = 0;
const int blinkPeriod = 500, blinkPeriod2 = 200;

void loop() {
  if (millis() > lastBlinkTime + blinkPeriod) {   //ready for a new blink
    M5.Lcd.setCursor(25,25);
    if (blinkState) {
      M5.Lcd.setTextColor(WHITE, BLACK);
    }
    else {
      M5.Lcd.setTextColor(RED, BLACK);
    }
    M5.Lcd.print("BLINK!");
    blinkState = !blinkState;
  }

  if (millis() > lastBlinkTime2 + blinkPeriod2) {   //ready for a new blink
    M5.Lcd.setCursor(25,50);
    if (blinkState2) {
      M5.Lcd.setTextColor(WHITE, BLACK);
    }
    else {
      M5.Lcd.setTextColor(RED, BLACK);
    }
    M5.Lcd.print("BLINK FASTER!");
    blinkState2 = !blinkState2;
  }
  
}
