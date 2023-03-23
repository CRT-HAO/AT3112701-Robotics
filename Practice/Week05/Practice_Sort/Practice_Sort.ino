#include <Arduino.h>

double array[] = { 2.5, 3.4, 6, -5, 10.2, 9.16 };
const size_t array_size = sizeof(array) / sizeof(double);

void bubbleSort(double *array, size_t size) {
  for(size_t i = 0; i < size - 1; i++) {
    for(size_t j = 0; j < size - 1 - i; j++) {
      if(array[j] < array[j + 1]) {
        double tmp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = tmp;
      }
    }
  }
}

void setup() {
  Serial.begin(115200);

  bubbleSort(array, array_size);
  
  for(size_t i = 0; i < array_size; i++) {
    Serial.print(array[i]);
    Serial.print(", ");
    Serial.println();
  }
}

void loop() {
}
