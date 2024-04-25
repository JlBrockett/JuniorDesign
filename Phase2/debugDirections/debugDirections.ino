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

volatile bool dir = true;

int motorSpeed = 255;


void setup() {
  
  pinMode(motorAPin1, OUTPUT);
  pinMode(motorAPin2, OUTPUT);
  pinMode(enableAPin1, OUTPUT);

  pinMode(motorBPin1, OUTPUT);
  pinMode(motorBPin2, OUTPUT);
  pinMode(enableBPin1, OUTPUT);

}

void loop() {
  // motorSpeed = analogRead(A1);
  // motorSpeed = map(motorSpeed, 0, 1023, 0, 255);
  // if (motorSpeed < 10) motorSpeed = 0;

  





  //move forward twelve inches
  forwardDirection(motorSpeed);
  delay(1600);

  //Stop
  stopMotor();
  delay(1000);

  //turn around 180°
  turn();
  delay(1160);

  //stop, move backwards three inches
  stopMotor();
  delay(1000);
  reverseDirection(motorSpeed);
  delay(800);

  //stop, turn left, turn right, turn right, and turn right to end up as close as possible to the  bot’s starting position.
  stopMotor();
  delay(1000);

  turn();
  delay(580);

  stopMotor();
  delay(1000);

  turnRight();
  delay(580);

  stopMotor();
  delay(1000);

  turnRight();
  delay(580);

  stopMotor();
  delay(1000);

  turnRight();
  delay(580);

  stopMotor();
  delay(1000);

  reverseDirection(motorSpeed);
  delay(2000);



  stopMotor();
  delay(10000);
}


/*
 * name:      forwardDirection
 * purpose:   move the motor
 * arguments: motor speed
 * returns:   None (void)
 * effects: moves the motor forward
 */
void forwardDirection(int speed) {
  analogWrite(motorAPin1, 150);
  digitalWrite(motorAPin2, LOW);

  digitalWrite(motorBPin1, LOW);
  analogWrite(motorBPin2, 150);

  digitalWrite(enableAPin1, HIGH); // Set speed (0 to 255)
  digitalWrite(enableBPin1, HIGH);
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
  analogWrite(motorAPin2, 150);
  
  analogWrite(motorBPin1, 150);
  digitalWrite(motorBPin2, LOW);

  digitalWrite(enableAPin1, HIGH); //right min 130
  digitalWrite(enableBPin1, HIGH); // left
}

void turn() {
  analogWrite(motorAPin1, 150);
  digitalWrite(motorAPin2, LOW);
  digitalWrite(enableAPin1, HIGH); 

  analogWrite(motorBPin1, 150);
  digitalWrite(motorBPin2, LOW);
  digitalWrite(enableBPin1, HIGH);
}

void turnRight() {
  digitalWrite(motorAPin1, LOW);
  analogWrite(motorAPin2, 150);
  digitalWrite(enableAPin1, HIGH); 

  digitalWrite(motorBPin1, LOW);
  analogWrite(motorBPin2, 150);
  digitalWrite(enableBPin1, HIGH);
}

void stopOneMotor() {
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, LOW);

  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, HIGH);
  digitalWrite(enableBPin1, 255);
}

void variableSpeeds() {
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, HIGH);
  
  digitalWrite(motorBPin1, HIGH);
  digitalWrite(motorBPin2, LOW);

  analogWrite(enableAPin1, 255); //left
  analogWrite(enableBPin1, 130); //right
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

/*
 * name:      changeDirection
 * purpose:   toggle direction boolean
 * arguments: None
 * returns:   None (void)
 */
void changeDirection() {
  dir = !dir;
}
