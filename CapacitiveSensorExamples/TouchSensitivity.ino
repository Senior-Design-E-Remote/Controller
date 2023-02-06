#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif


const int led = A2;
const int slide = A1;
uint16_t currtouched = 0;
Adafruit_MPR121 cap = Adafruit_MPR121();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(slide,INPUT);
  pinMode(led, OUTPUT);
  
  cap.begin(0x5A);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t t = 12;
uint8_t r = 6;

  // cap.writeRegister(MPR121_ECR,0x00);
  // while(cap.readRegister16(MPR121_ECR) != 0x00){
  //   Serial.println("Not Stopped");
  // }
  // Serial.println("Now I'm Stopped");

  cap.setThreshholds(t,r); //default 12,6
  Serial.println("Starting delay");
  delay(1000);
  Serial.println("ending Delay");
  // cap.writeRegister(MPR121_ECR,0x8F);  
  
  
  
  int slideVal = analogRead(slide);
  // Serial.print("Slide val: ");
  // Serial.println(slideVal);

  currtouched = cap.touched();
  bool buttonState = currtouched & _BV(1); //Capacitive Buttons
  //  int ledVal = map(slideVal, 0 , 1024, 0, 255);
  // analogWrite(led, ledVal);
  digitalWrite(led, buttonState);

  Serial.println(buttonState);

  //   uint16_t x = cap.readRegister8(MPR121_TOUCHTH_0 + 2 * 0);
  //   Serial.print("Reg value: ");
  //   Serial.println(x);

  // Serial.println("");
  // Serial.println("");  
}
