// NASA Rover - Basic Movement Short Range Obstacle Avoidance 
// Jacob Auman and Kelli McGuire

// Rover Parameters
////////////////////////////////

  int speed = 125; // default throttle to the motors (0-255)
  float leftAdjust = 1.25; // (0-1)  Used to correct motor drift in a straight line
  float rightAdjust = 1; // (0-1)

  float turnSpeed = 0.5; // (0-1) Fraction of power that inner bank will recieve
  float adjustSpeed = 0.5;
  int turnTime = 500; // time in milliseconds for the rover to turn
  float reverseSpeed = 0.7; // (0-1)

  int avoidDist = 55; // distance that the rover will stop at
  float frontSensitivity = 1;
  float leftSensitivity = 1;
  float rightSensitivity = 1;

  int Hz = 1; // delay in milliseconds
  int actionTime = 1000; // time in milliseconds for the rover to take action

//Pin Declarations 
////////////////////////////////
  // Stop Start Button
  const int stopButton = 2; // GPIO

  // Motor FL
  const int motorFL1 = 36; // GPIO
  const int motorFL2 = 34; // GPIO
  const int motorFLP = 4; // PWM
  // Motor FR
  const int motorFR1 = 32; // GPIO
  const int motorFR2 = 30; // GPIO
  const int motorFRP = 5; // PWM
  // Motor ML
  const int motorML1 = 44; // GPIO
  const int motorML2 = 42; // GPIO
  const int motorMLP = 6; // PWM
  // Motor MR
  const int motorMR1 = 40; // GPIO
  const int motorMR2 = 38; // GPIO
  const int motorMRP = 7; // PWM
  // Motor BL
  const int motorBL1 = 52; // GPIO
  const int motorBL2 = 50; // GPIO
  const int motorBLP = 8; // PWM
  // Motor BR
  const int motorBR1 = 48; // GPIO
  const int motorBR2 = 46; // GPIO
  const int motorBRP = 9; // PWM

  // Ultrasonic Array Pin Assignments
  const int trig1 =  25;
  const int echo1 =  23;
  const int trig2 =  29;
  const int echo2 =  27;
  const int trig3 =  33;
  const int echo3 =  31;
  const int trig4 =  37;
  const int echo4 =  35;
  const int trig5 =  41;
  const int echo5 =  39;
  const int trig6 =  45;
  const int echo6 =  43;
  const int trig7 =  49;
  const int echo7 =  47;
  
  // Initialize Variables
  int dist1, dist2, dist3, dist4, dist5, dist6, dist7;
  volatile bool driveState = false; 

// Functions
////////////////////////////////

