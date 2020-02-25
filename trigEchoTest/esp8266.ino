
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>


const char ssid[] = "Robot110";
const char password[] = "123456789";

int leftSpeed = 0, rightSpeed = 0;
const int leftPinA = D1;
const int leftPinB = D2;
const int rightPinA = D5;
const int rightPinB = D6;

ESP8266WebServer server(80);

void controlSpeed(int pinA,int pinB, int speed) {
  if(speed == 0) {
     digitalWrite(pinA, LOW);
     digitalWrite(pinB, LOW);
  }
  int duty = abs(speed) * 1023 / 100;
  if(speed > 0) {
    analogWrite(pinA, duty);
    digitalWrite(pinB, LOW);
  }
  if(speed < 0) {
    analogWrite(pinB, duty);
    digitalWrite(pinA, LOW);
  }
}

void handleRight() {
  for(int i = 0;i < server.args();++i) {
    if(server.argName(i) == "speed") {
      sscanf(server.arg(i).c_str(), "%d", &rightSpeed);
      rightSpeed -= 100;
      if(rightSpeed < -100 || rightSpeed > 100) {
        rightSpeed = 0;
      }
      server.send(200, "text/text", "success!");
      controlSpeed(rightPinA, rightPinB, rightSpeed);
      return;
    }
  }
}

void handleLeft() {
  for(int i = 0;i < server.args();++i) {
    if(server.argName(i) == "speed") {
      sscanf(server.arg(i).c_str(), "%d", &leftSpeed);
      leftSpeed -= 100;
      if(leftSpeed < -100 || leftSpeed > 100) {
        leftSpeed = 0;
      }
      server.send(200, "text/text", "success!");
      controlSpeed(leftPinA, leftPinB, leftSpeed);
      return;
    }
  }
}
  
void handleStatus() {
   char buf[256];
   sprintf(buf, "<h2>Left Speed: %d</h2>\n<h2>Right Speed: %d</h2>", leftSpeed, rightSpeed);
   server.send(200, "text/html", buf);
}

void handleRoot() {
  char buf[256];
  sprintf(buf, "<h1>Hello World!</h1>\n<h2>SSID: %s</h2>\n<h2>IP: %s</h2>", ssid, WiFi.softAPIP().toString().c_str());
  server.send(200, "text/html", buf);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(leftPinA, OUTPUT);  
  pinMode(leftPinB, OUTPUT);
  pinMode(rightPinA, OUTPUT);
  pinMode(rightPinB, OUTPUT);
  analogWriteFreq(10000);
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  if (MDNS.begin("robot")) {
    Serial.println("MDNS responder started");
  }

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/wheel/right", handleRight);
  server.on("/wheel/left", handleLeft);
  server.on("/status", handleStatus);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}
