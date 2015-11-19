#include <Arduino.h>
#include <Wire.h>
#include <Helper2.h>

void setup(){
  Serial.begin(9600);
  initialize();
  
  led1.on();
  led2.on();
}
  
void loop(){
  led1.brightness(0.4);
  led1.colorcircle();
  led1.InfoRGBHLS();
  led2.brightness(0.4);
  led2.colorcircle();
  led2.InfoRGBHLS();

  if (accel.tap){
    led1.randomcolor();
  }
  else if (accel.doubletap){
    led2.randomcolor();
  }    
    
  wait(100);
}

