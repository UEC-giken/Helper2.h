#include <Helper2.h>
#include <Wire.h>

void setup() {
  initialize();

  led1.randomColor();
  led2.randomColor();
  led1.on();
  led2.on();
}

void loop() {
  if (accel.active()) {
    led1.fadeIn();
    led2.fadeOut();
  } else {
    led1.fadeOut();
    led2.fadeIn();
  }

  wait(50);
}

