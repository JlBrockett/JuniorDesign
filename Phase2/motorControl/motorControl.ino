const int motorPin1 = 3;
const int motorPin2 = 4;
const int enablePin1 = 9;


void setup() {
  
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin1, OUTPUT);

}

void loop() {
  
  // Spin motor in one direction
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin1, 127); // Set speed (0 to 255)
  delay(2000); // Run for 2 seconds
  
  // Stop motor
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  delay(1000); // Stop for 1 second
  
  // Spin motor in opposite direction
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  analogWrite(enablePin1, 127); // Set speed (0 to 255)
  delay(2000); // Run for 2 seconds
  
  // Stop motor
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  delay(1000); // Stop for 1 second

}
