#include <Arduino.h>

#define SERVO_PIN 23

void setServoUS(uint8_t pin, uint32_t microseconds) {
  digitalWrite(pin, true);
  delayMicroseconds(microseconds);
  digitalWrite(pin, false);
  delayMicroseconds(20000 - microseconds);
}

void setup() {
  pinMode(SERVO_PIN, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  for(size_t i = 0; i < 180; i++) {
    uint32_t us = (i * 11.1111111111) + 500;
    setServoUS(SERVO_PIN, us);
    Serial.println(us);
  }
  for(size_t i = 0; i < 180; i++) {
    uint32_t us = ((180 - i) * 11.1111111111) + 500;
    setServoUS(SERVO_PIN, us);
    Serial.println(us);
  }
}
