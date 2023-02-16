//Esp being used is the ESP32-DevKitC-32E
//ESP32 BLE Controller Library: https://github.com/lemmingDev/ESP32-BLE-Gamepad

#include <Arduino.h>
#include <BleGamepad.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

const int numButtons = 10;//14;

const int leftJoyX = 25;
const int leftJoyY = 26;
const int rightJoyX = 36;
const int rightJoyY = 4; 

const int batteryPin = 13;
int batteryCount = 0;
float oldBatteryLevel = 0.0;
float batteryLevel = 0.0;

const int buttons[numButtons] = {12,27,11,10,9,8,7,6,5,4};//,9,6,3,0}; //first two are manual buttons, 11-4 are the core 8, 9 6 3 0 are the dpad

const byte buttonNames[numButtons] = {BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4, BUTTON_5, BUTTON_6, BUTTON_7, BUTTON_8, BUTTON_9, BUTTON_10};//, BUTTON_11, BUTTON_12, BUTTON_13, BUTTON_14};

bool oldButtonStates[numButtons] = {0,0,0,0,0,0,0,0,0,0};//,0,0,0,0};

uint16_t coreCurrtouched = 0;
// uint16_t dpCurrtouched = 0;
Adafruit_MPR121 coreCap = Adafruit_MPR121();
// Adafruit_MPR121 dpCap = Adafruit_MPR121();

BleGamepad bleGamepad("E-Remote", "Team 24", 100);

void setup()
{ 
  Serial.begin(115200);

  pinMode(batteryPin, INPUT);
  
  while(!coreCap.begin(0x5A)){

    Serial.println("Core Cap Not Connected");
  }

  Serial.println("Core Cap Connected");

  // while(!dpCap.begin(0x5B)){

  //   Serial.println("DPad Cap Not Connected");
  // }

  // Serial.println("DPad Cap Connected");

  for(int i = 0; i < 2; i++){ // Initialize all buttons

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
      // if(batteryCount >= 30){ //average battery level over time before reporting
        
      //   batteryLevel = batteryLevel + analogRead(batteryPin);

      //   uint8_t bl = (uint8_t) batteryLevel; //cast float to unit6_t

      //   if(batteryLevel != oldBatteryLevel{

      //     //float voltage = sensorValue * (5.0 / 1023.0);

      //     bleGamepad.setBatteryLevel(bl);
      //     oldBatteryLevel = bl; 
      //   })

      //   batteryCount = 0;

      //   batteryLevel = 0;
      // }
      // else{
      //   batteryLevel = batteryLevel + analogRead(batteryPin);

      //   batteryCount = batteryCount+1;
      // }

      bool buttonState;
      coreCurrtouched = coreCap.touched();
      // dpCurrtouched = dpCap.touched();
      
      for(int i = 0; i < numButtons; i++){ //Set button values, subtract 4 for the capacitive touch buttons
        if(i < 2){
          buttonState = digitalRead(buttons[i]); //Normal Buttons    
        }
        else if(i >=2 && i < 11){ //core 8 buttons
          buttonState = coreCurrtouched & _BV(buttons[i]); //Core 8 Capacitive Buttons
        }
        // else{
        //   buttonState = dpCurrtouched & _BV(buttons[i]); //DPad Capacitive Buttons
        // }

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

      // Serial.print("rightX: ");
      // Serial.print(rightX);
      // Serial.print(", rightY: ");
      // Serial.println(rightY);
    }
}
