#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#define LED_PIN 2

const char WIFI_SSID[] = "MI8";
const char WIFI_PASSWD[] = "0916819600";
 
WiFiUDP Udp;
const uint16_t LOCAL_UDP_PORT = 9487;
 
WiFiClient client;

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("...");
  }
  Serial.println();
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());

  Udp.begin(LOCAL_UDP_PORT);
  Serial.println("UDP server running, waiting for client...");
}
 
void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    char buf[packetSize];
    Udp.read(buf, packetSize);

    Serial.println();
    Serial.print("Received: ");
    Serial.println(buf);
    Serial.print("From IP: ");
    Serial.println(Udp.remoteIP());
    Serial.print("From Port: ");
    Serial.println(Udp.remotePort());
    bool led_on = false;
    if(buf[0] == 0 || buf[0] == 1) {
      led_on = (buf[0] == 1);
      digitalWrite(LED_PIN, led_on);
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.print(led_on ? "LED on" : "LED off");
      Udp.endPacket();
    }

  }
}