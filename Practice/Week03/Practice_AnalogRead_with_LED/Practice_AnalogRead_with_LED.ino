#include <Arduino.h>

#define PWM_CHANNEL 0
#define LED_PIN 2
#define ANALOG_PIN 4
#define WIDTH 12

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(ANALOG_PIN, INPUT);

  analogSetWidth(WIDTH);

  ledcSetup(PWM_CHANNEL, 5000, WIDTH);
  ledcAttachPin(LED_PIN, PWM_CHANNEL);
}

void loop() {
  const int val = analogRead(ANALOG_PIN);

  ledcWrite(PWM_CHANNEL, val);

  Serial.println(val);
  delay(20);
}
