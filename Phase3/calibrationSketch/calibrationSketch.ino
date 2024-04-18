const int redLEDPin = 9; 
const int blueLEDPin = 10;
const int sensorPin = A0; 

void setup() {
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(redLEDPin, HIGH);
  delay(100); // Stabilization delay
  Serial.print("Red LED reading: ");
  Serial.println(analogRead(sensorPin));
  digitalWrite(redLEDPin, LOW);

  delay(5000); // Wait before next reading

  digitalWrite(blueLEDPin, HIGH);
  delay(100); // Stabilization delay
  Serial.print("Blue LED reading: ");
  Serial.println(analogRead(sensorPin));
  digitalWrite(blueLEDPin, LOW);

  delay(500);
}

//red threshold: 660
//blue threshold: 370

//Yellow min: 390
//Yellow max: 690
