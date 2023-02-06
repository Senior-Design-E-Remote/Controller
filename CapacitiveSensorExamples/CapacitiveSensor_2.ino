#include <CapacitiveSensor.h>
/*
 * Uses a high value resistor e.g. 1M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_4_3 = CapacitiveSensor(4,3);      
CapacitiveSensor   cs_4_5 = CapacitiveSensor(4,5);        
CapacitiveSensor   cs_4_6 = CapacitiveSensor(4,6); 

#define led_red 12
#define led_green 11
#define led_yellow 10
#define led_blue 9

void setup()                    
{
   Serial.begin(9600);
   pinMode(led_red, OUTPUT);
   pinMode(led_green, OUTPUT);
   pinMode(led_yellow, OUTPUT);
   pinMode(led_blue, OUTPUT);
}

void loop()                    
{
    long start = millis();
    long total1 =  cs_4_2.capacitiveSensor(30);
    long total2 =  cs_4_3.capacitiveSensor(30);
    long total3 =  cs_4_5.capacitiveSensor(30);
    long total4 =  cs_4_6.capacitiveSensor(30);
    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing

    Serial.println(total1);
    Serial.print("\t"); // print sensor output 1
    Serial.println(total2); 
    Serial.print("\t"); 
    Serial.println(total3);
    Serial.print("\t"); 
    Serial.println(total4);
    Serial.print("\t"); 

  // Red LED 
    if (total1 >= 1000)
    {
      digitalWrite(led_red, HIGH);
      delay(100);
    }
    else if (total1 <= 1000)
    {
      digitalWrite(led_red, LOW);
      delay(100);
    }

 // Green LED
    if (total2 >= 1000)
    {
      digitalWrite(led_green, HIGH);
      delay(100);
    }
    else if (total2 <= 1000)
    {
      digitalWrite(led_green, LOW);
      delay(100);
    }

// Yellow LED
    if (total3 >= 1000)
    {
      digitalWrite(led_yellow, HIGH);
      delay(100);
    }
    else if (total3 <= 1000)
    {
      digitalWrite(led_yellow, LOW);
      delay(100);
    }
     
// Blue  LED
    if (total4 >= 1000)
    {
      digitalWrite(led_blue, HIGH);
      delay(100);
    }
    else if (total4 <= 1000)
    {
      digitalWrite(led_blue, LOW);
      delay(100);
    }

    delay(10);                             // arbitrary delay to limit data to serial port 
}
