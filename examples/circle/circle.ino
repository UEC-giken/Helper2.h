#include <Wire.h>
#include <Helper2.h>

void setup() {
  initialize();

  led1.on();
  led2.on();
}

void loop() {
  led1.stepColor();
  led1.debugPrint();
  led2.stepColor();
  led2.debugPrint();

  if (accel.tap()) {
    led1.randomColor();
  }

  if (accel.doubletap()) {
    led2.randomColor();
  }

  wait(100);
}

