//line_follower.ino
//This sketch implements line following for the TEC-Bot 7 using a Pololu
//QTR reflectance sensor and PID. It makes use of a custom Nano firmware
//(not the standard TEC-Bot Grbl) to be able to command the motors to move
//at a constant rate.
//
//You can tune the PID values using the M5 stack buttons. Once you find values
//that work well change the starting values in the sketch below.

#include <M5Stack.h>
#include <QTRSensors.h>
#include <FastLED.h>

//SET STARTING PID VALUES//
float kp = 5;               //proportional gain
float kd = 0;               //derivative gain
int baseSpeed = 5000;  //base speed
const int MAX_SPEED = 10000;

//PID variables
float motor1Speed, motor2Speed;
float lastError = 0;

//Adjustable parameter variables
float kpInc = 0.1;
float kdInc = 0.1;
int speedInc = 1000;

//Line sensor declarations
QTRSensors qtr;
const uint8_t SensorCount = 3;
uint16_t  sensorValues[SensorCount];

//LED declarations
#define Neopixel_PIN 1
#define NUM_LEDS 7
CRGB leds[NUM_LEDS];

void setup() {
  M5.begin();

  //Print the title text
  M5.Lcd.setTextColor(CYAN); M5.Lcd.setTextSize(2); M5.Lcd.setCursor(40, 0);
  M5.Lcd.println("Line Following");
  M5.Lcd.setTextColor(WHITE, BLACK);

  //Initialize the LEDs
  FastLED.addLeds<WS2811, Neopixel_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();

  //Initialize the line sensor
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]) {
    2, 5, 15
  }, SensorCount);

  //Initialize Grbl
  Serial2.begin(115200, SERIAL_8N1, 16, 17);

  //Wait for the user to press button A, then start calibrating the sensor
  M5.Lcd.setCursor(0, 30);
  M5.Lcd.println("press button A");
  M5.Lcd.println("to start calibrating");

  while (!M5.BtnA.wasPressed()) {
    M5.update();
  }

  M5.Lcd.setCursor(0, 30);
  M5.Lcd.println("calibrating...");
  M5.Lcd.println("move robot back and forth over line");
  for (int i = 0; i < 100; i++) {
    qtr.calibrate();
  }

  //Turn the LEDs green to indicate calibration is finished
  //wait for the user to press button A to continue
  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.show();
  M5.Lcd.println("done");
  M5.Lcd.println("press A to start");

  M5.update();
  while (!M5.BtnA.wasPressed()) {
    M5.update();
  }

  M5.Lcd.clear(); M5.Lcd.setCursor(40, 0); M5.Lcd.setTextColor(CYAN);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("Follow the line!");
  M5.Lcd.setTextColor(WHITE, BLACK); M5.Lcd.setTextSize(1);

}

void loop() {
  M5.update();

  ///////////////////
  //**PID SECTION**//
  ///////////////////

  //Read the line position
  uint16_t position = qtr.readLineBlack(sensorValues);

  //Calculate the error and correction
  float error = (float)position - 1000.0;
  float driveCorrection = kp * error + kd * (error - lastError);
  lastError = error;

  //Calculate the new motor speeds
  motor1Speed = baseSpeed + driveCorrection;
  motor2Speed = baseSpeed - driveCorrection;

  //////////////////////////
  //**Update the display**//
  //////////////////////////

  M5.Lcd.setCursor(0, 25); M5.Lcd.printf("Motor 1 Speed   : %2.2f", motor1Speed);
  M5.Lcd.setCursor(0, 40); M5.Lcd.printf("Motor 2 Speed   : %2.2f", motor2Speed);
  M5.Lcd.setCursor(0, 55); M5.Lcd.printf("Error           : %2.2f", error);
  M5.Lcd.setCursor(0, 70); M5.Lcd.printf("Drive Correction: %2.2f", driveCorrection);
  M5.Lcd.setCursor(0, 90); M5.Lcd.print("Button Menu");
  M5.Lcd.setCursor(0, 105); M5.Lcd.print("A: adjust kp  B: adjust kd  C: adjust speed");

  ///////////////////////////////
  //**Send the drive commands**//
  ///////////////////////////////
  
  setDrive(motor1Speed, motor2Speed, MAX_SPEED);

  /////////////////////////////////////
  //**Adjust the gain using buttons**//
  /////////////////////////////////////
  
  if (M5.BtnA.wasPressed()) {
    M5.update();
    M5.Lcd.clear();
    M5.Lcd.setCursor(14, 20); M5.Lcd.print("Tune P Gain (Kp)");
    M5.Lcd.setCursor(14, 35); M5.Lcd.print("A to continue");
    M5.Lcd.setCursor(14, 55); M5.Lcd.print("B to raise Kp");
    M5.Lcd.setCursor(14, 75); M5.Lcd.print("C to lower Kp");

    while (!M5.BtnA.wasPressed()) {
      M5.update();
      if (M5.BtnB.wasPressed()) {
        kp = kp + kpInc;
      }
      if (M5.BtnC.wasPressed()) {
        kp = kp - kpInc;
      }
      if (kp < 0) kp = 0;
      M5.Lcd.setCursor(14, 95); M5.Lcd.printf("Current Kp: %.4f", kp);
    }
    M5.Lcd.clear();
  }

  //Button B = adjust kd
  if (M5.BtnB.wasPressed()) {
    M5.update();
    M5.Lcd.clear();
    M5.Lcd.setCursor(14, 20); M5.Lcd.print("Tune D Gain (Kd)");
    M5.Lcd.setCursor(14, 35); M5.Lcd.print("A to continue");
    M5.Lcd.setCursor(14, 55); M5.Lcd.print("B to raise Kd");
    M5.Lcd.setCursor(14, 75); M5.Lcd.print("C to lower Kd");

    while (!M5.BtnA.wasPressed()) {
      M5.update();
      if (M5.BtnB.wasPressed()) {
        kd += kdInc;
      }
      if (M5.BtnC.wasPressed()) {
        kd -= kdInc;
      }
      if (kd < 0) kd = 0;
      M5.Lcd.setCursor(14, 95, 2); M5.Lcd.printf("Current Kd: %3.2f", kd);
    }
    M5.Lcd.clear();
  }

  //Button C = adjust delay
  if (M5.BtnC.wasPressed()) {
    M5.update();
    M5.Lcd.clear();
    M5.Lcd.setCursor(14, 20); M5.Lcd.print("Adjust speed");
    M5.Lcd.setCursor(14, 35); M5.Lcd.print("A to continue");
    M5.Lcd.setCursor(14, 55); M5.Lcd.print("B to go faster");
    M5.Lcd.setCursor(14, 75); M5.Lcd.print("C to go slower");

    while (!M5.BtnA.wasPressed()) {
      M5.update();
      if (M5.BtnB.wasPressed()) {
        baseSpeed += speedInc;
      }
      if (M5.BtnC.wasPressed()) {
        baseSpeed -= speedInc;
      }
      M5.Lcd.setCursor(14, 95, 2); M5.Lcd.printf("Current delay: %3d", baseSpeed);
    }
    M5.Lcd.clear();
  }
}

void setDrive(int speed1, int speed2, int rate) {
  Serial2.printf("SS %6d %6d\r", speed1, speed2);
}
