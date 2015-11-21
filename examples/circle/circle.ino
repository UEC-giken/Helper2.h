#include <Wire.h>
#include <Helper2.h>

void setup() {
  initialize();

  led1.on();
  led2.on();
}

void loop() {
  led1.stepcolor();
  led1.debug_print();
  led2.stepcolor();
  led2.debug_print();

  if (accel.tap()) {
    led1.randomcolor();
  }

  if (accel.doubletap()) {
    led2.randomcolor();
  }

  wait(100);
}

