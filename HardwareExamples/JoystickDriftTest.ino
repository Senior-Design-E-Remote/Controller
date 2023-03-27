#define leftJoyX 14
#define leftJoyY 12
#define rightJoyX 26
#define rightJoyY 27 

void printAxesMaxMin(int leftX, int leftY, int rightX, int rightY){

  static bool firstRead = 1;

  static int maxLeftX = 0;
  static int maxLeftY = 0;
  static int maxRightX = 0;
  static int maxRightY = 0;

  static int minLeftX = 0;
  static int minLeftY = 0;
  static int minRightX = 0;
  static int minRightY = 0;

  if(firstRead){
    Serial.println("Printing Max and Min Values for the Axes");
    maxLeftX = leftX;
    maxLeftY = leftY;
    maxRightX = rightX;
    maxRightY = rightY;
    
    minLeftX = leftX;
    minLeftY = leftY;
    minRightX = rightX;
    minRightY = rightY;

    delay(5000);
    firstRead = 0;
  }
  else{
    if(leftX>maxLeftX){
      maxLeftX = leftX;
      Serial.print("maxLeftX: ");
      Serial.println(maxLeftX);
    }
    if(leftX<minLeftX){
      minLeftX = leftX;
      Serial.print("minLeftX: ");
      Serial.println(minLeftX);
    }
    
    if(leftY>maxLeftY){
      maxLeftY = leftY;
      Serial.print("maxLeftY: ");
      Serial.println(maxLeftY);
    }
    if(leftY<minLeftY){
      minLeftY = leftY;
      Serial.print("minLeftY: ");
      Serial.println(minLeftY);
    }

    if(rightX>maxRightX){
      maxRightX = rightX;
      Serial.print("maxRightX: ");
      Serial.println(maxRightX);
    }
    if(rightX<minRightX){
      minRightX = rightX;
      Serial.print("minRightX: ");
      Serial.println(minRightX);
    }

    if(rightY>maxRightY){
      maxRightY = rightY;
      Serial.print("maxRightY: ");
      Serial.println(maxRightY);
    }
    if(rightY<minRightY){
      minRightY = rightY;
      Serial.print("minRightY: ");
      Serial.println(minRightY);
    }
  }      
}

void setup() {
  Serial.begin(115200);
  delay(2000);
}

void loop() {
  
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

  //printAxesMaxMin(leftX, leftY, rightX, rightY);

  
}
