const int sensorPin = A0;

//motor one
const int motorAPin1 = 9;
const int motorAPin2 = 10;
const int enableAPin1 = 11;

//motor two
const int motorBPin1 = 5;
const int motorBPin2 = 6;
const int enableBPin1 = 3;

const int RED_THRESHOLD = 630; 
const int BLUE_THRESHOLD = 570;
const int YELLOW_THRESHOLD = 700; 
const int range = 10; // ie threshold +/- range 

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
  int color = detectColor();
  switch(color) {
    case 0: // Black - adjust path
      Serial.println("Black detected");
      turnLeft();
      break;
    case 1: // Red
      Serial.println("Red detected");
      turnRight();
      break;
    case 2: // Blue
      //moveForward
      Serial.println("Blue detected");
      turnRight();
      break;
    case 3: // Yellow
      Serial.println("Yellow detected");
      turnRight();
      break;
  }
  delay(250); // Short delay to prevent erratic behavior
}

int detectColor() {
  int Reflection;
  // Measure reflection from red and blue LED's
  Reflection = analogRead(sensorPin);
  Serial.println(Reflection);

  // Logic to determine color based on the reflection values
  if (Reflection >= RED_THRESHOLD && Reflection <= YELLOW_THRESHOLD) {
    return 1; // Red
  } else if (Reflection >= BLUE_THRESHOLD && Reflection <= RED_THRESHOLD) {
    return 2; // Blue
  } else if (Reflection >= YELLOW_THRESHOLD) {
    return 3; // Yellow
  } else {
    return 0; // Black or no color detected
  }
}


void forwardDirection() {
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
void reverseDirection() {
  digitalWrite(motorAPin1, LOW);
  analogWrite(motorAPin2, 150);
  
  analogWrite(motorBPin1, 150);
  digitalWrite(motorBPin2, LOW);

  digitalWrite(enableAPin1, HIGH); //right min 130
  digitalWrite(enableBPin1, HIGH); // left
}

void turnLeft() {
  analogWrite(motorAPin1, 100);
  digitalWrite(motorAPin2, LOW);
  digitalWrite(enableAPin1, HIGH); 

  // analogWrite(motorBPin1, 100);
  analogWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, LOW);
  digitalWrite(enableBPin1, HIGH);
}

void turnRight() {
  digitalWrite(motorAPin1, LOW);
  // analogWrite(motorAPin2, 100);
  analogWrite(motorAPin2, LOW);
  digitalWrite(enableAPin1, HIGH); 

  digitalWrite(motorBPin1, LOW);
  analogWrite(motorBPin2, 100);
  digitalWrite(enableBPin1, HIGH);
}

void slightLeft() {
  analogWrite(motorAPin1, 150);
  digitalWrite(motorAPin2, LOW);

  digitalWrite(motorBPin1, LOW);
  analogWrite(motorBPin2, 120);

  digitalWrite(enableAPin1, HIGH);
  digitalWrite(enableBPin1, HIGH);
}

void slightRight() {
  analogWrite(motorAPin1, 120);
  digitalWrite(motorAPin2, LOW);

  digitalWrite(motorBPin1, LOW);
  analogWrite(motorBPin2, 100);

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
