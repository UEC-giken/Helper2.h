#include <Helper2.h>
#include <Wire.h>

void setup() {
  initialize();

  led1.on();
}

void loop() {
  led1.randomColor();

  wait(500);
}

