#include <Helper2.h>
#include <Wire.h>

void setup() {
  initialize();
  
  led1.randomcolor();
  led2.randomcolor();  
  led1.on();
  led2.on();
}

void loop() {
  led1.debug_print();
  led1.fadeIn();
  led2.debug_print();
  led2.fadeOut();
  wait(100);
  
  // led1.fadeOut();
  // led2.fadeIn(); 
  // wait(10000);
  // 
}

