// Test code to learn how to use a single slide potentiometer on an arduino uno and print the values in the serial monitor

// Libraries


// Pin Assignments
int potPinLeft = A5; // OTB
int potPinRight = A4; // OTB

// Variables
int potValueLeft = 0;
int potValueRight = 0;

void setup() {
  // Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // Read the potentiometer value
  potValueLeft = analogRead(potPinLeft);
  potValueRight = analogRead(potPinRight);

  // Print the potentiometer value
  Serial.print("Left: ");
  Serial.print(potValueLeft);
  Serial.print(" Right: ");
  Serial.println(potValueRight);
  delay(100);
}