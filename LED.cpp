#include "LED.h"

#define NUM_OF_LED 2
#define NUM_OF_PINS 2

Adafruit_NeoPixel AN_LED = Adafruit_NeoPixel(NUM_OF_LED, NUM_OF_PINS, NEO_RGB + NEO_KHZ800);

// must initialize with begin() and show()


// void Dot::debug_show() {
//   printf("(%d, %d)\n", this->x, this->y);
// };

bool LEDClass::on(){
  AN_LED.setPixelColor(led_num_, rgb_[0], rgb_[1], rgb_[2]);
  AN_LED.show();
  
  status_ = true;

  return status_;
}

bool LEDClass::off(){
  AN_LED.setPixelColor(led_num_, 0x000000);
  status_ = false;

  return status_;
}

bool LEDClass::getStatus(){
  return status_;
}

void LEDClass::color(uint8_t red, uint8_t green, uint8_t blue){
  rgb_[0] = red;
  rgb_[1] = green;
  rgb_[2] = blue;
  
  SetHLSFromRGB();
  
  if (status_){
    on();
  }
}

void LEDClass::color(float hue){
  hls_[0] = hue;
  
  SetRGBFromHLS();
  
  if (status_){
    on();
  }
}

void LEDClass::brightness(float brightness){
  hls_[1] = brightness;
  
  SetRGBFromHLS();
  
  if (status_){
    on();
  }
}
  
void LEDClass::saturation(float saturation){
  hls_[2] = saturation;
  
  SetRGBFromHLS();
  
  if (status_){
    on();
  }
}

// void LEDClass::randomcolor(){
//   
// }
//  

void LEDClass::InfoRGBHLS(){
  for (int8_t i = 0; i < 3; i++){
    Serial.print("rgb_[");
    Serial.print(i);
    Serial.print("] : ");
    Serial.println(rgb_[i]);  
  } 
  for (int8_t i = 0; i < 3; i++){
    Serial.print("hls_[");
    Serial.print(i);
    Serial.print("] : ");
    Serial.println(hls_[i]);  
  }
}

void LEDClass::SetHLSFromRGB(){
  int8_t min = 255, max = 0;
  for (int8_t i = 0; i < 3; i++){
    if (rgb_[i] < min){
      min = rgb_[i];
    }
    if (rgb_[i] > max){
      max = rgb_[i];
    }
  }
  
  if (max == min){
    hls_[0] = 0;
    hls_[2] = 0;
  }
  else {
    for (int8_t i = 0; i < 3; i++){
      if (max == rgb_[i]){
        hls_[0] = 60 * (rgb_[(i+1)%3] - rgb_[(i+2)%3]) / (max - min) + 120 * i;
      }
    }
    while (hls_[0] < 0){
      hls_[0] += 360;
    }
  }

  hls_[2] = (max + min) / 2;
  if (hls_[2] < 128){
    hls_[1] = (max - min) / (max + min);
  }  
  else {
    hls_[1] = (max - min) / (510 - max - min);    
  }
}

void LEDClass::SetRGBFromHLS(){
  uint8_t max, min;
  if (hls_[1] < 50) {
    max = 2.55 * (hls_[1] + hls_[1] * hls_[2] / 100);
    min = 2.55 * (hls_[1] - hls_[1] * hls_[2] / 100);
  } else {
    max = 2.55 * (hls_[1] + (100 - hls_[1]) * hls_[2] / 100);
    min = 2.55 * (hls_[1] - (100 - hls_[1]) * hls_[2] / 100);
  }

  if (hls_[0] < 60) {
    rgb_[0] = max;
    rgb_[1] = (hls_[0] / 60) * (max - min) + min;
    rgb_[2] = min;
  } else if (hls_[0] < 120) {
    rgb_[0] = ((120 - hls_[0]) / 60) * (max - min) + min;
    rgb_[1] = max;
    rgb_[2] = min;
  } else if (hls_[0] < 180) {
    rgb_[0] = min;
    rgb_[1] = max;
    rgb_[2] = ((hls_[0] - 120) / 60) * (max - min) + min;
  } else if (hls_[0] < 240) {
    rgb_[0] = min;
    rgb_[1] = ((240 - hls_[0]) / 60) * (max - min) + min;
    rgb_[2] = max;
  } else if (hls_[0] < 300) {
    rgb_[0] = ((hls_[0] - 240) / 60) * (max - min) + min;
    rgb_[1] = min;
    rgb_[2] = max;
  } else {
    rgb_[0] = max;
    rgb_[1] = min;
    rgb_[2] = ((360 - hls_[0]) / 60) * (max - min) + min;
  }
}
  
