#include <BleGamepad.h>
#include <ResponsiveAnalogRead.h>

#define leftJoyX 25 //A1
#define leftJoyY 26 //A0
#define rightJoyX 39 //A3
#define rightJoyY 34 //A2
#define restVal 16383 //Neutral rest value for joysticks

ResponsiveAnalogRead respLeftX(leftJoyX, true);
ResponsiveAnalogRead respLeftY(leftJoyY, true);
ResponsiveAnalogRead respRightX(rightJoyX, true);
ResponsiveAnalogRead respRightY(rightJoyY, true);

BleGamepad bleGamepad("Joy Test", "Team 24");

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
    Serial.println("Printing Max and Min Values for the Axes");
    maxLeftX = leftX;
    maxLeftY = leftY;
    maxRightX = rightX;
    maxRightY = rightY;
    
    minLeftX = leftX;
    minLeftY = leftY;
    minRightX = rightX;
    minRightY = rightY;

    Serial.println("Orignial Vals: ");
    Serial.print("minLeftX: ");
    Serial.println(minLeftX);
    Serial.print("maxLeftX: ");
    Serial.println(maxLeftX);
    Serial.print("minLeftY: ");
    Serial.println(minLeftY);
    Serial.print("maxLeftY: ");
    Serial.println(maxLeftY);
    Serial.print("minRightX: ");
    Serial.println(minRightX);
    Serial.print("maxRightX: ");
    Serial.println(maxRightX);
    Serial.print("minRightY: ");
    Serial.println(minRightY);
    Serial.print("maxRightY: ");
    Serial.println(maxRightY);
    Serial.println("");
    delay(5000);
    firstRead = 0;
  }
  else{
    if(leftX>maxLeftX){
      maxLeftX = leftX;
      Serial.print("maxLeftX: ");
      Serial.println(maxLeftX);
    }
    if(leftX<minLeftX){
      minLeftX = leftX;
      Serial.print("minLeftX: ");
      Serial.println(minLeftX);
    }
    
    if(leftY>maxLeftY){
      maxLeftY = leftY;
      Serial.print("maxLeftY: ");
      Serial.println(maxLeftY);
    }
    if(leftY<minLeftY){
      minLeftY = leftY;
      Serial.print("minLeftY: ");
      Serial.println(minLeftY);
    }

    if(rightX>maxRightX){
      maxRightX = rightX;
      Serial.print("maxRightX: ");
      Serial.println(maxRightX);
    }
    if(rightX<minRightX){
      minRightX = rightX;
      Serial.print("minRightX: ");
      Serial.println(minRightX);
    }

    if(rightY>maxRightY){
      maxRightY = rightY;
      Serial.print("maxRightY: ");
      Serial.println(maxRightY);
    }
    if(rightY<minRightY){
      minRightY = rightY;
      Serial.print("minRightY: ");
      Serial.println(minRightY);
    }
  }      
}

bool test = 1;

void testJoystickCalibration(bool pluggedIn){

  int leftX = 0;
  int leftY = 0;
  int rightX = 0;
  int rightY = 0;

  int minLeftX, maxLeftX, minLeftY, maxLeftY, minRightX, maxRightX, minRightY, maxRightY;

  // if(pluggedIn){
    minLeftX = 1850;
    maxLeftX = 1950;
    minLeftY = 1850;
    maxLeftY = 1950;
    minRightX = 1800;
    maxRightX = 1900;
    minRightY = 1800;
    maxRightY = 1869;
  // }
  // else{
  //   minLeftX = 1695;
  //   maxLeftX = 1705;
  //   minLeftY = 1710;
  //   maxLeftY = 1720;
  //   minRightX = 1635;
  //   maxRightX = 1645;
  //   minRightY = 1660;
  //   maxRightY = 1670;
  // }

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

  Serial.print("Analog Reads: ");
  Serial.print("LeftX: ");
  Serial.print(leftX);
  Serial.print(", LeftY: ");
  Serial.print(leftY);
  Serial.print(", rightX: ");
  Serial.print(rightX);
  Serial.print(", rightY: ");
  Serial.println(rightY);

  respLeftX.update();
  respLeftY.update();
  respRightX.update();
  respRightY.update();

  leftX = respLeftX.getValue();
  leftY = respLeftY.getValue();
  rightX = respRightX.getValue();
  rightY = respRightY.getValue();

  Serial.print("Responsive Analog: ");
  Serial.print("LeftX: ");
  Serial.print(leftX);
  Serial.print(", LeftY: ");
  Serial.print(leftY);
  Serial.print(", rightX: ");
  Serial.print(rightX);
  Serial.print(", rightY: ");
  Serial.print(rightY);
  Serial.println("");

  if(!respLeftX.hasChanged() && leftX >= minLeftX && leftX <= maxLeftX){
    leftX = restVal;
  }
  else{
    leftX = map(leftX, 0, 4095, 0, 32767);
  }

  if(!respLeftY.hasChanged() && leftY >= minLeftY && leftY <= maxLeftY){
    leftY = restVal;
  }
  else{  
    leftY = map(leftY, 0, 4095, 32767, 0);
  }

  if(!respRightX.hasChanged() && rightX >= minRightX && rightX <= maxRightX){
    rightX = restVal;
  }
  else{
    rightX = map(rightX, 0, 4095, 0, 32767);
  }

  if(!respRightY.hasChanged() && rightY >= minRightY && rightY <= maxRightY){
    rightY = restVal;
  }
  else{
    rightY = map(rightY, 0, 4095, 32767, 0);
  }

  bleGamepad.setLeftThumb(leftX,leftY);
  bleGamepad.setRightThumb(rightX,rightY);
}

void setup() {
  Serial.begin(115200);

  pinMode(4, INPUT);
  pinMode(27, INPUT_PULLUP);  
  pinMode(33, INPUT_PULLUP);  

  respLeftX.setAnalogResolution(4096);
  respLeftY.setAnalogResolution(4096);
  respRightX.setAnalogResolution(4096);
  respRightY.setAnalogResolution(4096);

  respLeftX.setActivityThreshold(30);
  respLeftY.setActivityThreshold(30);
  respRightX.setActivityThreshold(30);
  respRightY.setActivityThreshold(30);

  BleGamepadConfiguration bleGamepadConfig;
  bleGamepadConfig.setButtonCount(2);
  bleGamepadConfig.setHatSwitchCount(0);
  bleGamepadConfig.setWhichAxes(true, true, true, false, false, true, false, false); //only enable X, Y, Z, RZ
  bleGamepadConfig.setWhichSimulationControls(false,false,false,false,false);
  
  bleGamepad.begin(&bleGamepadConfig);
  delay(4000);
}

void loop() {
  
  //printAxesMaxMin();

  if(digitalRead(27)){
    bleGamepad.press(BUTTON_1);
  }
  else{
    bleGamepad.release(BUTTON_1);
  }
  if(digitalRead(33)){
    bleGamepad.press(BUTTON_2);
  }
  else{
    bleGamepad.release(BUTTON_2);
  }

  testJoystickCalibration(digitalRead(4));
}
