#include <Arduino.h>

#define BUTTON_PIN 0
#define LED_PIN 2
#define LED_BLINK_MS 1000

bool getButton() {
  return !digitalRead(BUTTON_PIN);
}

bool last_button_status = false;
bool getButtonClick() {
  bool button_status = getButton();
  bool click = button_status && button_status != last_button_status;
  last_button_status = button_status;
  return click;
}

void setLED(bool light) {
  digitalWrite(LED_PIN, light);
}

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  setLED((millis() % (LED_BLINK_MS * 2)) < LED_BLINK_MS);
  if(getButtonClick())
    Serial.println("Button Click!");
}