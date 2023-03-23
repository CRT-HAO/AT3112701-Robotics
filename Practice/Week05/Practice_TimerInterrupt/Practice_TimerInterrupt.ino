#include <Arduino.h>
#define LED_PIN 2

#define TIMER_ID 0
#define TIMER_DIVIDER 80
#define TIMER_COUNT_UP true

// 計時器上限值
#define TIMER_ALARM_VALUE 1000000

hw_timer_t *timer;
volatile bool led_on = false;

void IRAM_ATTR onTimer() {
  digitalWrite(LED_PIN, (led_on = !led_on));
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  timer = timerBegin(TIMER_ID, TIMER_DIVIDER, TIMER_COUNT_UP);
  timerAttachInterrupt(timer, &onTimer, TIMER_COUNT_UP);
  timerAlarmWrite(timer, TIMER_ALARM_VALUE, true);
  timerAlarmEnable(timer);
}

void loop() {
}
