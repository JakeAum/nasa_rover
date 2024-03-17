// Code to read ultrasonic array

// Ultrasonic Array Pin Assignments
// NOTE: Consult truth table in Jake's Notebook,  4 is the front facing sensor
const int trig1 =  12;
const int echo1 =  13;

const int trig2 =  10;
const int echo2 =  11;

const int trig3 =  8;
const int echo3 =  9;

const int trig4 =  6;
const int echo4 =  7;

const int trig5 =  4;
const int echo5 =  5;

const int trig6 =  2;
const int echo6 =  3;

const int trig7 =  23;
const int echo7 =  22;

// Led Array
const int led1 =  52;
const int led2 =  50;
const int led3 =  48;
 
// Variables
int dist1, dist2, dist3, dist4, dist5, dist6, dist7;

//Sensing
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

int sensorScan() {
  // loop through all sensors and read distance
  int dist1 = readUltrasonicSensor(trig1, echo1);
  int dist5 = readUltrasonicSensor(trig5, echo5);

  int dist2 = readUltrasonicSensor(trig2, echo2);
  int dist6 = readUltrasonicSensor(trig6, echo6);

  int dist3 = readUltrasonicSensor(trig3, echo3);
  int dist7 = readUltrasonicSensor(trig7, echo7);

  int dist4 = readUltrasonicSensor(trig4, echo4);

  // print data to serial monitor for python visualizer script
  // Serial.print(dist1);
  // Serial.print(" ");
  // Serial.print(dist2);
  // Serial.print(" ");
  // Serial.print(dist3);
  // Serial.print(" ");
  // Serial.print(dist4);
  // Serial.print(" ");
  // Serial.print(dist5);
  // Serial.print(" ");
  // Serial.print(dist6);
  // Serial.print(" ");
  // Serial.print(dist7);
  // Serial.println();

  int front = round((dist3+dist4+dist5)/3);
  int left = int((dist1+dist2+dist3)/3);
  int right = int((dist5+dist6+dist7)/3);
  
  Serial.print(front);
  Serial.print(" ");
  Serial.print(left);
  Serial.print(" ");
  Serial.print(right);
  Serial.println();

  return front,left,right;
}



int calcSteering(int left, int right) {
  int turn = 0;
  // NOTE: Eventually will be some range or gradient to control velocity and direction

  // // check if there is an obstacle in front of the rover
  
  // if (front < 50) {
  //   stop = 1;
  // } else {
  //   stop = 0;
  // }  

  // check if one side is obstructed
  
 

  if (left > right) {
    turn = 1;
  } else if (right > left) {
    turn = 2;
  } else {
    turn = 0;
  }
  Serial.print(" ");
  Serial.println(turn);
  // NOTE: also want to add a bias counter that in the micro can keep track of if it has strayed too far in one direction, assuming linear course
  return turn;
}


void ledBar (int num) {
 if (num = 1) {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
 }
 else if (num = 2) {
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);

 }
 else if (num = 3) {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
 }
}

// Arduino
void setup() {
  // Ultrasonic Sensor
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

  // Led Array
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);


  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);


  // Serial Monitor
  Serial.begin(9600);
}

void loop() {
  int f,l,r;
  f,l,r = sensorScan();
  
  int tokyoDrift = calcSteering(l,r);
  ledBar(tokyoDrift);


}