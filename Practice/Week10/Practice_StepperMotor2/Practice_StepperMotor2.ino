#include <Arduino.h>

#define BTN_PIN 0
#define STP_PUL_PIN 23
#define STP_DIR_PIN 22
#define STP_COUNT_STP 800

inline void step() {
  digitalWrite(STP_PUL_PIN, true);
  delayMicroseconds(10);
  digitalWrite(STP_PUL_PIN, false);
  delayMicroseconds(615);
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

uint32_t stp = 0;
bool dir = false;
void loop() {
  if(getButtonClick()) {
    dir = !dir;
    digitalWrite(STP_DIR_PIN, dir);
  }

  step();

  stp += dir ? 1 : -1;
  Serial.println(stp);
}
