#include "LED.h"

#define NUM_OF_LED 2
#define NUM_OF_PINS 2

Adafruit_NeoPixel AN_LED = Adafruit_NeoPixel(NUM_OF_LED, NUM_OF_PINS, NEO_RGB + NEO_KHZ800);

// must initialize with begin() and show()


// void Dot::debug_show() {
//   printf("(%d, %d)\n", this->x, this->y);
// };

bool LEDClass::on(){
  AN_LED.setPixelColor(led_num_, red_, green_, blue_);
  AN_LED.show();
  
  status_ = true;

  return status_;
}

bool LEDClass::off(){
  AN_LED.setPixelColor(led_num_, 0x000000);
  status_ = false;

  return status_;
}

// bool LEDClass::getStatus(){
//   return status_;
// }
// 
// void LEDClass::color(float hue){
//   color(led_num_, hue);
//   
//   
// }
// 
// void LEDClass::color(uint8_t r, uint8_t g, uint8_t b){
//   red_ = r;
//   green_ = g;
//   blue_ = b;
//   
//   SetHLSFromRGB();
// }
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
// void LEDClass::SetHLSFromRGB(){
//   
// }
// 
// void LEDClass::SetRGBFromHLS(){
//   double max, min;
//   if (brightness_ < 0.5) {
//     max = 255 * l * (saturation_ + 1);
//     min = 255 * l * (s - 1);
//   } else {
//     max = 255 * (l + (1 - l) * s);
//     min = 255 * (l - (1 - l) * s);
//   }
// 
//   if (h < 60) {
//     red_ = max;
//     green_ = (h / 60) * (max - min) + min;
//     blue_ = min;
//   } else if (h < 120) {
//     red_ = ((120 - h) / 60) * (max - min) + min;
//     green_ = max;
//     blue_ = min;
//   } else if (h < 180) {
//     red_ = min;
//     green_ = max;
//     blue_ = ((h - 120) / 60) * (max - min) + min;
//   } else if (h < 240) {
//     red_ = min;
//     green_ = ((240 - h) / 60) * (max - min) + min;
//     blue_ = max;
//   } else if (h < 300) {
//     red_ = ((h - 240) / 60) * (max - min) + min;
//     green_ = min;
//     blue_ = max;
//   } else {
//     red_ = max;
//     green_ = min;
//     blue_ = ((360-h) / 60) * (max - min) + min;
//   }
// }
//   
// 
// 
// 
// 
// void color_update_hsl(int led) {
//   double s = led_saturation[led-1];
//   double l = led_brightness[led-1];
//   double h = led_hue[led-1] * 360; // 0 - 360
// 
//   double max, min;
//   if (l < 0.5) {
//     max = 255 * l * (s + 1);
//     min = 255 * l * (s - 1);
//   } else {
//     max = 255 * (l + (1 - l) * s);
//     min = 255 * (l - (1 - l) * s);
//   }
// 
//   uint8_t r, g, b;
// 
//   if (h < 60) {
//     r = max;
//     g = (h / 60) * (max - min) + min;
//     b = min;
//   } else if (h < 120) {
//     r = ((120 - h) / 60) * (max - min) + min;
//     g = max;
//     b = min;
//   } else if (h < 180) {
//     r = min;
//     g = max;
//     b = ((h - 120) / 60) * (max - min) + min;
//   } else if (h < 240) {
//     r = min;
//     g = ((240 - h) / 60) * (max - min) + min;
//     b = max;
//   } else if (h < 300) {
//     r = ((h - 240) / 60) * (max - min) + min;
//     g = min;
//     b = max;
//   } else {
//     r = max;
//     g = min;
//     b = ((360-h) / 60) * (max - min) + min;
//   }
// 
//   uint32_t rgb = Adafruit_NeoPixel::Color(r, g, b);
//   // Serial.println(rgb, HEX);
//   led_colors[led-1] = rgb;
// 
// }