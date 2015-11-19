// #include "Helper2_protected.h"
#include "Adafruit_NeoPixel.h"

#pragma once

extern Adafruit_NeoPixel AN_LED;

class LED {
public:
  LED(int8_t num):
    led_num_(num),

    status_(false)
  {
    rgb_[0] = 100;
    rgb_[1] = 100;
    rgb_[2] = 100;
    SetRGBFromHLS();
  }
  // LED(const LED& origin){
  //
  // };

  // return led status
  bool on();
  bool off();
  bool getStatus();

  // led の色相を変更する
  // 色相: 0-360
  void color(uint8_t red, uint8_t green, uint8_t blue);
  void color(uint8_t hue);
  
  // led の明るさを変更する
  // 明るさ: 0-100
  void brightness(uint8_t brightness);
  
  // led の彩度を変更する
  // 彩度 0-100
  void saturation(uint8_t saturation);
  
  // led の色をランダムに点灯する
  void randomcolor();
  
  // DEBUG
  void RandomColorFromHLS();
  void RandomColorFromRGB();
  void InfoRGBHLS();
  
private:
  // led status on = true, off = false
  bool status_;

  // led_num_ = {0, 1, }
  int8_t led_num_;

  // led color (default = white)
  uint8_t rgb_[3];
  uint8_t hls_[3];
  
  void SetHLSFromRGB();
  void SetRGBFromHLS();
};
