#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "iot_iconset_16x16.h"

// If debugging WiFi, set DEBUG_WIFI,
// the WiFi list will be faked.
// #define DEBUG_WIFI

#ifdef DEBUG_WIFI
#define DEBUG_WIFI_NUMS 4
const String DEBUG_WIFI_SSID[] = {
  "eduroam",
  "NTUST-PEAP",
  "NTUST-UAM",
  "sensor",
};

const int32_t DEBUG_WIFI_RSSI[] = {
  -20,
  -60,
  -80,
  -40,
};

const wifi_auth_mode_t DEBUG_WIFI_AUTH_MODE[] = {
  WIFI_AUTH_WPA2_PSK,
  WIFI_AUTH_WPA2_PSK,
  WIFI_AUTH_OPEN,
  WIFI_AUTH_OPEN,
};
#endif

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const unsigned char* getWifiIcon(int32_t rssi) {
  if(rssi >= -20)
    return signal4_icon16x16;
  else if(rssi >= -40)
    return signal3_icon16x16;
  else if(rssi >= -60)
    return signal2_icon16x16;
  else
    return signal1_icon16x16;
}

void scan() {
  Serial.println("=================================");
  Serial.println("scan start");

#ifdef DEBUG_WIFI
  int n = DEBUG_WIFI_NUMS;
  delay(2000);
#endif
#ifndef DEBUG_WIFI
  int n = WiFi.scanNetworks();
#endif
  Serial.println("scan done");
  if (n == 0) {
      Serial.println("no networks found");
  } else {
      Serial.print(n);
      Serial.println(" networks found");
      int y = 0;
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      for (int i = 0; i < n; ++i) {
#ifdef DEBUG_WIFI
          String ssid = DEBUG_WIFI_SSID[i];
          int32_t rssi = DEBUG_WIFI_RSSI[i];
          wifi_auth_mode_t auth_mode = DEBUG_WIFI_AUTH_MODE[i];
#endif
#ifndef DEBUG_WIFI
          String ssid = WiFi.SSID(i);
          int32_t rssi = WiFi.RSSI(i);
          wifi_auth_mode_t auth_mode = WiFi.encryptionType(i);
#endif
          bool with_pwd = (auth_mode != WIFI_AUTH_OPEN);

          // Print SSID and infos on OLED
          display.setCursor(0, y);
          display.print(ssid.substring(0, 8));
          display.drawBitmap(112, y, getWifiIcon(rssi), 16, 16, 1);
          if(with_pwd)
            display.drawBitmap(96, y, lock_closed_icon16x16, 16, 16, 1);
          y += 16;

          // Print SSID and RSSI for each network found
          Serial.print(i + 1);
          Serial.print(": ");
          Serial.print(ssid);
          Serial.print(" (");
          Serial.print(rssi);
          Serial.print(")");
          Serial.println(with_pwd ? " " : "*");
      }
      display.display();
  }
  Serial.println("=================================");
}

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
  }

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  display.display();
  delay(2000);

  display.clearDisplay();
  display.display();

#ifdef DEBUG_WIFI
  Serial.println("WiFi scan running in debug mdoe,");
  Serial.println("WiFi list will be faked");
#endif

  Serial.println("Setup done");
}

void loop() {
  scan();
  delay(10000);
}