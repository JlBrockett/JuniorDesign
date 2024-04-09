const int redLEDPin = 9; 
const int blueLEDPin = 10;
const int sensorPin = A0; 


const int TURN_DELAY = 200; 
const int SEARCH_DELAY = 1000;

const int RED_THRESHOLD = ...; 
const int BLUE_THRESHOLD = ...; 
const int YELLOW_THRESHOLD_MIN = ...; 
const int YELLOW_THRESHOLD_MAX = ...; 

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
      break;
    case 2: // Blue
      //moveForward
      Serial.println("Blue detected");
      break;
    case 3: // Yellow
      Serial.println("Yellow detected");
      break;
  }
  delay(100); // Short delay to prevent erratic behavior
}

int detectColor() {
  int redReflection, blueReflection;

  // Measure reflection from red LED
  digitalWrite(redLEDPin, HIGH);
  delay(100); // Short delay to stabilize light reflection
  redReflection = analogRead(sensorPin);
  digitalWrite(redLEDPin, LOW);

  // Measure reflection from blue LED
  digitalWrite(blueLEDPin, HIGH);
  delay(100); // Short delay to stabilize light reflection
  blueReflection = analogRead(sensorPin);
  digitalWrite(blueLEDPin, LOW);

  // Logic to determine color based on the reflection values
  if (redReflection >= RED_THRESHOLD && blueReflection < BLUE_THRESHOLD) {
    return 1; // Red
  } else if (redReflection < RED_THRESHOLD && blueReflection >= BLUE_THRESHOLD) {
    return 2; // Blue
  } else if (redReflection >= YELLOW_THRESHOLD_MIN && redReflection <= YELLOW_THRESHOLD_MAX && 
             blueReflection >= YELLOW_THRESHOLD_MIN && blueReflection <= YELLOW_THRESHOLD_MAX) {
    return 3; // Yellow
  } else {
    return 0; // Black or no color detected
  }
}

void adjustPath() {
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
