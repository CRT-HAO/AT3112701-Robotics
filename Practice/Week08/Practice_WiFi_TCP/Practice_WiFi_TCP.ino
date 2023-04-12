#include <Arduino.h>
#include <WiFi.h>

const char WIFI_SSID[] = "Robot_Lab2.4";
const char WIFI_PASSWD[] = "73300000";
 
const uint16_t TCP_PORT = 6340;
const char TCP_HOST[] = "192.168.0.190";
 
WiFiClient client;

void setup() {
  Serial.begin(115200);
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());

  while (!client.connect(TCP_HOST, TCP_PORT)) {
      Serial.println("Connection to host failed");

      delay(1000);
  }
  Serial.println("Connected to server successful!");
}
 
void loop() {
  String message = "Hello from ESP32! time=" + String(millis());

  client.print(message.c_str());

  delay(1000);
}