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

const int RED_THRESHOLD = 730; 
const int BLUE_THRESHOLD = 670;
const int YELLOW_THRESHOLD = 870; 
const int BLACK_THRESHOLD = 540;
const int range = 10; // ie threshold +/- range 

void setup() {
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int color = detectColor();
  switch(color) {
    case 0: // Black - adjust path
      //adjustPath
      Serial.println("Black wins");
      break;
    case 1: // Red
      Serial.println("Red detected");
      turnRight();
      break;
    case 2: // Blue
      //moveForward
      Serial.println("Blue detected");
      turnLeft();
      break;
    case 3: // Yellow
      Serial.println("Yellow detected");
      break;
  }
  delay(100); // Short delay to prevent erratic behavior
}

int detectColor() {
  int Reflection;

  // Measure reflection from red LED
  digitalWrite(redLEDPin, HIGH);
//  delay(100); // Short delay to stabilize light reflection
//  redReflection = analogRead(sensorPin);
//  digitalWrite(redLEDPin, LOW);

  // Measure reflection from blue LED
  digitalWrite(blueLEDPin, HIGH);
  delay(100); // Short delay to stabilize light reflection
  Reflection = analogRead(sensorPin);
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

//void adjustPath() {
  // Initially, try turning slightly to the right to find the blue path
  turnSlightlyRight();
  
  // Wait a bit and check if the path is found
  delay(SEARCH_DELAY);
  
  int color = detectColor();
  if (color == 2) { // If blue path is found, continue forward
    moveForward();
  } else { // If still not found, try turning left more significantly
    turnSlightlyLeft();
  }
}







// const int redLEDPin = 9; 
// const int blueLEDPin = 10;
// const int sensorPin = A0; 


// const int TURN_DELAY = 200; 
// const int SEARCH_DELAY = 1000;

// const int RED_THRESHOLD = ...; 
// const int BLUE_THRESHOLD = ...; 
// const int YELLOW_THRESHOLD_MIN = ...; 
// const int YELLOW_THRESHOLD_MAX = ...; 

// void setup() {
//   pinMode(redLEDPin, OUTPUT);
//   pinMode(blueLEDPin, OUTPUT);
//   Serial.begin(9600);
// }

// void loop() {
//   int color = detectColor();
//   switch(color) {
//     case 0: // Black - adjust path
//       //adjustPath
//       Serial.println("Black wins");
//       break;
//     case 1: // Red
//       Serial.println("Red detected");
//       break;
//     case 2: // Blue
//       //moveForward
//       Serial.println("Blue detected");
//       break;
//     case 3: // Yellow
//       Serial.println("Yellow detected");
//       break;
//   }
//   delay(100); // Short delay to prevent erratic behavior
// }

// int detectColor() {
//   int redReflection, blueReflection;

//   // Measure reflection from red LED
//   digitalWrite(redLEDPin, HIGH);
//   delay(100); // Short delay to stabilize light reflection
//   redReflection = analogRead(sensorPin);
//   digitalWrite(redLEDPin, LOW);

//   // Measure reflection from blue LED
//   digitalWrite(blueLEDPin, HIGH);
//   delay(100); // Short delay to stabilize light reflection
//   blueReflection = analogRead(sensorPin);
//   digitalWrite(blueLEDPin, LOW);

//   // Logic to determine color based on the reflection values
//   if (redReflection >= RED_THRESHOLD && blueReflection < BLUE_THRESHOLD) {
//     return 1; // Red
//   } else if (redReflection < RED_THRESHOLD && blueReflection >= BLUE_THRESHOLD) {
//     return 2; // Blue
//   } else if (redReflection >= YELLOW_THRESHOLD_MIN && redReflection <= YELLOW_THRESHOLD_MAX && 
//              blueReflection >= YELLOW_THRESHOLD_MIN && blueReflection <= YELLOW_THRESHOLD_MAX) {
//     return 3; // Yellow
//   } else {
//     return 0; // Black or no color detected
//   }
// }

// void adjustPath() {
//   // Initially, try turning slightly to the right to find the blue path
//   //turnSlightlyRight();
  
//   // Wait a bit and check if the path is found
//   //delay(SEARCH_DELAY);
  
//   //int color = detectColor();
//   //if (color == 2) { // If blue path is found, continue forward
//     //moveForward();
//   //} else { // If still not found, try turning left more significantly
//     //turnSlightlyLeft();
//   //}
// }
