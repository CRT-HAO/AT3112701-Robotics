#include <Arduino.h>
#define BUTTON_PIN 0
#define LED_PIN 2
#define LED_BLINK_MS 1000
#define LED_BLINK_MS_FAST 200

volatile bool click = false;
bool fast = false;

void IRAM_ATTR onClick() {
  click = true;
}

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  attachInterrupt(BUTTON_PIN, onClick, FALLING);
}

uint64_t start_time = millis();
void loop() {
  if(click) {
    start_time = millis();
    fast = !fast;
    click = false;
  }
  uint64_t blink_time = fast ? LED_BLINK_MS_FAST : LED_BLINK_MS;
  digitalWrite(LED_PIN, ((millis() - start_time) % (blink_time * 2)) > blink_time);
}
