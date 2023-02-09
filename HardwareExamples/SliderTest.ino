#define slide A0
#define led 6

int oldslide;

void setup() {
  //put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(slide,INPUT);
  pinMode(led, OUTPUT);
  oldslide = analogRead(slide);
  analogWrite(led,128);
}



void loop() {
  //put your main code here, to run repeatedly:
  int slideVal = analogRead(slide);
  int ledVal = map(slideVal, 0 , 1024, 0, 128);
  if(slideVal > (oldslide+5) || slideVal < (oldslide-5)){
    analogWrite(led, ledVal);
    oldslide = slideVal;
    Serial.print("Old Slide Changed to ");
    Serial.println(oldslide);
  }
  // digitlaWrite(led,1);
  // analogWrite(led,128);
}
