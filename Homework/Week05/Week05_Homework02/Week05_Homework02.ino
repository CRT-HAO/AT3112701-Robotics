#include <Arduino.h>

#define BUTTON_PIN 0

volatile bool click = false;

void IRAM_ATTR onClick() {
  click = true;
}

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT);

  attachInterrupt(BUTTON_PIN, onClick, FALLING);
}

size_t i = 0;
void loop() {
  if(click) {
    i += 1;
    Serial.println(i);
    click = false;
  }
}
