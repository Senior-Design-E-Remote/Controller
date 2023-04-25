#include <XInput.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

const int LeftJoyXPin = A3;
const int LeftJoyYPin = A4;
const int LeftJoyPushPin = 15;

const int RightJoyXPin = A0;
const int RightJoyYPin = A1;
const int RightJoyPushPin = A5;

const int led1 = 9;
const int led2 = 10;
const int led3 = 11;
const int led4 = 12;
const int led5 = 13;
const int led6 = 1;
const int led7 = 17;
const int led8 = 16;

int touchInputs[8] = {0,0,0,0,0,0,0,0};

uint16_t currtouched = 0;
Adafruit_MPR121 cap = Adafruit_MPR121();

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);

  while(!cap.begin(0x5A)){
    digitalWrite(LED_BUILTIN, 1);
  }

  digitalWrite(LED_BUILTIN, 0); 

  XInput.begin();
}

void loop() {
  currtouched = cap.touched();
  boolean LeftJoyPushState = currtouched & _BV(0);
  for(uint8_t i = 0;i < 12;i++){
    touchInputs[i] = currtouched & _BV(i);
  }
  
  boolean StartState = touchInputs[0];
	XInput.setButton(BUTTON_A, StartState);   // press Start conditionally
  digitalWrite(led1, StartState);

  boolean SelectState = touchInputs[1];
	XInput.setButton(BUTTON_X, SelectState);   // press Select conditionally
  digitalWrite(led2, SelectState);

	boolean AState = touchInputs[2];
	XInput.setButton(BUTTON_B, AState);   // press A conditionally
  digitalWrite(led3, AState);

  boolean XState = touchInputs[3];
	XInput.setButton(BUTTON_Y, XState);   // press X conditionally
  digitalWrite(led4, XState);

  boolean YState = touchInputs[4];
	XInput.setButton(DPAD_UP, YState);   // press Y conditionally
  digitalWrite(led5, YState);

  boolean BState = touchInputs[5];
	XInput.setButton(DPAD_DOWN, BState);   // press B conditionally
  digitalWrite(led6, BState);

  boolean RBState = touchInputs[6];
	XInput.setButton(DPAD_LEFT, RBState);   // press RB conditionally
  digitalWrite(led7, RBState);

  boolean LBState = touchInputs[7];
	XInput.setButton(DPAD_RIGHT, LBState);   // press LB conditionally
  digitalWrite(led8, LBState);

  XInput.setRange(JOY_LEFT, 0, 1023);  // using analogRead (10-bit ADC)
  XInput.setRange(JOY_RIGHT, 0, 1023);  // using analogRead (10-bit ADC)
  pinMode(LeftJoyPushPin, INPUT_PULLUP);
  pinMode(RightJoyPushPin, INPUT_PULLUP);

  int LeftJoyXState = analogRead(LeftJoyXPin);
  int LeftJoyYState = analogRead(LeftJoyYPin);
  XInput.setJoystickX(JOY_LEFT, LeftJoyYState, true);
  XInput.setJoystickY(JOY_LEFT, LeftJoyXState, true); //Y axis needed to be inverted for correct positioning

  boolean LeftJoyPushState = !digitalRead(LeftJoyPushPin);
  XInput.setButton(TRIGGER_LEFT, LeftJoyPushState);   // press L3 Right conditionally

  int RightJoyXState = analogRead(RightJoyXPin);
  int RightJoyYState = analogRead(RightJoyYPin);
  XInput.setJoystickX(JOY_RIGHT, RightJoyXState, false);
  XInput.setJoystickY(JOY_RIGHT, RightJoyYState, true); //Y axis needed to be inverted for correct positioning

  boolean RightJoyPushState = !digitalRead(RightJoyPushPin);
  XInput.setButton(TRIGGER_RIGHT, RightJoyPushState);   // press L3 Right conditionally
}
