#include <Helper2.h>
#include <Wire.h>
#include <TimerOne.h>

void setup(){
  Serial.begin(9600);

  initialize();
}

void loop(){
  led1.color(100, 0 , 100);
  led1.on();
  led1.debug_print();
  delay(500);

  led1.color(0);
  led1.debug_print();
  delay(500);

  led1.brightness(0.1);
  led1.debug_print();
  delay(500);

  led1.saturation(0);
  led1.debug_print();
  delay(500);

}

