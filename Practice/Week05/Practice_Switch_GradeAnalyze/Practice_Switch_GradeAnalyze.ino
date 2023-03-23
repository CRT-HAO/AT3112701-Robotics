#include <Arduino.h>
#include "limits.h"

void setup() {
  Serial.begin(115200);
}

void loop() {
  while(Serial.available()) {
    String input_str = Serial.readString();
    uint32_t score = input_str.toInt();

    switch(score) {
      case 0 ... 59:
        Serial.println("Fail");
        break;
      case 60 ... 79:
        Serial.println("Pass");
        break;
      case 80 ... 89:
        Serial.println("Good");
        break;
      case 90 ... UINT32_MAX:
        Serial.println("Very Good");
        break;
    }
  }
}
