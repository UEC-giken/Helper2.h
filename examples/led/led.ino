#include <Helper2.h>
#include <Wire.h>

void setup() {
  initialize();
}

void loop() {
  led1.color(100, 0 , 100);
  led1.on();
  wait(500);

  led1.color(0);
  wait(500);

  led1.brightness(0.1);
  wait(500);

  led1.saturation(0);
  wait(500);
}

