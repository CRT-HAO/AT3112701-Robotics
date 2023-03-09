#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Hi");
}

void loop() {
  if(Serial.available()) {
    String str = Serial.readString();

    long sum = 0;
    int last_index = -1;

    for(;;) {
      int index = str.indexOf(',', last_index + 1);

      String num_str = str.substring(last_index + 1, index);

      sum += num_str.toInt();

      if(index == -1)
        break;
      
      last_index = index;
    }

    Serial.println(sum);
  }
}