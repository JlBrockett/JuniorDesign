#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = SECRET_SSID; 
char pass[] = SECRET_PASS;
const char postRoute[] = "POST /1B9564ECC320/1B9564ECC321 HTTP/1.1"; 

int status = WL_IDLE_STATUS;

char server[] = "ee31.ece.tufts.edu";
WiFiClient client;

void setup() {
  Serial.begin(9600);

  while (!Serial) {

    ; // wait for serial port to connect. Needed for native USB port only

  }

  // check for the WiFi module:

  if (WiFi.status() == WL_NO_MODULE) {

    Serial.println("Communication with WiFi module failed!");

    // don't continue

    while (true);

  }

  String fv = WiFi.firmwareVersion();

  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {

    Serial.println("Please upgrade the firmware");

  }


  while (status != WL_CONNECTED) {

    Serial.print("Attempting to connect to SSID: ");

    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);

  }

  Serial.println("Connected to wifi");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");

  // if you get a connection, report back via serial:

  if (client.connect(server, 80)) {

    Serial.println("connected to server");

    // Make a HTTP request:
    client.println("GET /search?q=arduino HTTP/1.1");

    client.println("Host: www.google.com");

    client.println("Connection: close");

    client.println();

  }
}

void loop() {

  // if there are incoming bytes available

  // from the server, read them and print them:

  while (client.available()) {

    char c = client.read();

    Serial.write(c);

  }

  // if the server's disconnected, stop the client:

  if (!client.connected()) {

    Serial.println();

    Serial.println("disconnecting from server.");

    client.stop();

    // do nothing forevermore:

    while (true);

  }
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

  Serial.println(" dBm");
}

void GETServer(const char theRoute[], char *message) { 
 
  if (client.connect(server, 80)) { 
    // Make a HTTP GET request: 
    client.println(theRoute); 
    client.print("Host: "); 
    client.println(server); 
    client.println("Connection: close"); 
    client.println(); 
    GetMessageBody(); // get the message from the server 
    // place in appropriate form and variable 
    // if the server's disconnected, stop the client: 
    if (!client.connected()) { 
      client.stop() 
    } 
  } 
}

void POSTServer(const char theRoute[], char *bodyMessage) {  
  client.println(theRoute); 
  client.print("Host: "); 
  client.println(server); 
  client.println("Content-Type: application/x-www-form-urlencoded"); 
  client.print("Content-Length: "); 
  int postBodyLength = strlen(bodyMessage); 
  client.println(postBodyLength); 
  client.println(); 
  client.print(bodyMessage); 
} 