// W
int readUltrasonicSensor(int trigPin, int echoPin) {
  // function to read ultrasonic sensor and return distance in CM
  int duration, distance;
  // Clear trigPin
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Initiate trigPin reading
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance the speed of sound in air is approximately 343 meters per second (or 0.034 centimeters per microsecond). The division by 2 is necessary because the sound wave travels to the target and then back to the source.
  distance = duration * 0.034 / 2; 
  return distance;
}
// W
int scanFront() {
  int dist3 = readUltrasonicSensor(trig3, echo3);
  int dist4 = readUltrasonicSensor(trig4, echo4);
  int dist5 = readUltrasonicSensor(trig5, echo5);

  // Serial Statment For Debugging
  // Serial.print(dist3);
  // Serial.print(" ");
  // Serial.print(dist4);
  // Serial.print(" ");
  // Serial.print(dist5);
  // Serial.print(" ");
  
  int front = int((dist3+dist4+dist5)/3);
  return front;
} 
// W
int scanLeft() {
  int dist1 = readUltrasonicSensor(trig1, echo1);
  int dist2 = readUltrasonicSensor(trig2, echo2);
  int dist3 = readUltrasonicSensor(trig3, echo3);

  // Serial Statment For Debugging
  // Serial.print(dist1);
  // Serial.print(" ");
  // Serial.print(dist2);
  // Serial.print(" ");
  // Serial.print(dist3);
  // Serial.print(" ");

  int left = int((dist2+dist3)/2);
  return left;
}
// W
int scanRight() {
  int dist5 = readUltrasonicSensor(trig5, echo5);
  int dist6 = readUltrasonicSensor(trig6, echo6);
  int dist7 = readUltrasonicSensor(trig7, echo7);

  // Serial Statment For Debugging
  // Serial.print(dist5);
  // Serial.print(" ");
  // Serial.print(dist6);
  // Serial.print(" ");
  // Serial.println(dist7);

  int right = int((dist5+dist6)/2);
  return right;
}
//W
void driveStop(){
  digitalWrite(motorFL1, LOW);
  digitalWrite(motorFL2, LOW);
  analogWrite(motorFLP, 0);

  digitalWrite(motorFR1, LOW);
  digitalWrite(motorFR2, LOW);
  analogWrite(motorFRP, 0);

  digitalWrite(motorML1, LOW);
  digitalWrite(motorML2, LOW);
  analogWrite(motorMLP, 0);

  digitalWrite(motorMR1, LOW);
  digitalWrite(motorMR2, LOW);
  analogWrite(motorMRP, 0);

  digitalWrite(motorBL1, LOW);
  digitalWrite(motorBL2, LOW);
  analogWrite(motorBLP, 0);

  digitalWrite(motorBR1, LOW);
  digitalWrite(motorBR2, LOW);
  analogWrite(motorBRP, 0);
};
//W
void driveForward(){
  digitalWrite(motorFL1, HIGH);
  digitalWrite(motorFL2, LOW);
  analogWrite(motorFLP, speed*leftAdjust);

  digitalWrite(motorFR1, HIGH);
  digitalWrite(motorFR2, LOW);
  analogWrite(motorFRP, speed*rightAdjust);

  digitalWrite(motorML1, HIGH);
  digitalWrite(motorML2, LOW);
  analogWrite(motorMLP, speed*leftAdjust);

  digitalWrite(motorMR1, HIGH);
  digitalWrite(motorMR2, LOW);
  analogWrite(motorMRP, speed*rightAdjust);

  digitalWrite(motorBL1, HIGH);
  digitalWrite(motorBL2, LOW);
  analogWrite(motorBLP, speed*leftAdjust);

  digitalWrite(motorBR1, HIGH);
  digitalWrite(motorBR2, LOW);
  analogWrite(motorBRP, speed*rightAdjust);
};
//W
void driveBackward(){
  digitalWrite(motorFL1, LOW);
  digitalWrite(motorFL2, HIGH);
  analogWrite(motorFLP, (speed*leftAdjust)*reverseSpeed);

  digitalWrite(motorFR1, LOW);
  digitalWrite(motorFR2, HIGH);
  analogWrite(motorFRP, (speed*rightAdjust)*reverseSpeed);

  digitalWrite(motorML1, LOW);
  digitalWrite(motorML2, HIGH);
  analogWrite(motorMLP, (speed*leftAdjust)*reverseSpeed);

  digitalWrite(motorMR1, LOW);
  digitalWrite(motorMR2, HIGH);
  analogWrite(motorMRP, (speed*rightAdjust)*reverseSpeed);

  digitalWrite(motorBL1, LOW);
  digitalWrite(motorBL2, HIGH);
  analogWrite(motorBLP, (speed*leftAdjust)*reverseSpeed);

  digitalWrite(motorBR1, LOW);
  digitalWrite(motorBR2, HIGH);
  analogWrite(motorBRP, (speed*rightAdjust)*reverseSpeed);
  
};
// NTT
void turnLeft(){
  digitalWrite(motorFL1, LOW);
  digitalWrite(motorFL2, HIGH);
  analogWrite(motorFLP, (speed*leftAdjust)*turnSpeed);

  digitalWrite(motorFR1, HIGH);
  digitalWrite(motorFR2, LOW);
  analogWrite(motorFRP, (speed*rightAdjust)*turnSpeed);

  digitalWrite(motorML1, LOW);
  digitalWrite(motorML2, HIGH);
  analogWrite(motorMLP, (speed*leftAdjust)*turnSpeed);

  digitalWrite(motorMR1, HIGH);
  digitalWrite(motorMR2, LOW);
  analogWrite(motorMRP, (speed*rightAdjust)*turnSpeed);

  digitalWrite(motorBL1, LOW);
  digitalWrite(motorBL2, HIGH);
  analogWrite(motorBLP, (speed*leftAdjust)*turnSpeed);

  digitalWrite(motorBR1, HIGH);
  digitalWrite(motorBR2, LOW);
  analogWrite(motorBRP, (speed*rightAdjust)*turnSpeed);
};
// NTT
void turnRight(){
  digitalWrite(motorFL1, HIGH);
  digitalWrite(motorFL2, LOW);
  analogWrite(motorFLP, speed*leftAdjust);

  digitalWrite(motorFR1, HIGH);
  digitalWrite(motorFR2, LOW);
  analogWrite(motorFRP, (speed*rightAdjust)*turnSpeed);

  digitalWrite(motorML1, HIGH);
  digitalWrite(motorML2, LOW);
  analogWrite(motorMLP, speed*leftAdjust);

  digitalWrite(motorMR1, HIGH);
  digitalWrite(motorMR2, LOW);
  analogWrite(motorMRP, (speed*rightAdjust)*turnSpeed);

  digitalWrite(motorBL1, HIGH);
  digitalWrite(motorBL2, LOW);
  analogWrite(motorBLP, speed*leftAdjust);

  digitalWrite(motorBR1, HIGH);
  digitalWrite(motorBR2, LOW);
  analogWrite(motorBRP, (speed*rightAdjust)*turnSpeed);
};
// DNE
void bigBrain(int frontReading, int leftReading, int rightReading) {

  // Check Front For Immediate Collision
  if (frontReading < avoidDist) {
    Serial.println("Front Collision");

    driveStop();
    delay(actionTime);
    // adjust direction
      if (leftReading > rightReading) {
        turnRight();
        delay(turnTime*adjustSpeed);
      } else {
        turnLeft();
        delay(turnTime*adjustSpeed);
      }
  } else if (leftReading < avoidDist) {
    Serial.println("Left Collision");
    driveStop();
    delay(actionTime);
    turnRight();
    delay(turnTime);
      
  } else if (rightReading < avoidDist) {
    Serial.println("Right Collision");
    driveStop();
    delay(actionTime);
    turnLeft();
    delay(turnTime);
    
  } else {
    // Slight Steering Adjustments
    if (leftReading > rightReading) {
      Serial.println("Left Adjust");
      turnLeft();
      delay(turnTime);
    } else if (rightReading > leftReading) {
      Serial.println("Right Adjust");
      turnRight();
      delay(turnTime);
    } else {
      Serial.println("Continue Forward");
      driveForward();
      delay(actionTime);
    }  
  }
};

