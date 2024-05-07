/*
motorControl.ino
Alex, Jane, Selasie, and Supriti
April 25th, 2024

EE31 Challenge 5
*/

#include <Ultrasonic.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

/*
How to download the Ultrasonic library:
1. Download the Slider-Examples repository: https://github.com/uArm-Developer/Slider-Examples/archive/master.zip 95
2. Unzip the downloaded file.
3. (In the Arduino IDE) Sketch > Include library > Add .ZIP Library
4. From the unzipped folder, select Slider-Examples-master/lib/Grove_Ultrasonic_Ranger.zip
5. Click the "Open" button.
*/

LiquidCrystal_I2C lcd(0x27, 16, 2);

Ultrasonic ultrasonic(A2); 

const int motorAPin1 = 10; 
const int motorAPin2 = 9;
const int enableAPin1 = 11;

//motor two
const int motorBPin1 = 5;
const int motorBPin2 = 6;
const int enableBPin1 = 3;

int redLed = A4;
int yellowLed = 1;
int blueLed = 0;
int greenLed = 13;




void setup() {
  
  pinMode(motorAPin1, OUTPUT);
  pinMode(motorAPin2, OUTPUT);
  pinMode(enableAPin1, OUTPUT);

  pinMode(motorBPin1, OUTPUT);
  pinMode(motorBPin2, OUTPUT);
  pinMode(enableBPin1, OUTPUT);

  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

}

void loop() {
  //move forward 25 inches
  vel();
  delay(1000);

  for (int i = 0; i <= 10; i++) {
    forwardDirection();
    vel();
    delay(100);
  }

  stopMotor();
  delay(1000);
  vel();

  for (int i = 0; i <= 10; i++) {
    fast();
    vel();
    delay(100);
  }

  // for (int i = 0; i <= 10; i++) {
  //   reverseDirection();
  //   vel();
  //   delay(500);
  // }


  // for (int i = 0; i <= 10; i++) {
  //   reverseDirection();
  //   vel();
  //   delay(500);
  // }



  stopMotor();
  vel();
  delay(250);
  vel();
  delay(3000); 
}




void vel() {
  static unsigned long lastTime = 0;
  static long lastDistance = 0;
  float velocity = 0.0;

  unsigned long currentTime = millis();
  long currentDistance = ultrasonic.MeasureInCentimeters();

  // Calculate velocity only if a significant time has elapsed (e.g., every 200 milliseconds)
  if (currentTime - lastTime >= 500) {
    // Calculate velocity in cm/s
    velocity = (float)(currentDistance - lastDistance) / (currentTime - lastTime) * 1000.0;
    velocity = -velocity;
    
    lastDistance = currentDistance;
    lastTime = currentTime;
  }
  lcd.setCursor(0,0);
  lcd.print("Velocity:");
  lcd.setCursor(0,1);
  lcd.print(velocity);
  lcd.setCursor(4, 1);
  lcd.print(" cm/s");

  delay(100);
}




/*
 * name:      forwardDirection
 * purpose:   move the motor
 * arguments: motor speed
 * returns:   None (void)
 * effects: moves the motor forward
 */
void fast() {
  analogWrite(motorAPin1, 200);
  digitalWrite(motorAPin2, LOW);

  digitalWrite(motorBPin1, LOW);
  analogWrite(motorBPin2, 200);

  digitalWrite(enableAPin1, HIGH); // Set speed (0 to 255)
  digitalWrite(enableBPin1, HIGH);
}


void forwardDirection() {
  analogWrite(motorAPin1, 150);
  digitalWrite(motorAPin2, LOW);

  digitalWrite(motorBPin1, LOW);
  analogWrite(motorBPin2, 140);

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
