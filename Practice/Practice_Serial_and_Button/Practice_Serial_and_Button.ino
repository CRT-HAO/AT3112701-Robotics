#define BTN_PIN 0
#define FREQ 2000

bool readBtn() {
  return !digitalRead(BTN_PIN);
}

void setup() {
  Serial.begin(115200);

  pinMode(BTN_PIN, INPUT);
}

void loop() {
  Serial.println(readBtn());
  delay(FREQ);
}