#include <Arduino.h>
#define BUTTON_PIN 0
#define LED_PIN 2

volatile bool click = false;

void IRAM_ATTR test() {
  click = !click;
}

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  attachInterrupt(BUTTON_PIN, test, FALLING);
}

void loop() {
  digitalWrite(LED_PIN, click);
  delay(1000);
}
