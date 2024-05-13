#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoSTL.h>
#include <vector>
LiquidCrystal_I2C lcd(0x27, 16, 2);

/*======================================SONGS===============================================*/

//SONG:
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0


// change this to make the song slower or faster
int tempo = 114;

// change this to whichever pin you want to use
int buzzer = A3;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  // Never Gonna Give You Up - Rick Astley
  // Score available at https://musescore.com/chlorondria_5/never-gonna-give-you-up_alto-sax
  // Arranged by Chlorondria

  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,4, //1
  NOTE_E5,-4, NOTE_FS5,-4, NOTE_A5,16, NOTE_G5,16, NOTE_FS5,8,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,2,
  NOTE_A4,16, NOTE_A4,16, NOTE_B4,16, NOTE_D5,8, NOTE_D5,16,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,4, //repeat from 1
  NOTE_E5,-4, NOTE_FS5,-4, NOTE_A5,16, NOTE_G5,16, NOTE_FS5,8,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,2,
  NOTE_A4,16, NOTE_A4,16, NOTE_B4,16, NOTE_D5,8, NOTE_D5,16,
  REST,4, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_D5,8, NOTE_E5,8, NOTE_CS5,-8,
  NOTE_B4,16, NOTE_A4,2, REST,4, 

  REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,4, NOTE_A4,8, //7
  NOTE_A5,8, REST,8, NOTE_A5,8, NOTE_E5,-4, REST,4, 
  NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_D5,8, NOTE_E5,8, REST,8,
  REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
  REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4,
  NOTE_E5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, REST,4,
   
  NOTE_D5,2, NOTE_E5,8, NOTE_FS5,8, NOTE_D5,8, //13
  NOTE_E5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, NOTE_A4,4,
  REST,2, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8,
  REST,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,

  NOTE_E5,-8, NOTE_E5,-8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,-8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //18
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,8, NOTE_A4,8, NOTE_A4,8, 
  NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,

  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,  //23
  NOTE_E5,4, NOTE_D5,2, REST,4,
  REST,8, NOTE_B4,8, NOTE_D5,8, NOTE_B4,8, NOTE_D5,8, NOTE_E5,4, REST,8,
  REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
  REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4,
  REST,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8, NOTE_D5,8,
  
  REST,8, NOTE_A4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, //29
  REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
  NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4, REST,8,
  REST,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,4, NOTE_E5,-4, 
  NOTE_D5,2, NOTE_D5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, 
  NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8, NOTE_A4,8, NOTE_A4,4,

  REST,-4, NOTE_A4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, //35
  REST,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_E5,-8, NOTE_E5,-8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8, 

   NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //40
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,  
  NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
   
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //45
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,  
  NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //45
  
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8, 

  NOTE_E5,4, NOTE_D5,2, REST,4
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;



int beep_pin=A3;
int gap=1000;

//END OF SONG



//NOKIA
int ntempo = 180;

// change this to whichever pin you want to use

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int nmelody[] = {

  // Nokia Ringtone 
  // Score available at https://musescore.com/user/29944637/scores/5266155
  
  NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4, 
  NOTE_CS5, 8, NOTE_B4, 8, NOTE_D4, 4, NOTE_E4, 4, 
  NOTE_B4, 8, NOTE_A4, 8, NOTE_CS4, 4, NOTE_E4, 4,
  NOTE_A4, 2, 
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int nnotes = sizeof(nmelody) / sizeof(nmelody[0]) / 2;

// this calculates the duration of a whole note in ms
int nwholenote = (60000 * 4) / ntempo;

int ndivider = 0, nnoteDuration = 0;


/*============================Server Communications===================================*/

//Our UUID: 56FC703ACE1A
//Cp-team UUID: 828BD9E1B7C7

char ssid[] = "junior"; 
char pass[] = "designdesign";
int status = WL_IDLE_STATUS;
char server[] = "ee31.ece.tufts.edu";    // name address for ee31 (using DNS)

WiFiClient client;

char messageData[100];
char getRoute[] = "GET /56FC703ACE1A/56FC703ACE1A HTTP/1.1";
char postBody[] = "04/27/2024&variable2=value2&variable3=value3&variable4=value4&variable5=value5&variable6=light";
char postRoute[] = "POST /56FC703ACE1A/56FC703ACE1A HTTP/1.1";

// variables
int amp_Count = 0;
std::vector<char> command;
int idx = 0;
int startRead = 0;


/*================================GENERAL PINS==============================================*/
const int sensorPin = A0;
const int collisionSensor = A1;
int redLed = A4;
int yellowLed = 1;
int blueLed = 0;
int greenLed = 13;
int headlights = 4;
int brakelights = 12;



/*================================MOTOR PINS==============================================*/
//motor one
const int motorAPin1 = 10; //left
const int motorAPin2 = 9;
const int enableAPin1 = 11;

//motor two
const int motorBPin1 = 5; //right
const int motorBPin2 = 6;
const int enableBPin1 = 3;

//thresholds
// const int RED_THRESHOLD = 590; 
// const int BLUE_THRESHOLD = 540;
// const int YELLOW_THRESHOLD = 670; 

const int RED_THRESHOLD = 950; 
const int BLUE_THRESHOLD = 700;
const int YELLOW_THRESHOLD = 1000; 

//booleans
bool wallOne = false;
bool wallTwo = false;
bool wallThree = false;













/*=====================================SETUP==============================================*/
void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(motorAPin1, OUTPUT);
  pinMode(motorAPin2, OUTPUT);
  pinMode(enableAPin1, OUTPUT);

  pinMode(motorBPin1, OUTPUT);
  pinMode(motorBPin2, OUTPUT);
  pinMode(enableBPin1, OUTPUT);
  Serial.begin(9600);
  while (!Serial) {

    ; // wait for serial port to connect. Needed for native USB port only

  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("No WiFi :(");
    while (true);
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);

    printWifiStatus();
    delay(3000);
  }

  Serial.println("Connected to WiFi");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Yes WiFi :)");
  printWifiStatus();




  Serial.println("\nStarting connection to server...");

  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Connected");
  }
}


