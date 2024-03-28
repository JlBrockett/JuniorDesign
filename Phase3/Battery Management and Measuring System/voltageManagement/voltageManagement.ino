const int analogPin = A0; 
const float resistorOne = 2000.0; //Assumed value for R1
const float resistorTwo = 1000.0; //Assumed value for R2


void setup() {
  Serial.begin(9600);
}


void loop() {
  int sensorValue = analogRead(analogPin);
  float voltage = sensorValue * (5.00 / 1023.00); // Convert to voltage
  float batteryVoltage = voltage * ((resistorOne + resistorTwo) / resistorTwo);

  Serial.print("Battery Voltage: ");
  Serial.println(batteryVoltage);

  
  //Battery low; might need to measure that before we set a threshold
  if (batteryVoltage <= 6.0) { 
    Serial.println("Battery low, consider replacing.");
  }

  delay(1000);
}