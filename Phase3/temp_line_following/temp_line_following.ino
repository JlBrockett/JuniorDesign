const int redLEDPin = 13; 
const int blueLEDPin = 12;
const int sensorPin = A5;

//motor one
const int motorAPin1 = 9;
const int motorAPin2 = 10;
const int enableAPin1 = 11;

//motor two
const int motorBPin1 = 5;
const int motorBPin2 = 6;
const int enableBPin1 = 3;

const int RED_THRESHOLD = 860; 
const int BLUE_THRESHOLD = 800;
const int YELLOW_THRESHOLD = 900; 
const int range = 10; // ie threshold +/- range 

void setup() {
  pinMode(motorAPin1, OUTPUT);
  pinMode(motorAPin2, OUTPUT);
  pinMode(enableAPin1, OUTPUT);

  pinMode(motorBPin1, OUTPUT);
  pinMode(motorBPin2, OUTPUT);
  pinMode(enableBPin1, OUTPUT);

  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
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

  // Turn red and blue LED's
  digitalWrite(redLEDPin, HIGH);
  digitalWrite(blueLEDPin, HIGH);

  // Short delay to stabilize light reflection
  delay(250);

  // Measure reflection from red and blue LED's
  Reflection = analogRead(sensorPin);
  Serial.println(Reflection);

  //Turn off red and blue LED's
  digitalWrite(blueLEDPin, LOW);
  digitalWrite(redLEDPin, LOW);

  // Logic to determine color based on the reflection values
  if (Reflection >= RED_THRESHOLD + range && Reflection <= RED_THRESHOLD - range) {
    return 1; // Red
  } else if (Reflection >= BLUE_THRESHOLD + range && Reflection <= BLUE_THRESHOLD - range) {
    return 2; // Blue
  } else if (Reflection >= YELLOW_THRESHOLD + range && Reflection <= YELLOW_THRESHOLD - range) {
    return 3; // Yellow
  } else {
    return 0; // Black or no color detected
  }
}


void turnLeft() {
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorAPin2, LOW);
  analogWrite(enableAPin1, 150); 

  digitalWrite(motorBPin1, HIGH);
  digitalWrite(motorBPin2, LOW);
  analogWrite(enableBPin1, 150);
}

void turnRight() {
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, HIGH);
  analogWrite(enableAPin1, 150); 

  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, HIGH);
  analogWrite(enableBPin1, 150);
}

void stopMotors() {
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, LOW);

  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, LOW);
}
