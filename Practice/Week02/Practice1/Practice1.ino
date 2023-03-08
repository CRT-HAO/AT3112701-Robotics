#define LED_PIN 2
#define BTN_PIN 0
#define FREQ_NORMAL 500
#define FREQ_FAST 200

bool on = false;
bool fast = false;
bool last_btn = false;

bool readBtn() {
  return !digitalRead(BTN_PIN);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);
}

void loop() {
  digitalWrite(LED_PIN, (on = !on));

  if(!last_btn && readBtn())
    fast = !fast;
  last_btn = readBtn();

  delay(fast ? FREQ_FAST : FREQ_NORMAL);
}