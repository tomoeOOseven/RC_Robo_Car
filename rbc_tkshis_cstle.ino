#define IN_1  5          // L298N in1 motors Right Front        GPIO15(D1)
#define IN_2  4          // L298N in2 motors Right Front        GPIO13(D2)
#define IN_3  0           // L298N in3 motors Left Front         GPIO2(D3)
#define IN_4  2           // L298N in4 motors Left Front         GPIO0(D4)
#define IN_5  14           // L298N in1 motors Right Rear         GPIO3(D5)
#define IN_6  12           // L298N in2 motors Right Rear         GPIO1(D6)
#define IN_7  13          // L298N in3 motors Left Rear          GPIO16(D7)
#define IN_8  15          // L298N in4 motors Left Rear          GPIO10(D8)

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

String command;            // String to store app command state.
int speedCar = 800;        // 400 - 1023.
int speed_Coeff = 3;

const char* ssid = "NodeMCU Car";
ESP8266WebServer server(80);

void setup() {
 
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
  pinMode(IN_5, OUTPUT);
  pinMode(IN_6, OUTPUT);
  pinMode(IN_7, OUTPUT);
  pinMode(IN_8, OUTPUT);
  
  Serial.begin(115200);
 
  // Connecting WiFi
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
  // Starting WEB-server 
  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);
  server.begin();
}

void goAhead() { 
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  
  digitalWrite(IN_5, LOW);
  digitalWrite(IN_6, HIGH);

  digitalWrite(IN_7, LOW);
  digitalWrite(IN_8, HIGH);
}

void goBack() { 
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  
  digitalWrite(IN_5, HIGH);
  digitalWrite(IN_6, LOW);

  digitalWrite(IN_7, HIGH);
  digitalWrite(IN_8, LOW);
}

void goRight() { 
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);

  digitalWrite(IN_5, HIGH);
  digitalWrite(IN_6, LOW);

  digitalWrite(IN_7, LOW);
  digitalWrite(IN_8, HIGH);
}

void goLeft() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);

  digitalWrite(IN_5, LOW);
  digitalWrite(IN_6, HIGH);

  digitalWrite(IN_7, HIGH);
  digitalWrite(IN_8, LOW);
}

void goAheadRight() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);

  digitalWrite(IN_5, HIGH);
  digitalWrite(IN_6, LOW);

  digitalWrite(IN_7, LOW);
  digitalWrite(IN_8, HIGH);
}

void goAheadLeft() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);

  digitalWrite(IN_5, LOW);
  digitalWrite(IN_6, HIGH);

  digitalWrite(IN_7, HIGH);
  digitalWrite(IN_8, LOW);
}

void goBackRight() { 
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);

  digitalWrite(IN_5, LOW);
  digitalWrite(IN_6, HIGH);

  digitalWrite(IN_7, HIGH);
  digitalWrite(IN_8, LOW);
}

void goBackLeft() { 
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);

  digitalWrite(IN_5, HIGH);
  digitalWrite(IN_6, LOW);

  digitalWrite(IN_7, LOW);
  digitalWrite(IN_8, HIGH);
}

void stopRobot() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);

  digitalWrite(IN_5, LOW);
  digitalWrite(IN_6, LOW);

  digitalWrite(IN_7, LOW);
  digitalWrite(IN_8, LOW);
}

void loop() {
  server.handleClient();
  
  command = server.arg("State");
  if (command == "F") goAhead();
  else if (command == "B") goBack();
  else if (command == "L") goLeft();
  else if (command == "R") goRight();
  else if (command == "I") goAheadRight();
  else if (command == "G") goAheadLeft();
  else if (command == "J") goBackRight();
  else if (command == "H") goBackLeft();
  else if (command == "S") stopRobot();
}

void HTTP_handleRoot() {
  if (server.hasArg("State")) {
    Serial.println(server.arg("State"));
  }
  server.send(200, "text/html", "");
  delay(1);
}