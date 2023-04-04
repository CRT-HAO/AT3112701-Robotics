int * getA() {
  int * a = new int;
  *a = 123;
  return a;
}

void setup() {
  Serial.begin(115200);

  int * test = getA();

  Serial.println(*test);
}

void loop() {
}