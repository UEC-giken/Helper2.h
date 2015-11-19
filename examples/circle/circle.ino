#include <Wire.h>
#include <Helper2.h>
#include <TimerOne.h>

void setup(){
  Serial.begin(9600);
  initialize();

  led1.on();
  led2.on();
}

void loop(){
  led1.colorcircle();
  led1.debug_print();
  led2.colorcircle();
  led2.debug_print();

  if (accel.tap()){
    led1.randomcolor();
  }

  if (accel.doubletap()){
    led2.randomcolor();
  }

  wait(100);
}