void loop() {
  digitalWrite(blueLed, HIGH);
  delay(250);
  digitalWrite(blueLed, LOW);
  digitalWrite(redLed, HIGH);
  delay(250);
  digitalWrite(redLed, LOW);
  digitalWrite(blueLed, HIGH);
  delay(250);
  digitalWrite(blueLed, LOW);
  digitalWrite(redLed, HIGH);
  delay(250);
  digitalWrite(blueLed, HIGH);
  digitalWrite(redLed, LOW);
  delay(250);
  digitalWrite(redLed, HIGH);
  delay(250);
  digitalWrite(blueLed, LOW);

  lcd.clear();
  detectCollision();
  while (!wallOne) {
    forwardDirection();
    detectCollision();
  }

  stopMotor();
  horn();
  delay(800);
  turnRight();

  //delay for 180 deg turn
  // delay(2200);
  delay(1450);

  stopMotor();
  delay(800);

  //find red line
  int colorOne = detectColor();
  delay(250);
  while (colorOne != 1) {
     forwardDirection();
     colorOne = detectColor();
     delay(250);
  }
  
  stopMotor();
  delay(800);
  turnLeft();
  delay(1000);
  stopMotor();
  // delay(1000);

  //Send Server Message
  //message does not need to be specific. The reciever will just detect the presence of a new message
  POSTServer(postRoute, postBody);

  digitalWrite(redLed, HIGH);
  digitalWrite(blueLed, HIGH);
  delay(250);
  digitalWrite(redLed, LOW);
  digitalWrite(blueLed, LOW);
  delay(250);
  digitalWrite(redLed, HIGH);
  digitalWrite(blueLed, HIGH);
  delay(250);
  digitalWrite(redLed, LOW);
  digitalWrite(blueLed, LOW);

  delay(1000);

  digitalWrite(brakelights, HIGH);
  digitalWrite(headlights, HIGH);
  delay(250);
  digitalWrite(brakelights, LOW);
  digitalWrite(headlights, LOW);
  delay(250);  

  horn();
  horn();


  detectCollision();
  digitalWrite(redLed, HIGH);
  while (!wallTwo) {
    redLineFollowing();
    detectCollision();
  }
  digitalWrite(redLed, LOW);
  stopMotor();
  horn();

  digitalWrite(redLed, HIGH);
  delay(250);
  digitalWrite(redLed, LOW);
  delay(250);
  digitalWrite(redLed, HIGH);
  delay(250);
  digitalWrite(redLed, LOW);
  delay(250);

  //Send Server Message
  //message does not need to be specific. The reciever will just detect the presence of a new message
  POSTServer(postRoute, postBody);

  //Recieve Message
  digitalWrite(redLed, HIGH);
  delay(250);
  digitalWrite(redLed, LOW);
  delay(250);
  digitalWrite(redLed, HIGH);
  delay(250);
  digitalWrite(redLed, LOW);
  delay(250);
  digitalWrite(redLed, HIGH);
  delay(250);
  digitalWrite(redLed, LOW);
  delay(250);

  digitalWrite(greenLed, HIGH);


  turnLeft();
  delay(1100);
  stopMotor();
  delay(800);

  //find yellow line
  int colorOne = detectColor();
  delay(250);
  while (colorOne != 3) {
     forwardDirection();
     colorOne = detectColor();
     delay(250);
  }

  stopMotor();
  delay(800);

  turnLeft();
  delay(1000);
  digitalWrite(greenLed, LOW);
  digitalWrite(yellowLed, HIGH);

  detectCollision();
  digitalWrite(yellowLed, HIGH);
  while (!wallThree) {
    redLineFollowing();
    detectCollision();
  }
  digitalWrite(yellowLed, LOW);
  stopMotor();
  horn();
  delay(800);


  //move to starting position
  turnLeft();
  delay(1000);
  forwardDirection();
  delay(1000);
  turnLeft();
  delay(1250);
  stopMotor();

  //Send Server Message at the end
  //message does not need to be specific. The reciever will just detect the presence of a new message
  POSTServer(postRoute, postBody);
  rick();

}

