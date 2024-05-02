//motor one
const int motorAPin1 = 10; //left
const int motorAPin2 = 9;
const int enableAPin1 = 11;

//motor two
const int motorBPin1 = 5; //right
const int motorBPin2 = 6;
const int enableBPin1 = 3;

void setup() {
  pinMode(motorAPin1, OUTPUT);
  pinMode(motorAPin2, OUTPUT);
  pinMode(enableAPin1, OUTPUT);

  pinMode(motorBPin1, OUTPUT);
  pinMode(motorBPin2, OUTPUT);
  pinMode(enableBPin1, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  forwardDirection();
  delay(250);
  stopMotor();
  delay(500);
}



void forwardDirection() {
  analogWrite(motorAPin1, 120);
  digitalWrite(motorAPin2, LOW);

  digitalWrite(motorBPin1, LOW);
  analogWrite(motorBPin2, 120);

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
void reverseDirection() {
  digitalWrite(motorAPin1, LOW);
  analogWrite(motorAPin2, 110);
  
  analogWrite(motorBPin1, 100);
  digitalWrite(motorBPin2, LOW);

  digitalWrite(enableAPin1, HIGH); //right min 130
  digitalWrite(enableBPin1, HIGH); // left
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
