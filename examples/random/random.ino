#include <Helper2.h>
#include <Wire.h>
#include <TimerOne.h>

void setup(){
  Serial.begin(9600);

  initialize();
}

void loop(){
  led1.randomcolor();
  led1.debug_print();
  led1.on();
  delay(500);
}

