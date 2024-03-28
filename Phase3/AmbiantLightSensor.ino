//TODO: CALIBRATE

const int LED = 2;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:

  /**DEBUGGING CODE
  static unsigned long PrintMillis = millis();
  if (millis()-PrintMillis > 150) {
    Serial.println(sensorValue);
  }*/

  static unsigned long LEDMillis = millis();
  if (sensorValue < 980){ //daytime
    if ( millis() - LEDMillis > 100){
      LEDMillis = millis();
      digitalWrite(LED, !digitalRead(LED));
    }
  } else {
    digitalWrite(LED, HIGH);
  }
}
