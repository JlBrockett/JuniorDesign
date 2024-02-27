/*
motorControl.ino
Alex, Jane, Selasie, and Supriti
February 16th, 2024

EE31 Phase 2A
*/

const int motorPin1 = 5;
const int motorPin2 = 6;
const int enablePin1 = 3;

static unsigned long controlMillis = millis();


void setup() {
  
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin1, OUTPUT);

}

void loop() {

  if (millis() - controlMillis < 5000) {
    forwardDirection();
  }
  else if (millis() - controlMillis > 5000 and millis() - controlMillis < 7000) {
    stopMotor();
  }
  else if (millis() - controlMillis > 7000 and millis() - controlMillis < 12000) {
    reverseDirection();
  }
  else if (millis() - controlMillis > 12000) {
    controlMillis = millis();
  }

}


/*
 * name:      forwardDirection
 * purpose:   move the motor
 * arguments: None
 * returns:   None (void)
 * effects: moves the motor forward
 */
void forwardDirection() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin1, 255); // Set speed (0 to 255)
  // delay(2000); // Run for 2 seconds
}


/*
 * name:      reverseDirection
 * purpose:   move the motor
 * arguments: None
 * returns:   None (void)
 * effects: moves the motor backward
 */
void reverseDirection() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  analogWrite(enablePin1, 255); // Set speed (0 to 255)
  // delay(2000); // Run for 2 seconds
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
}
