const int analogPin = A5; 
const float resistorOne = 100000.0; //Assumed value for R1
const float resistorTwo = 51000.0; //Assumed value for R2

// const float r1min = resistorOne - (resistorOne * 0.05);
// const float r1max = resistorOne + (resistorOne * 0.05);

// const float r2min = resistorTwo - (resistorTwo * 0.05);
// const float r2max = resistorTwo + (resistorTwo * 0.05);


void setup() {
  Serial.begin(9600);
}


void loop() {
  int sensorValue = analogRead(analogPin);
  // Serial.println(sensorValue);
  float voltage = sensorValue * (5.05 / 1023.00); // Convert to voltage
  float batteryVoltage = voltage * ((resistorOne + resistorTwo) / resistorTwo);

  Serial.print("Battery Voltage: ");
  Serial.println(batteryVoltage);

  
  //Battery low; might need to measure that before we set a threshold
  if (batteryVoltage <= 6.0) { 
    Serial.println("Battery low, consider replacing.");
  }

  delay(1000);
}