//Esp being used is the ESP32-DevKitC-32E
//ESP32 BLE Controller Library: https://github.com/lemmingDev/ESP32-BLE-Gamepad

#include <Arduino.h>
#include <BleGamepad.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

const int numButtons = 10;

const int leftJoyX = 39;
const int leftJoyY = 36;
const int rightJoyX = 14;
const int rightJoyY = 12; 

const int buttons[numButtons] = {16,17,0,10,2,3,11,5,6,9}; //A, X, Y, B, Start, Select Note: last 4 are for touch buttons

const byte buttonNames[numButtons] = {BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4, BUTTON_5, BUTTON_6, BUTTON_7, BUTTON_8, BUTTON_9, BUTTON_10};

bool oldButtonStates[numButtons] = {0,0,0,0,0,0,0,0,0,0};

uint16_t currtouched = 0;
Adafruit_MPR121 cap = Adafruit_MPR121();

BleGamepad bleGamepad("E-Remote", "Team 24", 100);

void setup()
{ 
  Serial.begin(115200);

  Serial.println("hi");
  
  cap.begin(0x5A);

  for(int i = 0; i < numButtons-4; i++){ // Initialize all buttons

    pinMode(buttons[i], INPUT_PULLUP);
  }
  BleGamepadConfiguration bleGamepadConfig;
  bleGamepadConfig.setButtonCount(numButtons);
  bleGamepadConfig.setWhichAxes(true, true, true, false, false, true, false, false); //only enable X, Y, Z, RZ
  bleGamepadConfig.setWhichSimulationControls(false,false,false,false,false);
  bleGamepad.begin(&bleGamepadConfig);
  //The default bleGamepad.begin() above enables 16 buttons, all axes, one hat, and no simulation controls or special buttons
}

void loop()
{   
    if (bleGamepad.isConnected())
    {
        bool buttonState;
        currtouched = cap.touched();

        for(int i = 0; i < numButtons; i++){ //Set button values, subtract 4 for the capacitive touch buttons
          if(i < 2){
            buttonState = digitalRead(buttons[i]); //Normal Buttons    
          }
          else {
            buttonState = currtouched & _BV(buttons[i]); //Capacitive Buttons
          }
          Serial.print("Button ");
          Serial.print(buttons[i]);
          if(buttonState){
            Serial.println("on");
          }
          else{
            Serial.println("off");
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

        leftX = map(leftX, 0, 4095, 0, 32767);
        leftY = map(leftY, 0, 4095, 0, 32767);
        rightX = map(rightX, 0, 4095, 0, 32767);
        rightY = map(rightY, 0, 4095, 0, 32767);       

        bleGamepad.setLeftThumb(leftX,leftY);
        bleGamepad.setRightThumb(rightX,rightY);

        Serial.print("rightX: ");
        Serial.print(rightX);
        Serial.print(", rightY: ");
        Serial.println(rightY);
    }
}
