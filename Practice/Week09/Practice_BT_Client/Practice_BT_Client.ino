#include <Arduino.h>
#include <BluetoothSerial.h>

#define LED_PIN 2

BluetoothSerial SerialBT;

const char BT_NAME[] = "HAO's ESP32";
const char BT_PIN[] = "9487";

void setup() {
  Serial.begin(115200);

  SerialBT.begin(BT_NAME);
  // SerialBT.setPin(BT_PIN);

  byte mac_bt[6];
  esp_read_mac(mac_bt, ESP_MAC_BT);
  Serial.printf("Bluetooth Address: %02X:%02X:%02X:%02X:%02X:%02X",
                mac_bt[0], mac_bt[1], mac_bt[2], mac_bt[3], mac_bt[4], mac_bt[5]);
}

void loop() {
  if(SerialBT.available()) {
    char val = SerialBT.read();
    switch(val) {
      case '0':
      case '1':
        digitalWrite(LED_PIN, val == '1');
        break;
    }
  }
}