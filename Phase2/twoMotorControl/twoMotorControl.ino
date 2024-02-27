/*
motorControl.ino
Alex, Jane, Selasie, and Supriti
February 16th, 2024

EE31 Phase 2A
*/

//motor one
const int motorAPin1 = 3;
const int motorAPin2 = 4;
const int enableAPin1 = 9;

//motor two
const int motorBPin1 = 5;
const int motorBPin2 = 6;
const int enableBPin1 = 10;

const int onSwitch = 7;
const int dirButton = 8;

volatile bool dir = true;


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
  
  // static unsigned long controlMillis = millis();

  // if (millis() - controlMillis > 0 and millis() - controlMillis < 20000) {
  //   directionOne();
  // }
  // else if (millis() - controlMillis > 20000 and millis() - controlMillis < 40000) {
  //   directionTwo();
  // }

  if (onSwitch == HIGH and dir == true) {
    directionOne();
  }
  else if (onSwitch == HIGH and dir == false) {
    directionTwo();
  }

}


/*
 * name:      directionOne
 * purpose:   move the motor
 * arguments: None
 * returns:   None (void)
 * effects: moves the motor forward
 */
void directionOne() {
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorAPin2, LOW);
  analogWrite(enableAPin1, 255); // Set speed (0 to 255)

  digitalWrite(motorBPin1, HIGH);
  digitalWrite(motorBPin2, LOW);
  analogWrite(enableBPin1, 255);
}


/*
 * name:      directionTwo
 * purpose:   move the motor
 * arguments: None
 * returns:   None (void)
 * effects: moves the motor backward
 */
void directionTwo() {
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, HIGH);
  analogWrite(enableAPin1, 255); // Set speed (0 to 255)

  digitalWrite(motorBPin1, Low);
  digitalWrite(motorBPin2, High);
  analogWrite(enableBPin1, 255);
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

void changeDirection() {
  dir = !dir;
}