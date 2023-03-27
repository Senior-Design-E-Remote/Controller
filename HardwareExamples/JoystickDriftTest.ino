#include <BleGamepad.h>

#define leftJoyX 12
#define leftJoyY 14
#define rightJoyX 27
#define rightJoyY 26 

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

  for(int i = 0; i < 1000; i++){ //sum 10 readings
    leftX += analogRead(leftJoyX);
    leftY += analogRead(leftJoyY);
    rightX += analogRead(rightJoyX);
    rightY += analogRead(rightJoyY);
  }
  // get average of 10 readings and map them to Joystick range
  leftX /= 1000;
  leftY /= 1000;
  rightX /= 1000;
  rightY /= 1000;

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

BleGamepad bleGamepad("Joy Test", "Team 24");

void setup() {
  Serial.begin(115200);
  pinMode(16, INPUT_PULLUP);  
  pinMode(17, INPUT_PULLUP);  
  BleGamepadConfiguration bleGamepadConfig;
  bleGamepadConfig.setButtonCount(2);
  bleGamepadConfig.setWhichAxes(true, true, true, false, false, true, false, false); //only enable X, Y, Z, RZ
  bleGamepadConfig.setWhichSimulationControls(false,false,false,false,false);
  
  bleGamepad.begin(&bleGamepadConfig);
  delay(2000);
}

void loop() {
  
  //printAxesMaxMin();

  if(digitalRead(16)){
    bleGamepad.press(BUTTON_1);
  }
  else{
    bleGamepad.release(BUTTON_1);
  }
  if(digitalRead(17)){
    bleGamepad.press(BUTTON_2);
  }
  else{
    bleGamepad.release(BUTTON_2);
  }

  float restVal = 16383;

  //for(int restVal = 16383; restVal < 16386; restVal++) { //Uncomment if you want to cycle through Joystick rest Values

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

  Serial.print("restVal: ");
  Serial.print(restVal);
  Serial.print(", LeftX: ");
  Serial.print(leftX);
  Serial.print(", LeftY: ");
  Serial.print(leftY);
  Serial.print(", rightX: ");
  Serial.print(rightX);
  Serial.print(", rightY: ");
  Serial.print(rightY);

  if(leftX>1925 && leftX<1937){
    leftX = restVal;
  }
  else{
    leftX = map(leftX, 0, 4095, 32767, 0);
  }

  if(leftY>1927 && leftY<1941){
    leftY = restVal;
  }
  else{
    leftY = map(leftY, 0, 4095, 0, 32767);
  }

  if(rightX>1875 && rightX<1932){
    rightX = restVal;
  }
  else{
    rightX = map(rightX, 0, 4095, 32767, 0);
  }

  if(rightY>1870 && rightY<1927){
    rightY = restVal;
  }
  else{
    rightY = map(rightY, 0, 4095, 0, 32767); 
  }

  Serial.print(", LeftX: ");
  Serial.print(leftX);
  Serial.print(", LeftY: ");
  Serial.print(leftY);
  Serial.print(", rightX: ");
  Serial.print(rightX);
  Serial.print(", rightY: ");
  Serial.print(rightY);
  Serial.println("");

  bleGamepad.setLeftThumb(leftX,leftY);
  bleGamepad.setRightThumb(rightX,rightY);
  //}
}
