#include <Arduino.h>

#define LED_PIN_R 5
#define LED_PIN_G 18
#define LED_PIN_B 19

#define LED_PWM_CHANNEL_R 0
#define LED_PWM_CHANNEL_G 1
#define LED_PWM_CHANNEL_B 2

#define LED_PWM_FREQ 2000
#define LED_PWM_WIDTH 16

#define LED_WAVE_LENGTH_MS 2000

const double LED_START_DEG_R = 0;
const double LED_START_DEG_G = LED_START_DEG_R + 120;
const double LED_START_DEG_B = LED_START_DEG_G + 120;

double degToRad(double deg) {
  return deg * M_PI / 180;
}

const uint16_t PWM_VAL_MAX = pow(2, LED_PWM_WIDTH);
uint16_t calculateLedVal(double deg) {
  return ((sin(degToRad(deg)) + 1) / 2) * PWM_VAL_MAX;
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN_R, OUTPUT);
  pinMode(LED_PIN_G, OUTPUT);
  pinMode(LED_PIN_B, OUTPUT);

  ledcSetup(LED_PWM_CHANNEL_R, LED_PWM_FREQ, LED_PWM_WIDTH);
  ledcAttachPin(LED_PIN_R, LED_PWM_CHANNEL_R);

  ledcSetup(LED_PWM_CHANNEL_G, LED_PWM_FREQ, LED_PWM_WIDTH);
  ledcAttachPin(LED_PIN_G, LED_PWM_CHANNEL_G);

  ledcSetup(LED_PWM_CHANNEL_B, LED_PWM_FREQ, LED_PWM_WIDTH);
  ledcAttachPin(LED_PIN_B, LED_PWM_CHANNEL_B);
}

void loop() {
  double time_deg = (millis() % LED_WAVE_LENGTH_MS) / (double)LED_WAVE_LENGTH_MS * 360.0;
  uint16_t led_val_r = calculateLedVal(time_deg + LED_START_DEG_R);
  uint16_t led_val_g = calculateLedVal(time_deg + LED_START_DEG_G);
  uint16_t led_val_b = calculateLedVal(time_deg + LED_START_DEG_B);

  ledcWrite(LED_PWM_CHANNEL_R, led_val_r);
  ledcWrite(LED_PWM_CHANNEL_G, led_val_g);
  ledcWrite(LED_PWM_CHANNEL_B, led_val_b);

  Serial.print("led_val_r:");
  Serial.print(led_val_r);
  Serial.print(",");
  Serial.print("led_val_g:");
  Serial.print(led_val_g);
  Serial.print(",");
  Serial.print("led_val_b:");
  Serial.print(led_val_b);
  Serial.println();

  delay(20);
}
