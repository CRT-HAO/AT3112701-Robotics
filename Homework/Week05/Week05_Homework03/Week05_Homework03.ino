#include <Arduino.h>

#define BUTTON_PIN 0
#define LED_PIN 2
#define LED_BLINK_TIMES 10
#define LED_BLINK_MS 50

volatile uint64_t start_blink_time = INFINITY;

void IRAM_ATTR onClick() {
  start_blink_time = millis();
}

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  attachInterrupt(BUTTON_PIN, onClick, FALLING);
}

void loop() {
  if((millis() - start_blink_time) < (LED_BLINK_TIMES * LED_BLINK_MS))
    digitalWrite(LED_PIN, (millis() % (LED_BLINK_MS * 2) < LED_BLINK_MS));
  else
    digitalWrite(LED_PIN, false);
}
