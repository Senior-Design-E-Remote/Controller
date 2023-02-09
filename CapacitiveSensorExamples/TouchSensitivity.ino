#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

const int led = 6;
uint16_t currtouched = 0;
Adafruit_MPR121 cap = Adafruit_MPR121();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  
  cap.begin(0x5A);
}

void loop() {
  // put your main code here, to run repeatedly:
  // uint8_t t = 12;
  // uint8_t r = 6;

  // cap.setThreshholds(t,r); //default 12,6  
  
  
  currtouched = cap.touched();
  bool buttonState = currtouched & _BV(1); //Capacitive Button

  digitalWrite(led,buttonState);

  // Serial.println(buttonState);

    uint16_t x = cap.readRegister8(MPR121_TOUCHTH_0 + 2 * 0);
    Serial.print("Threshold Val: ");
    Serial.println(x);

    int f = cap.filteredData(1);
    int b = cap.baselineData(1);

    Serial.print("Baseline: ");
    Serial.print(b);
    Serial.print(", Filtered: ");
    Serial.println(f);

  Serial.println("");
  Serial.println("");

  delay(1000);  
}
