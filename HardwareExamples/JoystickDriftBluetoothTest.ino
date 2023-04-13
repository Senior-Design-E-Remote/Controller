#include <ResponsiveAnalogRead.h>
#include "BluetoothSerial.h"

#define leftJoyX 25 //A1
#define leftJoyY 26 //A0
#define rightJoyX 39 //A3
#define rightJoyY 34 //A2
#define restVal 16383 //Neutral rest value for joysticks

ResponsiveAnalogRead respLeftX(leftJoyX, true);
ResponsiveAnalogRead respLeftY(leftJoyY, true);
ResponsiveAnalogRead respRightX(rightJoyX, true);
ResponsiveAnalogRead respRightY(rightJoyY, true);

BluetoothSerial SerialBT;

void printAxesMaxMin(){

  static bool firstRead = 1;

  static int maxLeftX = 0;
  static int maxLeftY = 0;
  static int maxRightX = 0;
  static int maxRightY = 0;

  static int minLeftX = 0;
  static int minLeftY = 0;
  static int minRightX = 0;
  static int minRightY = 0;

  int leftX = 0;
  int leftY = 0;
  int rightX = 0;
  int rightY = 0;

  for(int i = 0; i < 100; i++){ //sum 10 readings
    leftX += analogRead(leftJoyX);
    leftY += analogRead(leftJoyY);
    rightX += analogRead(rightJoyX);
    rightY += analogRead(rightJoyY);
  }
  // get average of 10 readings and map them to Joystick range
  leftX /= 100;
  leftY /= 100;
  rightX /= 100;
  rightY /= 100;

  if(firstRead){
    SerialBT.println("Printing Max and Min Values for the Axes");
    maxLeftX = leftX;
    maxLeftY = leftY;
    maxRightX = rightX;
    maxRightY = rightY;
    
    minLeftX = leftX;
    minLeftY = leftY;
    minRightX = rightX;
    minRightY = rightY;

    SerialBT.println("Orignial Vals: ");
    SerialBT.print("minLeftX: ");
    SerialBT.println(minLeftX);
    SerialBT.print("maxLeftX: ");
    SerialBT.println(maxLeftX);
    SerialBT.print("minLeftY: ");
    SerialBT.println(minLeftY);
    SerialBT.print("maxLeftY: ");
    SerialBT.println(maxLeftY);
    SerialBT.print("minRightX: ");
    SerialBT.println(minRightX);
    SerialBT.print("maxRightX: ");
    SerialBT.println(maxRightX);
    SerialBT.print("minRightY: ");
    SerialBT.println(minRightY);
    SerialBT.print("maxRightY: ");
    SerialBT.println(maxRightY);
    SerialBT.println("");
    delay(5000);
    firstRead = 0;
  }
  else{
    if(leftX>maxLeftX){
      maxLeftX = leftX;
      SerialBT.print("maxLeftX: ");
      SerialBT.println(maxLeftX);
    }
    if(leftX<minLeftX){
      minLeftX = leftX;
      SerialBT.print("minLeftX: ");
      SerialBT.println(minLeftX);
    }
    
    if(leftY>maxLeftY){
      maxLeftY = leftY;
      SerialBT.print("maxLeftY: ");
      SerialBT.println(maxLeftY);
    }
    if(leftY<minLeftY){
      minLeftY = leftY;
      SerialBT.print("minLeftY: ");
      SerialBT.println(minLeftY);
    }

    if(rightX>maxRightX){
      maxRightX = rightX;
      SerialBT.print("maxRightX: ");
      SerialBT.println(maxRightX);
    }
    if(rightX<minRightX){
      minRightX = rightX;
      SerialBT.print("minRightX: ");
      SerialBT.println(minRightX);
    }

    if(rightY>maxRightY){
      maxRightY = rightY;
      SerialBT.print("maxRightY: ");
      SerialBT.println(maxRightY);
    }
    if(rightY<minRightY){
      minRightY = rightY;
      SerialBT.print("minRightY: ");
      SerialBT.println(minRightY);
    }
  }      
}

void testJoystickCalibration(){

  int leftX = 0;
  int leftY = 0;
  int rightX = 0;
  int rightY = 0;

  for(int i = 0; i < 100; i++){ //sum 1000 readings
    leftX += analogRead(leftJoyX);
    leftY += analogRead(leftJoyY);
    rightX += analogRead(rightJoyX);
    rightY += analogRead(rightJoyY);
  }
  // get average of 10 readings and map them to Joystick range
  leftX /= 100;
  leftY /= 100;
  rightX /= 100;
  rightY /= 100;

  SerialBT.print("Analog Reads: ");
  SerialBT.print("LeftX: ");
  SerialBT.print(leftX);
  SerialBT.print(", LeftY: ");
  SerialBT.print(leftY);
  SerialBT.print(", rightX: ");
  SerialBT.print(rightX);
  SerialBT.print(", rightY: ");
  SerialBT.println(rightY);

  respLeftX.update();
  respLeftY.update();
  respRightX.update();
  respRightY.update();

  leftX = respLeftX.getValue();
  leftY = respLeftY.getValue();
  rightX = respRightX.getValue();
  rightY = respRightY.getValue();

  SerialBT.print("Responsive Analog: ");
  SerialBT.print("LeftX: ");
  SerialBT.print(leftX);
  SerialBT.print(", LeftY: ");
  SerialBT.print(leftY);
  SerialBT.print(", rightX: ");
  SerialBT.print(rightX);
  SerialBT.print(", rightY: ");
  SerialBT.print(rightY);
  SerialBT.println("");

  // if(!respLeftX.hasChanged() && leftX < 2000 && leftX > 1800){
  //   leftX = restVal;
  // }
  // else{
  //   leftX = map(leftX, 0, 4095, 0, 32767);
  // }

  // if(!respLeftY.hasChanged() && leftY < 2000 && leftY > 1800){
  //   leftY = restVal;
  // }
  // else{  
  //   leftY = map(leftY, 0, 4095, 32767, 0);
  // }

  // if(!respRightX.hasChanged() && rightX < 2000 && rightX > 1800){
  //   rightX = restVal;
  // }
  // else{
  //   rightX = map(rightX, 0, 4095, 0, 32767);
  // }

  // if(!respRightY.hasChanged() && rightY < 2000 && rightY > 1800){
  //   rightY = restVal;
  // }
  // else{
  //   rightY = map(rightY, 0, 4095, 32767, 0);
  // }
}

void setup() {
  SerialBT.begin("JoyTestBluetooth");

  respLeftX.setAnalogResolution(4096);
  respLeftY.setAnalogResolution(4096);
  respRightX.setAnalogResolution(4096);
  respRightY.setAnalogResolution(4096);

  respLeftX.setActivityThreshold(30);
  respLeftY.setActivityThreshold(30);
  respRightX.setActivityThreshold(30);
  respRightY.setActivityThreshold(30);

  delay(10000);
}

void loop() {
  
  //printAxesMaxMin();

  testJoystickCalibration();
}