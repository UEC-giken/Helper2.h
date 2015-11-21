#include <Helper2.h>
#include <Wire.h>

bool tapped;

void setup() {
  initialize();
  
  led1.randomcolor();
  led2.randomcolor();  
  led1.on();
  led2.on();
}

void loop() {
  if (tapped){
    led1.debug_print();
    led1.fadeIn();
    led2.debug_print();
    led2.fadeOut();
    if (accel.tap()){
      tapped = false;
    }
  }
  else {
    led1.debug_print();
    led1.fadeOut();
    led2.debug_print();
    led2.fadeIn(); 
    if (accel.tap()){
      tapped = true;
    }
  }
  
  wait(100);
}

