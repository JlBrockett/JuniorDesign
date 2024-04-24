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


const int TURN_DELAY = 200; 
const int SEARCH_DELAY = 1000;

// const int RED_THRESHOLD = 730; 
// const int BLUE_THRESHOLD = 670;
// const int YELLOW_THRESHOLD = 870; 
// const int BLACK_THRESHOLD = 540;

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

//First loop
// void loop() {
//   int color = detectColor();
//   switch(color) {
//     case 0: // Black - adjust path
//       //adjustPath
//       Serial.println("Black detected");
//       break;
//     case 1: // Red
//       Serial.println("Red detected");
//       turnRight();
//       break;
//     case 2: // Blue
//       //moveForward
//       Serial.println("Blue detected");
//       turnLeft();
//       break;
//     case 3: // Yellow
//       Serial.println("Yellow detected");
//       break;
//   }
//   delay(100); // Short delay to prevent erratic behavior
// }

void loop() {
  int color = detectColor();
  switch(color) {
    case 0: // Black - adjust path
      //adjustPath
      Serial.println("Black detected");
      stopMotor();
      break;
    case 1: // Red
      Serial.println("Red detected");
      turnRight();
      break;
    case 2: // Blue
      //moveForward
      Serial.println("Blue detected");
      turnLeft();
      // forwardDirection();
      break;
    case 3: // Yellow
      Serial.println("Yellow detected");
      stopMotor();
      break;
  }
  delay(250); // Short delay to prevent erratic behavior
}

int detectColor() {
  int Reflection;

  // Measure reflection from red LED
  digitalWrite(redLEDPin, HIGH);

  // Measure reflection from blue LED
  digitalWrite(blueLEDPin, HIGH);

  // Short delay to stabilize light reflection
  delay(250); 

  //Record and turn LED's off
  Reflection = analogRead(sensorPin);
  Serial.println(Reflection);
  digitalWrite(blueLEDPin, LOW);
  digitalWrite(redLEDPin, LOW);


  // Logic to determine color based on the reflection values
  // if (Reflection >= RED_THRESHOLD + range && Reflection <= RED_THRESHOLD - range) {
  if (Reflection >= RED_THRESHOLD - range && Reflection <= YELLOW_THRESHOLD) {
    return 1; // Red
  } else if (Reflection >= BLUE_THRESHOLD && Reflection < RED_THRESHOLD) {
    return 2; // Blue
  } else if (Reflection >= YELLOW_THRESHOLD + range || Reflection >= YELLOW_THRESHOLD - range) {
    return 3; // Yellow
  } else {
    return 0; // Black or no color detected
  }
}

void forwardDirection() {
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, HIGH);
  
  digitalWrite(motorBPin1, HIGH);
  digitalWrite(motorBPin2, LOW);

  analogWrite(enableAPin1, 130); //left
  analogWrite(enableBPin1, 210); //right
}

void reverseDirection() {
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorAPin2, LOW);

  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, HIGH);

  analogWrite(enableAPin1, 130); //left
  analogWrite(enableBPin1, 210); //right
}


void turnLeft() {
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorAPin2, LOW);
  analogWrite(enableAPin1, 150); 

  digitalWrite(motorBPin1, HIGH);
  digitalWrite(motorBPin2, LOW);
  analogWrite(enableBPin1, 150);
  //add delay
}

void turnRight() {
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, HIGH);
  analogWrite(enableAPin1, 150); 

  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, HIGH);
  analogWrite(enableBPin1, 150);
  //add delay
}

void stopMotor() {
  //stop motor A
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, LOW);

  //stop motor B
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, LOW);
}


//second loop
// void loop() {
//   int color = detectColor();
//   switch(color) {
//     case 0: // Black - adjust path
//       //adjustPath
//       Serial.println("Black detected");
//       break;
//     case 1: // Red
//       Serial.println("Red detected");
//       turnRight();
//       break;
//     case 2: // Blue
//       //moveForward
//       Serial.println("Blue detected");
//       forwardDirection();
//       break;
//     case 3: // Yellow
//       Serial.println("Yellow detected");
//       stopMotor();
//       break;
//   }
//   delay(100); // Short delay to prevent erratic behavior
// }

//The turn we have is the point turn. We have to work on a curve turn which moves forward/backward while turning

