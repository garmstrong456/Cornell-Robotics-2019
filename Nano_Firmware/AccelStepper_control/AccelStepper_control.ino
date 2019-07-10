//AccelStepper_control.ino
//
//Implements stepper motor control on the Arduino Nano for the TEC-Bot 7.
//Uses AccelStepper to allow continuous speed commands. Currently does not
//use acceleration or distance commands.
//
//To use: send string commands over Serial (just like with Grbl). Currently the
//the commands must follow a very strict format to be interpreted correctly
//TODO: implement better string parsing
//
//Commands (#'s indicate signed integers):
//"SS ###### ######" Set the speed of both motors at once
//"S1 ######"        Set the speed of motor 1
//"S2 ######"        Set the speed of motor 2
//"VV ######"        Set the max speed for both motors
//"AA ######"        Set the acceleration for both motors NOT CURRENTLY USED
//"P1"               Ask for the position of motor1
//"P2"               Ask for the position of motor2

#include <AccelStepper.h>
#include <NewPing.h>

AccelStepper motor1(AccelStepper::DRIVER, 2, 5);     //X axis from Grbl
AccelStepper motor2(AccelStepper::DRIVER, 3, 6);     //Y axis from Grbl

#define TRIG_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 200
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

int stepConversion = 8;     //used to convert Grbl units to AccelStepper units
                            //for continuity with GrblForBots
String lastCommand = "";

void setup() {
  motor1.setMaxSpeed(34000);        //Default values for max speed
  motor2.setMaxSpeed(34000);

  motor1.setPinsInverted(true);     //AccelStepper reverses the direction compared
  motor2.setPinsInverted(true);     //to Grbl. Fix that here

  motor1.setAcceleration(32000);    //Accel is not used in this version
  motor2.setAcceleration(32000);

  //Initialize coms with the M5
  Serial.begin(115200, SERIAL_8N1);
}

void loop() {
  //Check to see if a new character is available on the Serial line
  if (Serial.available()) {
    char commandChar = Serial.read();   //Read it if it is

    //If the character is a carriage return or newline assume we have a complete command
    if (commandChar == '\r' or commandChar == '\n') {
        //The first two characters of a command indicate what type it is
        String commandBase = lastCommand.substring(0, 2);

        //Set speed on both motors
        if      (commandBase == "SS") {
            motor1.setSpeed(lastCommand.substring(3,9).toInt()*stepConversion/60);
            motor2.setSpeed(lastCommand.substring(10).toInt()*stepConversion/60);
        }

        //Set speed on one motor
        else if (commandBase == "S1") {
            motor1.setSpeed(lastCommand.substring(3).toInt()*stepConversion/60);
        }
        else if (commandBase == "S2") {
            motor2.setSpeed(lastCommand.substring(3).toInt()*stepConversion/60);
        }

        //Set acceleration
        else if (commandBase == "AA") {
            int newAcc = lastCommand.substring(3).toInt()*stepConversion;
            motor1.setAcceleration(newAcc);
            motor2.setAcceleration(newAcc);
        } 

        //Set max speed
        else if (commandBase == "VV") {
            int newMaxSpeed = lastCommand.substring(3).toInt()*stepConversion/60;
            motor1.setMaxSpeed(newMaxSpeed);
            motor2.setMaxSpeed(newMaxSpeed);
        }

        //Return motor position
        else if (commandBase == "P1") {
            Serial.println(motor1.currentPosition());
        }
        else if (commandBase == "P2") {
            Serial.println(motor2.currentPosition());
        }
        else if (commandBase == "UU") {
            Serial.println(sonar.ping_cm());
        }
        lastCommand = "";   //Reset the command string for the next command
    }

    //If the command is not complete add the character to the command string
    else {
        lastCommand = lastCommand + commandChar;
    }
  }

  //update the motors
  motor1.runSpeed();
  motor2.runSpeed();
}
