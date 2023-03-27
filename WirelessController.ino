//Esp being used is the ESP32-DevKitC-32E
//ESP32 BLE Controller Library: https://github.com/lemmingDev/ESP32-BLE-Gamepad

#include <Arduino.h>
#include <BleGamepad.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

#define numButtons 15

#define leftJoyX 25
#define leftJoyY 26
#define rightJoyX 36
#define rightJoyY 4 

const int buttons[numButtons] = {12,27,15,12,27,33,15,0,1,3,4,6,7,9,10}; //first two are manual buttons, 11-4 are the core 8, the last four are the dpad

const byte buttonNames[numButtons] = {BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4, BUTTON_5, BUTTON_6, BUTTON_7, BUTTON_8, BUTTON_9, BUTTON_10, BUTTON_11, BUTTON_12, BUTTON_13, BUTTON_14, BUTTON_15};//, BUTTON_11, BUTTON_12, BUTTON_13, BUTTON_14};

bool oldButtonStates[numButtons] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

uint16_t coreCurrtouched = 0;
Adafruit_MPR121 coreCap = Adafruit_MPR121();

BleGamepad bleGamepad("E-Remote", "Team 24");

void setup()
{ 
  Serial.begin(115200);
  
  while(!coreCap.begin(0x5A)){

    Serial.println("Core Cap Not Connected");
  }

  Serial.println("Core Cap Connected");

  for(int i = 0; i < 8; i++){ // Initialize all buttons

    pinMode(buttons[i], INPUT_PULLUP);
  }  

  pinMode(buttons[2], INPUT);

  BleGamepadConfiguration bleGamepadConfig;
  bleGamepadConfig.setButtonCount(numButtons);
  bleGamepadConfig.setHatSwitchCount(1);
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
    
    for(int i = 0; i < numButtons; i++){ //Set button values, subtract 4 for the capacitive touch buttons
      if(i < 3){
        buttonState = 0;
        //buttonState = digitalRead(buttons[i]); //Normal Buttons    
      }
      else if(i >= 3 && i < 7){
        buttonState = digitalRead(buttons[i]); //Normal Buttons        
      }
      else{ //core 8 buttons
        buttonState = coreCurrtouched & _BV(buttons[i]); //Core 8 Capacitive Buttons
      }      

      if(oldButtonStates[i] != buttonState){ //Only send new signal if button state changed
        oldButtonStates[i] = buttonState;
        if(buttonState){
          bleGamepad.press(buttonNames[i]);
          Serial.print("Button ");
          Serial.print(i);
          Serial.println(" Pressed");
        }          
        else{
          bleGamepad.release(buttonNames[i]);
          Serial.print("Button ");
          Serial.print(i);
          Serial.println(" Unpressed");           
        }
      }
    }

    //Set Joystick Values. Note: Joysticks need 3.3V?

    int leftX = 0;
    int leftY = 0;
    int rightX = 0;
    int rightY = 0;

    for(int i = 0; i < 10; i++){ //sum 10 readings
      leftX += analogRead(leftJoyX);
      leftY += analogRead(leftJoyY);
      rightX += analogRead(rightJoyX);
      rightY += analogRead(rightJoyY);
    }
    // get average of 10 readings and map them to Joystick range
    leftX /= 10;
    leftY /= 10;
    rightX /= 10;
    rightY /= 10;

    leftX = map(leftX, 0, 4095, 32767, 0);
    leftY = map(leftY, 0, 4095, 0, 32767);
    rightX = map(rightX, 0, 4095, 32767, 0);
    rightY = map(rightY, 0, 4095, 0, 32767);       

    bleGamepad.setLeftThumb(leftX,leftY);
    bleGamepad.setRightThumb(rightX,rightY);
  }
}

//https://www.youtube.com/watch?v=KTMq3vARsko
