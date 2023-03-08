#include <Arduino.h>

#define LED_PIN 2
#define TOUCH_PIN 4
#define TOUCH_THRESHOLD 35

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(TOUCH_PIN, INPUT);

  Serial.begin(115200);
}

void loop() {
  const int val = touchRead(TOUCH_PIN);
  digitalWrite(LED_PIN, val < TOUCH_THRESHOLD);
  Serial.println(val);
  delay(200);
}
