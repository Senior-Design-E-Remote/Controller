const int buttonPin1 = 1;
const int buttonPin2 = 2;
const int buttonPin3 = 3;
const int buttonPin4 = 4;
const int buttonPin5 = 5;
const int buttonPin6 = 6;
const int buttonPin7 = 7;
const int buttonPin8 = 8;

const int ledPin1 =  9;
const int ledPin2 =  10;
const int ledPin3 =  11;
const int ledPin4 =  12;
const int ledPin5 =  13;
const int ledPin6 =  A0;
const int ledPin7 =  A1;
const int ledPin8 =  A2;

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int buttonState5 = 0;
int buttonState6 = 0;
int buttonState7 = 0;
int buttonState8 = 0;


void setup()
{
  pinMode(ledPin1, OUTPUT); 
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT); 
  pinMode(ledPin6, OUTPUT);
  pinMode(ledPin7, OUTPUT);
  pinMode(ledPin8, OUTPUT);
  
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin5, INPUT);
  pinMode(buttonPin6, INPUT);
  pinMode(buttonPin7, INPUT);
  pinMode(buttonPin8, INPUT);
}

void loop()
{
  buttonState1 = digitalRead(buttonPin1);
  if (buttonState1 == HIGH)
  {
    digitalWrite(ledPin1, HIGH);
  }  
  else
  {
    digitalWrite(ledPin1, LOW);
  }

   
  buttonState2 = digitalRead(buttonPin2);
    if (buttonState2 == HIGH)
  {
    digitalWrite(ledPin2, HIGH);
  } 
  else
  {
    digitalWrite(ledPin2, LOW);
  }

  
  buttonState3 = digitalRead(buttonPin3);
  if (buttonState3 == HIGH)
  {
    digitalWrite(ledPin3, HIGH);
  } 
  else
  {
    digitalWrite(ledPin3, LOW);
  }

  
  buttonState4 = digitalRead(buttonPin4);
  if (buttonState4 == HIGH)
  {
    digitalWrite(ledPin4, HIGH);
  } 
  else
  {
    digitalWrite(ledPin4, LOW);
  }

  buttonState5 = digitalRead(buttonPin5);
  if (buttonState5 == HIGH)
  {
    digitalWrite(ledPin5, HIGH);
  } 
  else
  {
    digitalWrite(ledPin5, LOW);
  }

  
  buttonState6 = digitalRead(buttonPin6);
  if (buttonState6 == HIGH)
  {
    digitalWrite(ledPin6, HIGH);
  } 
  else
  {
    digitalWrite(ledPin6, LOW);
  }

  
  buttonState7 = digitalRead(buttonPin7);
      if (buttonState7 == HIGH)
  {
    digitalWrite(ledPin7, HIGH);
  } 
  else
  {
    digitalWrite(ledPin7, LOW);
  }

  
  buttonState8 = digitalRead(buttonPin8);
  if (buttonState8 == HIGH)
  {
    digitalWrite(ledPin8, HIGH);
  } 
  else
  {
    digitalWrite(ledPin8, LOW);
  }

 /*
 // Turn on LED 1 if button 1 or button 2 are pressed 
  if (buttonState1 == HIGH || buttonState2 == HIGH)
  {
    digitalWrite(ledPin1, HIGH);
  } 
  else
  {
    digitalWrite(ledPin1, LOW);
  }

// Turn on LED 2 if button 3 or button 4 are pressed 
  if (buttonState3 == HIGH || buttonState4 == HIGH)
  {
    digitalWrite(ledPin2, HIGH);
  } 
  else
  {
    digitalWrite(ledPin2, LOW);
  }

// Turn on LED 3 if button 5 or button 6 are pressed 
  if (buttonState5 == HIGH || buttonState6 == HIGH)
  {
    digitalWrite(ledPin23 HIGH);
  } 
  else
  {
    digitalWrite(ledPin3, LOW);
  }

// Turn on LED 4 if button 7 or button 8 are pressed 
  if (buttonState7 == HIGH || buttonState8 == HIGH)
  {
    digitalWrite(ledPin4, HIGH);
  } 
  else
  {
    digitalWrite(ledPin4, LOW);
  }*/
  
  
}