// W
void stopButtonInterrupt() {
  static unsigned long lastDebounceTime = 0;
  unsigned long debounceDelay = 15; // Adjust this value to reduce debounce effect

  // Check if enough time has passed since the last button press
  if (millis() - lastDebounceTime > debounceDelay) {
    // Toggle state 
    if (driveState == false) {
      driveState = true;
      Serial.println("Drive");
    } else {
      driveState = false;
      driveStop();
      Serial.println("Stop");
    }
    lastDebounceTime = millis(); // Update the last debounce time
  }
};

// Arduino Main Functions
////////////////////////////////

void setup() {
  // Serial Monitor
  Serial.begin(115200);
  Serial.println("Hello World");

  // Stop Button
  pinMode(stopButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(stopButton), stopButtonInterrupt, FALLING);

  // Ultrasonic Sensors
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);
  pinMode(trig4, OUTPUT);
  pinMode(echo4, INPUT);
  pinMode(trig5, OUTPUT);
  pinMode(echo5, INPUT);
  pinMode(trig6, OUTPUT);
  pinMode(echo6, INPUT);
  pinMode(trig7, OUTPUT);
  pinMode(echo7, INPUT);

  // Motor Pins
  pinMode(motorFL1, OUTPUT);
  pinMode(motorFL2, OUTPUT);
  pinMode(motorFLP, OUTPUT);
  pinMode(motorFR1, OUTPUT);
  pinMode(motorFR2, OUTPUT);
  pinMode(motorFRP, OUTPUT);
  pinMode(motorML1, OUTPUT);
  pinMode(motorML2, OUTPUT);
  pinMode(motorMLP, OUTPUT);
  pinMode(motorMR1, OUTPUT);
  pinMode(motorMR2, OUTPUT);
  pinMode(motorMRP, OUTPUT);
  pinMode(motorBL1, OUTPUT);
  pinMode(motorBL2, OUTPUT);
  pinMode(motorBLP, OUTPUT);
  pinMode(motorBR1, OUTPUT);
  pinMode(motorBR2, OUTPUT);
  pinMode(motorBRP, OUTPUT);

  // Initialize Motors - Forward
  digitalWrite(motorFL1, HIGH);
  digitalWrite(motorFL2, LOW);

  digitalWrite(motorFR1, HIGH);
  digitalWrite(motorFR2, LOW);

  digitalWrite(motorML1, HIGH);
  digitalWrite(motorML2, LOW);

  digitalWrite(motorMR1, HIGH);
  digitalWrite(motorMR2, LOW);

  digitalWrite(motorBL1, HIGH);
  digitalWrite(motorBL2, LOW);

  digitalWrite(motorBR1, HIGH);
  digitalWrite(motorBR2, LOW);

  Serial.println("Goodbye World");
}

void loop() {
  // Check the driveState
  if (driveState == true) {
    
    // Read the sensors
    int frontReading = scanFront();
    int leftReading = scanLeft();
    int rightReading = scanRight();

    // Serial Statment For Debugging
    Serial.print(leftReading);
    Serial.print(" ");
    Serial.print(frontReading);
    Serial.print(" ");
    Serial.println(rightReading);  

    // Make a decision
    //bigBrain(frontReading, leftReading, rightReading);
    turnLeft();
    delay(turnTime);

  } else {
    driveStop();

    // Read the sensors
    int frontReading = scanFront();
    int leftReading = scanLeft();
    int rightReading = scanRight();

    // Serial Statement For Debugging
    Serial.print(leftReading);
    Serial.print(" ");
    Serial.print(frontReading);
    Serial.print(" ");
    Serial.println(rightReading);
  }

  delay(Hz); // delay to prevent overloading microcontroller
}