#include <Arduino.h>

#define LED_PIN_R 5
#define LED_PIN_G 18
#define LED_PIN_B 19

#define LED_PWM_CHANNEL_R 0
#define LED_PWM_CHANNEL_G 1
#define LED_PWM_CHANNEL_B 2

#define ANALOG_PIN 4
#define WIDTH 10


void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN_R, OUTPUT);
  pinMode(LED_PIN_G, OUTPUT);
  pinMode(LED_PIN_B, OUTPUT);
  pinMode(ANALOG_PIN, INPUT);

  analogSetWidth(WIDTH);

  ledcSetup(LED_PWM_CHANNEL_R, 5000, WIDTH);
  ledcAttachPin(LED_PIN_R, LED_PWM_CHANNEL_R);

  ledcSetup(LED_PWM_CHANNEL_G, 5000, WIDTH);
  ledcAttachPin(LED_PIN_G, LED_PWM_CHANNEL_G);

  ledcSetup(LED_PWM_CHANNEL_B, 5000, WIDTH);
  ledcAttachPin(LED_PIN_B, LED_PWM_CHANNEL_B);
}

void loop() {
  const int val = analogRead(ANALOG_PIN);

  ledcWrite(LED_PWM_CHANNEL_R, val);
  ledcWrite(LED_PWM_CHANNEL_G, val);
  ledcWrite(LED_PWM_CHANNEL_B, val);

  Serial.println(val);
  delay(20);
}
