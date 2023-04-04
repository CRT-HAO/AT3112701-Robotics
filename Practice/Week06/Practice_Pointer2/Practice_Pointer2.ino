#include <Arduino.h>

template <typename T>
void swap(T * a, T * b) {
  T tmp = *a;
  *a = *b;
  *b = tmp;
}

template <typename T>
void swap(T &a, T &b) {
  T tmp = a;
  a = b;
  b = tmp;
}

void setup() {
  Serial.begin(115200);

  int a = 123, b = 456;

  swap(a, b);

  Serial.print(a);
  Serial.print(", ");
  Serial.print(b);
  Serial.println();
}

void loop() { }