void detectCollision() {
  int val;
  val = analogRead(collisionSensor);
  if (val > 200) {
    if (wallOne == false) {
      wallOne = true;
    }
    else if (wallTwo == false) {
      wallTwo = true;
    }
    else if (wallThree == false) {
      wallThree = true;
    }
  }
}


int detectColor() {
  int Reflection;
  // Measure reflection from red and blue LED's
  Reflection = analogRead(sensorPin);
  lcd.setCursor(0,0);
  lcd.print(Reflection);

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


void redLineFollowing() {

  int color = detectColor();
  switch(color) {
    case 0: // Black - adjust path
      slightLeft();
      break;
    case 1: // Red
      slightRight();
      break;
    case 2: // Blue
      slightRight();
      break;
    case 3: // Yellow
      slightRight();
      break;
  }
  // 
  delay(200); // Short delay to prevent erratic behavior
  stopMotor();
  delay(20);
}

void yellowLineFollowing() {
  int color = detectColor();
  switch(color) {
    case 0: // Black - adjust path
      Serial.println("Black detected");
      turnLeft();
      break;
    case 3: // Red
      Serial.println("Yellow detected");
      turnRight();
      break;
  }
  delay(250); // Short delay to prevent erratic behavior
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

void turnRight() {
  analogWrite(motorAPin1, 150);
  digitalWrite(motorAPin2, LOW);
  digitalWrite(enableAPin1, HIGH); 

  analogWrite(motorBPin1, 150);
  digitalWrite(motorBPin2, LOW);
  digitalWrite(enableBPin1, HIGH);
}

void turnLeft() {
  digitalWrite(motorAPin1, LOW);
  analogWrite(motorAPin2, 150);
  digitalWrite(enableAPin1, HIGH); 

  digitalWrite(motorBPin1, LOW);
  analogWrite(motorBPin2, 150);
  digitalWrite(enableBPin1, HIGH);
}

void slightLeft() {
  digitalWrite(motorAPin1, LOW);
  // analogWrite(motorAPin2, 100);
  analogWrite(motorAPin2, LOW);
  digitalWrite(enableAPin1, HIGH); 

  digitalWrite(motorBPin1, LOW);
  analogWrite(motorBPin2, 100);
  digitalWrite(enableBPin1, HIGH);
}

void slightRight() {
  analogWrite(motorAPin1, 100);
  digitalWrite(motorAPin2, LOW);
  digitalWrite(enableAPin1, HIGH); 

  // analogWrite(motorBPin1, 100);
  analogWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, LOW);
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

void rick() {
  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}





void horn(){
  float rise_fall_time=2000;
  int steps=100;
  float f_max=1500;
  float f_min=500;
  float delay_time=rise_fall_time/steps;
  float step_size=1.012;
  for (float f =f_min;f<f_max;f*=step_size){
    tone(beep_pin,f);
    delay(delay_time);
  }
  noTone(beep_pin);
  delay(100);
  
}

void printWifiStatus() {

  // print the SSID of the network you're attached to:

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println("dBm");
}

void POSTServer(const char getRoute[], char *bodyMessage) {
  if (client.connect(server, 80)) {
    client.println(getRoute);
    client.print("Host: ");
    client.println(server);
    client.println("Content-Type:application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    int postBodyLength = strlen(bodyMessage);
    client.println(postBodyLength);
    client.println();
    client.print(bodyMessage);
    if(!client.connected()) {
      client.stop();
    }
  }
}

