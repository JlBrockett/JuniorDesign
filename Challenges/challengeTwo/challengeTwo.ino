/*
motorControl.ino
Alex, Jane, Selasie, and Supriti
April 25th, 2024

EE31 Challenge 2
*/


#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoSTL.h>
#include <vector>

//Our UUID: 56FC703ACE1A
//Cp-team UUID: 828BD9E1B7C7

char ssid[] = "junior"; 
char pass[] = "designdesign";
int status = WL_IDLE_STATUS;
char server[] = "ee31.ece.tufts.edu";    // name address for ee31 (using DNS)

WiFiClient client;

char messageData[100];
char getRoute[] = "GET /828BD9E1B7C7/56FC703ACE1A HTTP/1.1";
char postBody[] = "variable1=04/28/2024&variable2=value2&variable3=value3&variable4=value4&variable5=value5&variable6=light";
char postRoute[] = "POST /56FC703ACE1A/828BD9E1B7C7 HTTP/1.1";

// variables
int amp_Count = 0;
std::vector<char> command;
int idx = 0;
int startRead = 0;

//motor one
const int motorAPin1 = 9;
const int motorAPin2 = 10;
const int enableAPin1 = 11;

//motor two
const int motorBPin1 = 5;
const int motorBPin2 = 6;
const int enableBPin1 = 3;


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
  // if there are incoming bytes available

  // from the server, read them and print them:
  Serial.println("Test");

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
    Serial.println();
    readCommand(messageData);
    Serial.println("\ndisconnecting from server.");

    client.stop();

    while (true);

  }

  POSTServer(postRoute, postBody);
  static unsigned long timer = millis();
  delay(10000);
  unsigned long diff = millis() - timer;
  Serial.println();
  Serial.println(diff);
  //delay for sending messages will happen here.
  GetServer(getRoute, messageData);

  //move forward twelve inches
  
}

void sequence() {
  Serial.println("Starting sequence");
  forwardDirection();
  delay(1400);

  //Stop
  stopMotor();
  delay(1000);

  //turn around 180°
  turn();
  delay(1210);

  //stop, move backwards three inches
  stopMotor();
  delay(1000);
  reverseDirection();
  delay(410);

  //stop, turn left, turn right, turn right, and turn right to end up as close as possible to the  bot’s starting position.
  stopMotor();
  delay(1000);

  turn();
  delay(1210/2 + 10);

  stopMotor();
  delay(1000);

  turnRight();
  delay(1210/2 + 50);

  stopMotor();
  delay(1000);

  turnRight();
  delay(1210/2 + 50);

  stopMotor();
  delay(1000);

  turnRight();
  delay(1210/2 + 50);

  stopMotor();
  delay(1000);

  reverseDirection();
  delay(1830);



  stopMotor();
  // delay(10000);
}


/*
 * name:      forwardDirection
 * purpose:   move the motor
 * arguments: motor speed
 * returns:   None (void)
 * effects: moves the motor forward
 */
void forwardDirection() {
  analogWrite(motorAPin1, 170);
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

void turn() {
  analogWrite(motorAPin1, 160);
  digitalWrite(motorAPin2, LOW);
  digitalWrite(enableAPin1, HIGH); 

  analogWrite(motorBPin1, 150);
  digitalWrite(motorBPin2, LOW);
  digitalWrite(enableBPin1, HIGH);
}

void turnRight() {
  digitalWrite(motorAPin1, LOW);
  analogWrite(motorAPin2, 150);
  digitalWrite(enableAPin1, HIGH); 

  digitalWrite(motorBPin1, LOW);
  analogWrite(motorBPin2, 150);
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

    //&& idx < sizeof(messageData -1)
    // while (client.available()) {
    //   char c = client.read();
    //   Serial.write(c);
    //   messageData[idx] = c;
    //   idx++;
    // }

    for(int i = 0; i < 100; i++){
      char c = client.read();
      message[i] = c;
    }

    //messageData[227] = '\0';
    //getCommand(messageData);
    //printCommand(command);
    //printMessage(message);
    //readCommand();

    delay(10000);

    // if server is disconnected, stop the client:
    if(!client.connected()) {
      client.stop();
    }
  }
}




void GetMessageBody(char *message) {


}




void POSTServer(const
  char getRoute[],
  char *bodyMessage) {




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




void getCommand(char *message) {

  int ampCount = 0;
  int idx = 0;

  while (message[idx] != '\0') {

    if (message[idx] == '&') {
      ampCount ++;
    }

    if (ampCount >= 8) {
      command.push_back(message[idx]);
    }

    idx++;
  }
}




void printCommand(std::vector<char> command) {

  for (int i = 0; i < command.size(); i++) {

    Serial.print(command[i]);

  }

}




void printMessage(char *message) {

  for (int i = 0; i < 15; i++) {

    Serial.print(message[i]);

  }

}




void readCommand(char *message) {

  sequence();

}


