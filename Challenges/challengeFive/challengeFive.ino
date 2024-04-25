/*
motorControl.ino
Alex, Jane, Selasie, and Supriti
April 25th, 2024

EE31 Challenge 5
*/

//motor one
const int motorAPin1 = 9;
const int motorAPin2 = 10;
const int enableAPin1 = 11;

//motor two
const int motorBPin1 = 5;
const int motorBPin2 = 6;
const int enableBPin1 = 3;


void setup() {
  
  pinMode(motorAPin1, OUTPUT);
  pinMode(motorAPin2, OUTPUT);
  pinMode(enableAPin1, OUTPUT);

  pinMode(motorBPin1, OUTPUT);
  pinMode(motorBPin2, OUTPUT);
  pinMode(enableBPin1, OUTPUT);

}

void loop() {
  //move forward 25 inches
  forwardDirection();
  delay(1600);

  //Stop
  stopMotor();
  delay(1000);
}


/*
 * name:      forwardDirection
 * purpose:   move the motor
 * arguments: motor speed
 * returns:   None (void)
 * effects: moves the motor forward
 */
void forwardDirection() {
  analogWrite(motorAPin1, 150);
  digitalWrite(motorAPin2, LOW);

  digitalWrite(motorBPin1, LOW);
  analogWrite(motorBPin2, 150);

  digitalWrite(enableAPin1, HIGH); // Set speed (0 to 255)
  digitalWrite(enableBPin1, HIGH);
}


/*
 * name:      stopMotor
 * purpose:   stop the motor
 * arguments: None
 * returns:   None (void)
 */
void stopMotor() {
  //stop motor A
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, LOW);

  //stop motor B
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, LOW);
}
