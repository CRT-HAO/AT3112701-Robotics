#include <Arduino.h>

#define ANALOG_PIN 4

void setup() {
  pinMode(ANALOG_PIN, INPUT);

  Serial.begin(115200);
}

void loop() {
  Serial.println(analogRead(ANALOG_PIN));
  delay(20);
}
