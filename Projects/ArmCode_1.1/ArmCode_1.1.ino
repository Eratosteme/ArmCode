#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char* SSID = "connect";
const char* PASSWORD = "123ouinon";
 
WebServer server(80);
 
String stringa = "Hello World!";

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
WiFi.mode(WIFI_STA);
WiFi.begin(SSID, PASSWORD);
Serial.println("");
 
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.print("Connettiti a ");
Serial.println(SSID);
Serial.print("IP address: ");
Serial.println(WiFi.localIP());

if (MDNS.begin("esp32")) {
Serial.print("ESP32 online: ");
Serial.println("http://esp32.local/");
}
server.on("/", handleRoot);
server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}
void handleRoot() {
server.send(200, "text/plain", "Hello World");
}