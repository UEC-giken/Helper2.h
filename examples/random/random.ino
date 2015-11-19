#include <Arduino.h>
#include <Wire.h>
#include <Helper2.h>

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

