#include <Arduino.h>

#define SERVO_PIN 23
#define SERVO_PWM_CHANNEL 0
#define SERVO_PWM_FREQ 50
#define SERVO_PWM_RESOLUTION 16

const uint32_t SERVO_PWM_MAX_DUTY = pow(2, SERVO_PWM_RESOLUTION) - 1;
void setServoAngle(double angle) {
  uint32_t duty = ((angle * 0.0005555555556) + 0.025) * SERVO_PWM_MAX_DUTY;
  ledcWrite(SERVO_PWM_CHANNEL, duty);
  Serial.println(duty);
}

void setup() {
  Serial.begin(115200);

  pinMode(SERVO_PIN, OUTPUT);

  ledcSetup(SERVO_PWM_CHANNEL, SERVO_PWM_FREQ, SERVO_PWM_RESOLUTION);
  ledcAttachPin(SERVO_PIN, SERVO_PWM_CHANNEL);
}

void loop() {
  for(size_t i = 0; i < 180; i++) {
    setServoAngle(i);
    // Serial.println(i);
    delay(10);
  }
  for(size_t i = 0; i < 180; i++) {
    setServoAngle(180 - i);
    // Serial.println(180 - i);
    delay(10);
  }
}
