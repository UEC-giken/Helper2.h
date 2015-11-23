#include <Helper2.h>
#include <Wire.h>

void setup() {
  initialize();
}

void loop() {
  led2.on();
  if (accel.doubletap()) {
     led2.randomcolor();
  }
  
  if (accel.tap()) {
    led1.on();
  } else {
    led1.off();
  }
  wait(20);
};
