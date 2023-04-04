#include <Arduino.h>
#include <ESP32Servo.h> 

Servo myservo;

const int servoPin = 23;
const int potPin = 34;
const int ADC_Max = 4096;

int val;

void setup()
{
  Serial.begin(115200);
  myservo.attach(servoPin, 500, 2500);
}

void loop() {
  for(size_t i = 0; i < 180; i++) {
    Serial.println(i);
    myservo.write(val);
    delay(20);
  }
}