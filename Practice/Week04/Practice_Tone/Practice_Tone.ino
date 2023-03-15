#define BUZZER_PIN 23
#define BUZZER_PWM_CHANNEL 0
#define BUZZER_PWM_RESOLUTION 12

int tone[] = { 650, 400 };
size_t tone_size = sizeof(tone) / sizeof(int);

void setup() {
  Serial.begin(115200);

  pinMode(BUZZER_PIN, OUTPUT);

  ledcSetup(BUZZER_PWM_CHANNEL, tone[0], BUZZER_PWM_RESOLUTION);
  ledcAttachPin(BUZZER_PIN, BUZZER_PWM_CHANNEL);
}

void loop() {
  for(size_t i = 0; i < tone_size; i++) {
    ledcWriteTone(BUZZER_PWM_CHANNEL, tone[i]);
    Serial.println(tone[i]);
    delay(500);
  }
}
