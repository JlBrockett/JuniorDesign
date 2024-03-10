/*
motorControl.ino
Alex, Jane, Selasie, and Supriti
February 16th, 2024

EE31 Phase 2A
*/

/*
TODOS:
1. Turn left- sharp
2. Turn right- sharp
3. Turn 180*
4. Turn arbitary angle

modify speed
*/

//motor one
const int motorAPin1 = 9;
const int motorAPin2 = 10;
const int enableAPin1 = 11;

//motor two
const int motorBPin1 = 5;
const int motorBPin2 = 6;
const int enableBPin1 = 3;

const int onSwitch = 7;
const int dirButton = 8;

volatile bool dir = true;

int motorSpeed = 255;


void setup() {
  
  pinMode(motorAPin1, OUTPUT);
  pinMode(motorAPin2, OUTPUT);
  pinMode(enableAPin1, OUTPUT);

  pinMode(motorBPin1, OUTPUT);
  pinMode(motorBPin2, OUTPUT);
  pinMode(enableBPin1, OUTPUT);

  pinMode(onSwitch, INPUT_PULLUP);
  pinMode(dirButton, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(onSwitch), stopMotor, FALLING);
  attachInterrupt(digitalPinToInterrupt(dirButton), changeDirection, FALLING);

}

void loop() {
  motorSpeed = analogRead(A1);
  motorSpeed = map(motorSpeed, 0, 1023, 0, 255);
  if (motorSpeed < 10) motorSpeed = 0;

  forwardDirection(motorSpeed);

  // turn();
  // stopMotor();
}


/*
 * name:      forwardDirection
 * purpose:   move the motor
 * arguments: motor speed
 * returns:   None (void)
 * effects: moves the motor forward
 */
void forwardDirection(int speed) {
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorAPin2, LOW);
  
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, HIGH);

  analogWrite(enableAPin1, 150); // Set speed (0 to 255)
  analogWrite(enableBPin1, 150);
}


/*
 * name:      reverseDirection
 * purpose:   move the motor
 * arguments: motor speed
 * returns:   None (void)
 * effects: moves the motor backward
 */
void reverseDirection(int speed) {
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, HIGH);

  digitalWrite(motorBPin1, HIGH);
  digitalWrite(motorBPin2, LOW);

  analogWrite(enableAPin1, 150); // Set speed (0 to 255)
  analogWrite(enableBPin1, 200);
}

void turn() {
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorAPin2, LOW);
  analogWrite(enableAPin1, 150); 

  digitalWrite(motorBPin1, HIGH);
  digitalWrite(motorBPin2, LOW);
  analogWrite(enableBPin1, 150);

  delay(1280);
}


// /*
//  * name:      leftDirection --- more to do
//  * purpose:   move the motor left
//  * arguments: None
//  * returns:   None (void)
//  * effects: moves the motor forward
//  */
// void leftDirection() {
//   digitalWrite(motorAPin1, HIGH);
//   digitalWrite(motorAPin2, LOW);
//   analogWrite(enableAPin1, 255); // Set speed (0 to 255)

//   digitalWrite(motorBPin1, LOW);
//   digitalWrite(motorBPin2, HIGH);
//   analogWrite(enableBPin1, 100);
// }


// /*
//  * name:      rightDirection ---  more to do
//  * purpose:   move the motor right
//  * arguments: None
//  * returns:   None (void)
//  * effects: moves the motor forward
//  */
// void rightDirection() {
//   digitalWrite(motorAPin1, LOW);
//   digitalWrite(motorAPin2, HIGH);
//   analogWrite(enableAPin1, 100); // Set speed (0 to 255)

//   digitalWrite(motorBPin1, HIGH);
//   digitalWrite(motorBPin2, LOW);
//   analogWrite(enableBPin1, 255);
// }


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

/*
 * name:      changeDirection
 * purpose:   toggle direction boolean
 * arguments: None
 * returns:   None (void)
 */
void changeDirection() {
  dir = !dir;
}
