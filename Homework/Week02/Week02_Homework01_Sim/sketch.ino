// For real world device
#define LED_PIN 2
#define BTN_PIN 0
// For simulator
// #define LED_PIN 2
// #define BTN_PIN 23

typedef enum {
  ONE,
  ZERO_EIGHT,
  ZERO_SIX,
  ZERO_FOUR,
  ZERO_TWO
} Mode;

Mode mode;

bool getButton() {
  return !digitalRead(BTN_PIN);
}

bool last_button = getButton();
bool getButtonClick() {
  bool button = getButton() && !last_button;
  last_button = getButton();
  return button;
}

uint32_t getLEDDealyTime(Mode mode) {
  switch(mode) {
    default:
    case Mode::ONE:
      return 1000;
    case Mode::ZERO_EIGHT:
      return 800;
    case Mode::ZERO_SIX:
      return 600;
    case Mode::ZERO_FOUR:
      return 400;
    case Mode::ZERO_TWO:
      return 200;
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(BTN_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  mode = Mode::ONE;
}

void loop() {
  if(getButtonClick()) {
    mode = (mode != Mode::ZERO_TWO) ? (Mode)((uint8_t)mode + 1) : Mode::ONE;
    Serial.print("Mode=");
    Serial.print(mode);
    Serial.print(", DelayTime=");
    Serial.print(getLEDDealyTime(mode));
    Serial.print("ms");
    Serial.println();
  }

  uint32_t led_delay_time = getLEDDealyTime(mode);

  digitalWrite(LED_PIN, (millis() % (led_delay_time * 2)) < led_delay_time);

  delay(10);
}