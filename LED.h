#include "Helper2_protected.h"

#pragma once

class LED {
  public:
    byte x, y;

    // LED() { this->isFirst = true; };
    LED(byte led_no) {
      this->no = led_no;
    };

    // led の色相を変更する
    // 色相: 0.0-1.0
    void color(int led, double hue);

    // led の明るさを変更する
    // 明るさ: 0.0-1.0
    void brightness(int led, double brightness);

    // led の彩度を変更する
    // 彩度 0.0-1.0
    void saturation(int led, double saturation);

    // led の色をランダムに点灯する
    void randomcolor(int led);

    // void debug_show();

    LED(const LED &other) {};
  private:
    byte no;
};
