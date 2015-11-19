// #include "Helper2_protected.h"
#include "Adafruit_NeoPixel.h"

#pragma once

extern Adafruit_NeoPixel AN_LED;

class LED {
public:
  LED(int8_t num):
    led_num_(num),
    status_(false),
    red_(255),
    green_(255),
    blue_(255),
    saturation_(1.0),
    brightness_(0.5),
    hue_(0)
  {};
  // LED(const LED& origin){
  //
  // };

  // return led status
  bool on();
  bool off();
  bool getStatus();

  // led の色相を変更する
  // 色相: 0.0-1.0
  void color(float hue);
  void color(uint8_t red, uint8_t green, uint8_t blue);

  // led の明るさを変更する
  // 明るさ: 0.0-1.0
  void brightness(float brightness);

  // led の彩度を変更する
  // 彩度 0.0-1.0
  void saturation(float saturation);

  // led の色をランダムに点灯する
  // void randomcolor();

private:
  // led status on = true, off = false
  bool status_;

  // led_num_ = {0, 1, }
  int8_t led_num_;

  // led color (default = white)
  uint8_t red_, green_, blue_;
  float saturation_, brightness_, hue_;

  // saturation_, brightness_, hue_ から RGB を算出し、 red_, green_, blue_ に代入する
  void SetHLSFromRGB();

  // red_, green_, blue_ から HLS を算出し、 saturation_, brightness_, hue_ に代入する
  void SetRGBFromHLS();

  // void SetHLSFromRGB(uint8_t r, uint8_t g, uint8_t b);
  // void SetRGBFromHLS(float s, float b, float h);
};

// class LED {
//   public:
//     byte x, y;
//
//     // LED() { this->isFirst = true; };
//
//
//     // led の色相を変更する
//     // 色相: 0.0-1.0
//     void color(int8_t led, float hue);
//
//
//     void brightness(int8_t led, float brightness);
//
//     // led の彩度を変更する
//     // 彩度 0.0-1.0
//     void saturation(int8_t led, float saturation);
//
//     // led の色をランダムに点灯する
//     void randomcolor(int8_t led);
//
//     // void debug_show();
//
//     LED(const LED &other) {};
//   private:
//     byte no;
// };
