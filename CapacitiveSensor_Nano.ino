#include <CapacitiveSensor.h>
CapacitiveSensor Sensor = CapacitiveSensor(4, 6);
//CapacitiveSensor Sensor2 = CapacitiveSensor(4, 5);
//CapacitiveSensor Sensor3 = CapacitiveSensor(4, 7);
long val;
// val 2, val 3 if u have other sensors 
int pos;

#define led 13

void setup()
{
Serial.begin(9600);
pinMode(led, OUTPUT);
}

void loop()
{

val = Sensor.capacitiveSensor(30);
Serial.println(val);
if (val >= 1000 && pos == 0)
{
digitalWrite(led, HIGH);
pos = 1;
delay(500);
}

else if (val >= 1000 && pos == 1)
{
digitalWrite(led, LOW);
pos = 0;
delay(500);
}

delay(10);
}
