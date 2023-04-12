#include <Arduino.h>
#include <WiFi.h>

const char WIFI_SSID[] = "Robot_Lab2.4";
const char WIFI_PASSWD[] = "73300000";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);

  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(". ");
    delay(500);
  }
}

void loop() {
  Serial.println();
  Serial.print("IP Address: ");
  Serial.print(WiFi.localIP());
  Serial.print(", RSSI: ");
  Serial.print(WiFi.RSSI());
  Serial.println();
  delay(1000);
}
