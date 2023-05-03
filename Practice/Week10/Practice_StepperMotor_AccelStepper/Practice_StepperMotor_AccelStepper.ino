#include <Arduino.h>
#include <AccelStepper.h>

#define BTN_PIN 0
#define STP_PUL_PIN 23
#define STP_DIR_PIN 22

AccelStepper stepper(AccelStepper::DRIVER, STP_PUL_PIN, STP_DIR_PIN);

void setup() {
  stepper.setMaxSpeed(20000.0);
  stepper.setAcceleration(20000.0);
  stepper.setMinPulseWidth(40);
}

bool dir = false;
void loop() {
  if(!stepper.run()) {
    stepper.move(800 * (dir ? 1 : -1));
    dir = !dir;
  }
}