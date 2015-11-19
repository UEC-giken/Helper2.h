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
// 
// void LEDClass::color(float hue){
//   color(led_num_, hue);
//   
//   
// }
// 
void LEDClass::color(uint8_t red, uint8_t green, uint8_t blue){
  rgb_[0] = red;
  rgb_[1] = green;
  rgb_[2] = blue;
  
  SetHLSFromRGB();
}
// 
// void brightness(double brightness){
//   brightness_ = brightness;
//   
//   SetRGBFromHLS();  
// }
//   
// void saturation(double saturation){
//   
// }
// 
// void LEDClass::randomcolor(){
//   
// }
//  
void LEDClass::SetHLSFromRGB(){
  int8_t min = 0, max = 0;
  for (int8_t i = 0; i < 3; i++){
    if (rgb_[i] < min){
      min = rgb_[i];
    }
    if (rgb_[i] > max){
      max = rgb_[i];
    }
  }
  
  if (rgb_[0] == rgb_[1] && rgb_[1] == rgb_[2]){
    hsl_[0] = 0;
  }
  else {
    for (int8_t i = 0; i < 3; i++){
      if (max == rgb_[i]){
        hsl_[0] = 60 * ((rgb_[(i+1)%3] - rgb_[(i+2)%3]) / (max - min));
      }
    }
    if (hsl_[0] < 0){
      hsl_[0] += 360;
    }
  }

  hsl_[2] = (max + min) / 2;
  if (hsl_[2] <= 127){
    hsl_[1] = (max - min) / (max + min);
  }  
  else {
    hsl_[1] = (max - min) / (510 - max - min);    
  }
}

// void LEDClass::SetRGBFromHLS(){
//   double max, min;
//   if (brightness_ < 0.5) {
//     max = 255 * brightness_ * (saturation_ + 1);
//     min = 255 * brightness_ * (saturation_ - 1);
//   } else {
//     max = 255 * (brightness_ + (1 - brightness_) * saturation_);
//     min = 255 * (brightness_ - (1 - brightness_) * saturation_);
//   }
// 
//   if (hue_ < 60) {
//     red_ = max;
//     green_ = (hue_ / 60) * (max - min) + min;
//     blue_ = min;
//   } else if (hue_ < 120) {
//     red_ = ((120 - hue_) / 60) * (max - min) + min;
//     green_ = max;
//     blue_ = min;
//   } else if (hue_ < 180) {
//     red_ = min;
//     green_ = max;
//     blue_ = ((hue_ - 120) / 60) * (max - min) + min;
//   } else if (hue_ < 240) {
//     red_ = min;
//     green_ = ((240 - hue_) / 60) * (max - min) + min;
//     blue_ = max;
//   } else if (hue_ < 300) {
//     red_ = ((hue_ - 240) / 60) * (max - min) + min;
//     green_ = min;
//     blue_ = max;
//   } else {
//     red_ = max;
//     green_ = min;
//     blue_ = ((360 - hue_) / 60) * (max - min) + min;
//   }
// }
//   
