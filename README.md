# Cornell Robotics 2019
### Example code and other resources for the Cornell Summer College class "Fabricating the Future"

#### Useful links and documentation

Google drive link: https://drive.google.com/open?id=1hPUkdF6yZZ2uZ4no-0SsohxhQZEXsbS1

M5 Software installation instructions: https://github.com/m5stack/M5Stack

Lecture notes and other files will be posted here

TEC-Bot 7 Project page: https://idea7.cc/project/tec-bot-7-0/
Includes a cool 3D model of the kit as well as assembly instructions

FastLED reference: https://github.com/FastLED/FastLED/wiki/Pixel-reference

Robot Motor Sizing Tutorial: https://www.robotshop.com/blog/en/drive-motor-sizing-tutorial-3661

#### How to get this code (and other git repositories)
If you're comfortable with Git the best way to keep up to date with this code is to clone the repository. Follow the instructions here:
[Cloning a Repository](https://help.github.com/articles/cloning-a-repository/).

A lower tech method is to download everything as a zip. This is much simpler but you'll have to repeat the process every time you want to update the code.
1. Click the green button labeled "Clone or Download".
2. Click "download zip".
3. Unzip the files and copy to your local Arduino Sketchbook directory. See this link for more info on how the Arduino IDE organizes files: [Arduino Files](https://programmingelectronics.com/understanding-the-arduino-sketchbook-opening-and-saving-arduino-sketches/).

You can also view a file simply by clicking on it. From there you can copy and paste the code into a new sketch in the Arduino IDE.

## M5 Programming Reference

This is a partial list of useful function related to the M5.

### Official M5Stack documentation
The official M5Stack documentation is here: [M5Stack Documentation](https://docs.m5stack.com/#/en/core/basic)

### General Arduino reference
Full documentation of the Arduino IDE can be found here: [Arduino IDE reference](https://arduino.cc/reference/en/)

More general Arduino reference: [Introduction to Arduino](https://arduino.cc/en/Guide/HomePage)

Check out this link for a good intro to the Arduino IDE and Arduino specific c++ functions: [LadyAda's Learn Arduino](https://learn.adafruit.com/ladyadas-learn-arduino-lesson-number-2)


### Basic M5 Functions

##### M5.begin()
Initialize the M5, must be called at the beginning of every program. To avoid problems with initializing DIO pins this should be the first line in the setup() routine at the beginning of every program.

##### M5.update()
This function updates the buttons and speaker. It should be included in the main loop function as well as any other loop that uses the buttons. See the "line_follow" sketch for a good example of how to use this function.

##### M5.powerOFF()
Turns off the M5, pretty self explanatory.

### LCD Text Functions

##### M5.Lcd.clear()
Clears the display and sets the background color to black.

##### M5.Lcd.setCursor(int x, int y, int fontSize)
Set the cursor location in pixels and the font size.

##### M5.Lcd.print(x)
Display the variable x (any data type) at the current cursor location.

##### M5.Lcd.printf(string formatString, x, y, ...)
Similar to the [c++ printf function](http://www.cplusplus.com/reference/cstdio/printf/). Uses formatString to display the variables x, y, etc.

### MPU9250 Functions
The MPU9250 is the motion processing unit (an accelerometer, gyroscope, magnetometer combo, also called an Inertial Measurement Unit or IMU) included in each M5.

##### Wire.begin()
Called at the beginning of each sketch that uses the MPU. Initializes I2C communication with the MPU

##### IMU.CalibrateMPU9250(IMU.gyroBias, IMU.accelBias)
Runs a routine to calibrate the accelerometer and gyro and stores the values in IMU.gyroBias and IMU.accelBias. The MPU must be placed on a level surface with the LCD screen pointing up and kept perfectly still while this routine runs.

##### IMU.initMPU9250()
Initialize the accelerometer and gyro.

##### IMU.initAK8963()
Initialize the magnetometer

##### IMU.readAccelData(IMU.accelCount), IMU.readGyroData(IMU.gyroCount), IMU.readMagData(IMU.magCount)
Reads data from the appropriate sensor and stores it in the provided array.
```
IMU.accelCount[0]  //acceleration in the x direction
IMU.accelCount[1]  //acceleration in the y direction
IMU.accelCount[2]  //acceleration in the z direction
```
##### IMU.getAres(), IMU.getGres(), IMU.getMres()
Returns the resolution of each sensor. Multiply this by the raw data to obtain properly scaled data in engineering units.

For example: `IMU.accelCount[0]*IMU.getAres` will return the current acceleration in the x direction in m/s^2

##### Check to see if new MPU data is available
The MPU9250 sets an internal flag whenever it reads new data.

`IMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01`

This will return true when new data is availabe
