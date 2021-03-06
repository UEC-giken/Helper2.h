#include <Adafruit_NeoPixel.h>

#pragma once

extern Adafruit_NeoPixel AN_LED;

class LED {
public:
  LED(int8_t num):
  led_num_(num), status_(false),
  saturation_(0.7), brightness_(0.3), hue_(0.0) {
    SetRGBFromHLS();
  }

  // return led status
  bool on();
  bool off();
  bool flip();
  // bool getStatus();

  // led の色相を変更する
  // 色相: 0.0-1.0
  void color(uint8_t red, uint8_t green, uint8_t blue);
  void color(float hue);

  // led の明るさを変更する
  // 明るさ: 0.0-1.0
  void brightness(float brightness);

  // led の彩度を変更する
  // 彩度 0.0-1.0
  void saturation(float saturation);

  // led の色をランダムに点灯する
  void randomColor();
  void stepColor(float span = 0.005);

  // fade brightness
  // return minまたはmaxに達したときにfalse
  bool fadeIn (float span = 0.02, float max = 0.5, bool loop = false);
  bool fadeOut(float span = 0.02, float min = 0.0, bool loop = false);

  // RGB と HLS の色情報をプリントする
  void debugPrint();

private:
  // led status on = true, off = false
  bool status_;

  // led_num_ = {0, 1, }
  const uint8_t led_num_;

  // led color (default = white)
  uint8_t red_, green_, blue_;
  float saturation_, brightness_, hue_;

  LED(const LED& origin) :
  led_num_(origin.led_num_)
  {}

  bool reflection();
  void SetHLSFromRGB();
  void SetRGBFromHLS();
};
