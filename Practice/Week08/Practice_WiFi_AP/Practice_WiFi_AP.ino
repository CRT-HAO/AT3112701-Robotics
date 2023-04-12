#include <Arduino.h>
#include <WiFi.h>

const char WIFI_SSID[] = "HAO's ESP32";
const char WIFI_PASSWD[] = "0916819600";
const int WIFI_CHANNEL = 8;

void setup() {
  Serial.begin(115200);
  WiFi.softAP(WIFI_SSID, WIFI_PASSWD, WIFI_CHANNEL);

  Serial.print("WiFi AP IP Address: ");
  Serial.print(WiFi.softAPIP());
  Serial.println();
}

void loop() { }