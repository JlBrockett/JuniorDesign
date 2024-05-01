#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoSTL.h>
#include <vector>

const int sensorPin = A0;
const int collisionSensor = A1;

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

const int RED_THRESHOLD = 770; 
const int BLUE_THRESHOLD = 650;
const int YELLOW_THRESHOLD = 800; 

//booleans
bool wallOne = false;
bool wallTwo = false;
bool wallThree = false;


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

void setup() {
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
    while (true);
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);

    printWifiStatus();
    delay(10000);
  }

  Serial.println("Connected to WiFi");
  printWifiStatus();




  Serial.println("\nStarting connection to server...");

  if (client.connect(server, 80)) {
    Serial.println("connected to server");
  }
}


void loop() {

  GetServer(getRoute, messageData);
  while (client.available()){
    char c = client.read();
    if (startRead == 8){
      messageData[idx] = c;
      idx++;
    }

    if (c == '&'){
      startRead++;
    }

    Serial.write(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {

    Serial.println();
    printMessage(messageData);
    readCommand(messageData);
    Serial.println("\ndisconnecting from server.");

    client.stop();

    while (true);

  }
  // sequence();
  // reverseDirection();

  // delay(5000);
  // stopMotor();

  // delay(2000);

  delay(1000);
  detectCollision();
  while (!wallOne) {
    forwardDirection();
    detectCollision();
  }

  stopMotor();
  delay(1000);
  turnRight();

  //delay for 180 deg turn
  // delay(2200);
  delay(2200);

  stopMotor();
  delay(1000);


  // int colorOne = detectColor();
  // delay(250);
  // while (colorOne != 1) {
  //    forwardDirection();
  //    colorOne = detectColor();
  //    delay(250);
  // }
  // stopMotor();
  // delay(5000);

  forwardDirection();
  delay(3000);
  stopMotor();
  delay(1800);
  turnLeft();
  delay(1100);
  stopMotor();
  delay(1000);

  detectCollision();
  while (!wallTwo) {
    redLineFollowing();
    detectCollision();
  }
  stopMotor();
  delay(2000);
  turnLeft();
  delay(1100);

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
  }
}


int detectColor() {
  int Reflection;
  // Measure reflection from red and blue LED's
  Reflection = analogRead(sensorPin);
  Serial.println(Reflection);

  // Logic to determine color based on the reflection values
  if (Reflection >= RED_THRESHOLD && Reflection <= YELLOW_THRESHOLD) {
    Serial.println("red detected");
    return 1; // Red
  } else if (Reflection >= BLUE_THRESHOLD && Reflection <= RED_THRESHOLD) {
    Serial.println("blue detected");
    return 2; // Blue
  } else if (Reflection >= YELLOW_THRESHOLD) {
    Serial.println("yellow detected");
    return 3; // Yellow
  } else {
    Serial.println("black detected");
    return 0; // Black or no color detected
  }
}




void sequence() {
  detectCollision();
  while (!wallOne) {
    forwardDirection();
    detectCollision();
  }

  stopMotor();
  turnRight();

  //delay for 180 deg turn
  delay(1500);

  //start detecting red
  int colorOne = detectColor();
  while (colorOne != 1) {
    forwardDirection();
    colorOne = detectColor();
  }

  stopMotor();
  //light based comms

  forwardDirection();
  //delay until off red track by a little bit
  delay(50);

  //start red line following while wall is not detected
  detectCollision();
  while (!wallTwo) {
    //follow red path
    //TODO: Write red line following code
    redLineFollowing();
    detectCollision();
  }

  stopMotor();
  turnLeft();
  //delay for 90 deg turn
  delay(800);

  int colorTwo = detectColor();
  while (colorTwo != 3) {
    forwardDirection();
    colorTwo = detectColor();
  }

  stopMotor();
  forwardDirection();
  //delay to go off track a little
  delay(50);

  //start yellow line following
  while(!wallThree) {
    //follow yellow path
    //TODO: Write yellow path following function
    yellowLineFollowing();
  }

  //TODO: Sequence after
}


void redLineFollowing() {
  // int color = detectColor();
  // switch(color) {
  //   case 0: // Black - adjust path
  //     Serial.println("Black detected");
  //     turnLeft();
  //     break;
  //   case 1: // Red
  //     Serial.println("Red detected");
  //     turnRight();
  //     break;
  // }
  // delay(250); // Short delay to prevent erratic behavior


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
  delay(100);
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
  analogWrite(motorAPin1, 90);
  digitalWrite(motorAPin2, LOW);

  digitalWrite(motorBPin1, LOW);
  analogWrite(motorBPin2, 90);

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
  analogWrite(motorAPin2, 110);
  
  analogWrite(motorBPin1, 100);
  digitalWrite(motorBPin2, LOW);

  digitalWrite(enableAPin1, HIGH); //right min 130
  digitalWrite(enableBPin1, HIGH); // left
}

void turnRight() {
  analogWrite(motorAPin1, 90);
  digitalWrite(motorAPin2, LOW);
  digitalWrite(enableAPin1, HIGH); 

  analogWrite(motorBPin1, 90);
  digitalWrite(motorBPin2, LOW);
  digitalWrite(enableBPin1, HIGH);
}

void turnLeft() {
  digitalWrite(motorAPin1, LOW);
  analogWrite(motorAPin2, 90);
  digitalWrite(enableAPin1, HIGH); 

  digitalWrite(motorBPin1, LOW);
  analogWrite(motorBPin2, 90);
  digitalWrite(enableBPin1, HIGH);
}

void slightLeft() {
  analogWrite(motorAPin1, 150);
  digitalWrite(motorAPin2, LOW);

  digitalWrite(motorBPin1, LOW);
  analogWrite(motorBPin2, 120);

  digitalWrite(enableAPin1, HIGH);
  digitalWrite(enableBPin1, HIGH);
}

void slightRight() {
  analogWrite(motorAPin1, 120);
  digitalWrite(motorAPin2, LOW);

  digitalWrite(motorBPin1, LOW);
  analogWrite(motorBPin2, 100);

  digitalWrite(enableAPin1, HIGH); // Set speed (0 to 255)
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




void GetServer(const char getRoute[], char *message) {

  if (client.connect(server, 80)) {

    // make an HTTP GET request:
    client.println(getRoute);
    client.print("Host: ");
    client.println(server);
    client.println("Connection:close");
    client.println();

    int idx = 0;

    for(int i = 0; i < 100; i++){
      char c = client.read();
      message[i] = c;
    }
    delay(5000);

    // if server is disconnected, stop the client:
    if(!client.connected()) {
      client.stop();
    }
  }
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

void printMessage(char *message) {

  for (int i = 0; i < 15; i++) {

    Serial.print(message[i]);

  }

}


void readCommand(char *message) {

  if (message[10] == 'm') {

    Serial.println("Move instr recieved");

  }

}
