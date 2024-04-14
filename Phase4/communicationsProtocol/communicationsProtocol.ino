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
char getRoute[] = "GET /828BD9E1B7C7/828BD9E1B7C7 HTTP/1.1";
char postBody[] = "variable1=date&variable2=value2&variable3=value3&variable4=value4&variable5=value5&variable6=light";
char postRoute[] = "POST /828BD9E1B7C7/828BD9E1B7C7 HTTP/1.1";

// variables
int amp_Count = 0;
std::vector<char> command;
int idx = 0;
int startRead = 0;
int LED_pin = 7;




void setup() {

  pinMode(LED_pin, OUTPUT);
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
    Serial.println("disconnecting from server.");

    client.stop();

    while (true);

  }

  POSTServer(postRoute, postBody);
  GetServer(getRoute, messageData);
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

  if (message[10] == 'l') {

    digitalWrite(LED_pin, HIGH);

    delay(1000);

    digitalWrite(LED_pin, LOW);

  }

}

