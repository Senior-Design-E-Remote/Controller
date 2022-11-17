#define slide A0
#define led 6

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(slide,INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int slideVal = analogRead(slide);
  int ledVal = map(slideVal, 0 , 1024, 0, 255);
  Serial.print("Slide val: ");
  Serial.println(slideVal);
  analogWrite(led, ledVal);
}
