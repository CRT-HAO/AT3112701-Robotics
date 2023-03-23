#include <Arduino.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  while(Serial.available()) {
    String input_str = Serial.readString();
    uint32_t score = input_str.toInt();

    if(score >= 80)
      Serial.println('A');
    else if(score >= 70 && score <= 79)
      Serial.println('B');
    else if(score >= 60 && score <= 69)
      Serial.println('C');
    else if(score < 60)
      Serial.println('D');
  }
}
