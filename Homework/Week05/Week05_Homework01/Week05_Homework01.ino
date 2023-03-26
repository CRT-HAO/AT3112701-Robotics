#include <Arduino.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  while(Serial.available()) {
    String str = Serial.readString();
    uint8_t input_byte = str.toInt();

    uint8_t high_times = 0;
    for(size_t i = 0; i < 8; i++) {
      uint8_t bit = bitRead(input_byte, i); 
      if(bit == 1)
        high_times += 1;
      Serial.print(bit);
      Serial.print(' ');
    }
    
    Serial.print(high_times);
    Serial.println();
  }
}
