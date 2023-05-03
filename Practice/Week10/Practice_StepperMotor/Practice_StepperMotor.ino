#include <Arduino.h>

#define BTN_PIN 0
#define STP_PUL_PIN 23
#define STP_DIR_PIN 22
#define STP_COUNT_STP 800

inline void step() {
  digitalWrite(STP_PUL_PIN, true);
  delayMicroseconds(10);
  digitalWrite(STP_PUL_PIN, false);
  delayMicroseconds(300);
}

void stepCount(uint32_t count) {
  uint32_t pul = count * STP_COUNT_STP;
  for(uint32_t i = 0; i < pul; i++)
    step();
}

inline bool getButton() {
  return !digitalRead(BTN_PIN);
}

bool lastButton = false;
inline bool getButtonClick() {
  bool button = getButton();
  bool click = button && !lastButton;
  lastButton = button;
  return click;
}

void setup() {
  Serial.begin(115200);

  pinMode(BTN_PIN, INPUT);
  pinMode(STP_PUL_PIN, OUTPUT);
  pinMode(STP_DIR_PIN, OUTPUT);
}

void loop() {
  bool click = getButtonClick();
  if(click) {
    Serial.println("Button click!");
    stepCount(1);
  }
}
