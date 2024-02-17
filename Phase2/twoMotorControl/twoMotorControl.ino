/*
motorControl.ino
Alex, Jane, Selasie, and Supriti
February 16th, 2024

EE31 Phase 2A
*/

const int motorPin1 = 3;
const int motorPin2 = 4;
const int enablePin1 = 9;


void setup() {
  
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin1, OUTPUT);

}

void loop() {
  
  static unsigned long controlMillis = millis();

  if (millis() - controlMillis > 0 and millis() - controlMillis < 20000) {
    directionOne()
  }
  else if (millis() - controlMillis > 20000 and millis() - controlMillis < 40000)

}


/*
 * name:      directionOne
 * purpose:   move the motor
 * arguments: None
 * returns:   None (void)
 * effects: moves the motor forward
 */
void directionOne() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin1, 127); // Set speed (0 to 255)
  delay(2000); // Run for 2 seconds
}


/*
 * name:      directionTwo
 * purpose:   move the motor
 * arguments: None
 * returns:   None (void)
 * effects: moves the motor backward
 */
void directionTwo() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  analogWrite(enablePin1, 127); // Set speed (0 to 255)
  delay(2000); // Run for 2 seconds
}


/*
 * name:      stopMotor
 * purpose:   stop the motor
 * arguments: None
 * returns:   None (void)
 */
void stopMotor() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  delay(1000); // Stop for 1 second
}