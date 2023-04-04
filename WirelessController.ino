//Esp being used is the Adafruit HUZZAH32 - ESP32 Feather
//ESP32 BLE Controller Library: https://github.com/lemmingDev/ESP32-BLE-Gamepad
//MPR121 Chip: https://www.adafruit.com/product/1982

#include <Arduino.h>
#include <BleGamepad.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"
#include <ResponsiveAnalogRead.h>

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

#define numButtons 16

#define leftJoyX 25 //A1
#define leftJoyY 26 //A0
#define rightJoyX 39 //A3
#define rightJoyY 34 //A2
#define restVal 16383 //Neutral rest value for joysticks

//Set up Responsive Analog Reads for each joystick axis

ResponsiveAnalogRead respLeftX(leftJoyX, true);
ResponsiveAnalogRead respLeftY(leftJoyY, true);
ResponsiveAnalogRead respRightX(rightJoyX, true);
ResponsiveAnalogRead respRightY(rightJoyY, true);

const int buttons[numButtons] = {27,33,32,15,0,1,2,3,4,5,6,7,8,9,10,11}; //first two are manual buttons, the other 12 are the touch capacitiv buttons connected to the MPR121

const byte buttonNames[numButtons] = {BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4, BUTTON_5, BUTTON_6, BUTTON_7, BUTTON_8, BUTTON_9, BUTTON_10, BUTTON_11, BUTTON_12, BUTTON_13, BUTTON_14, BUTTON_15, BUTTON_16}; //BUTTON_1 and BUTTON_2 are the physical buttons

bool oldButtonStates[numButtons] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //Save previous state of each button

uint16_t coreCurrtouched = 0;
Adafruit_MPR121 coreCap = Adafruit_MPR121();

BleGamepad bleGamepad("E-Remote", "Team 24");

void setup()
{ 
  Serial.begin(115200);
  // coreCap.begin(0x5A);
  while(!coreCap.begin(0x5A)){

    Serial.println("Core Cap Not Connected");
  }

  Serial.println("Core Cap Connected");

  for(int i = 0;i < 4;i++){ //Initialize Physical Buttons
    pinMode(buttons[i], INPUT_PULLUP); 
  }

  respLeftX.setAnalogResolution(4096);
  respLeftY.setAnalogResolution(4096);
  respRightX.setAnalogResolution(4096);
  respRightY.setAnalogResolution(4096);

  respLeftX.setActivityThreshold(30);
  respLeftY.setActivityThreshold(30);
  respRightX.setActivityThreshold(30);
  respRightY.setActivityThreshold(30);

  BleGamepadConfiguration bleGamepadConfig;
  bleGamepadConfig.setButtonCount(numButtons);
  bleGamepadConfig.setHatSwitchCount(0);
  bleGamepadConfig.setWhichAxes(true, true, true, false, false, true, false, false); //only enable X, Y, Z, RZ
  bleGamepadConfig.setWhichSimulationControls(false,false,false,false,false);
  
  bleGamepad.begin(&bleGamepadConfig);
}

void loop()
{   
  if (bleGamepad.isConnected())
  {
    bool buttonState;
    coreCurrtouched = coreCap.touched();
    
    for(int i = 0; i < numButtons; i++){ //Loop through buttons and check state
      if(i < 2){//Physical Buttons: Start, Select
        buttonState = digitalRead(buttons[i]);   
      }
      else if(i >=2 && i <4){ //Physical Buttons: Joystick Push-Ins need to be inverted for some reason
        buttonState = !digitalRead(buttons[i]);
      }
      else{ ////Capacitive Buttons: X,Y,LT,LB,RB,RT,A,B + DPad
        buttonState = coreCurrtouched & _BV(buttons[i]); 
      }      

      if(oldButtonStates[i] != buttonState){ //Only send new signal if button state changed
        oldButtonStates[i] = buttonState;
        if(buttonState){
          bleGamepad.press(buttonNames[i]);
        }          
        else{
          bleGamepad.release(buttonNames[i]);         
        }
      }
    }

    //Set Joystick Values Note: The joysticks fluctuate between values when at rest so 16383 is sent when they are within these ranges since 16383 is the true rest value

    int leftX = 0;
    int leftY = 0;
    int rightX = 0;
    int rightY = 0;

    //Filter Noise

    respLeftX.update();
    respLeftY.update();
    respRightX.update();
    respRightY.update();

    leftX = respLeftX.getValue();
    leftY = respLeftY.getValue();
    rightX = respRightX.getValue();
    rightY = respRightY.getValue();

    if(!respLeftX.hasChanged() && leftX < 2000 && leftX > 1800){
      leftX = restVal;
    }
    else{
      leftX = map(leftX, 0, 4095, 0, 32767);
    }

    if(!respLeftY.hasChanged() && leftY < 2000 && leftY > 1800){
      leftY = restVal;
    }
    else{  
      leftY = map(leftY, 0, 4095, 32767, 0);
    }

    if(!respRightX.hasChanged() && rightX < 2000 && rightX > 1800){
      rightX = restVal;
    }
    else{
      rightX = map(rightX, 0, 4095, 0, 32767);
    }

    if(!respRightY.hasChanged() && rightY < 2000 && rightY > 1800){
      rightY = restVal;
    }
    else{
      rightY = map(rightY, 0, 4095, 32767, 0);
    }

    bleGamepad.setLeftThumb(leftX,leftY);
    bleGamepad.setRightThumb(rightX,rightY);
  }
}

//https://www.youtube.com/watch?v=KTMq3vARsko
