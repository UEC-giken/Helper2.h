#include "Helper2_protected.h"

#pragma once

class Accel {
  public:
    int8_t x;
    int8_t y;
    int8_t z;

    // ここは getter にしたほうが良い?
    bool active;
    bool freefall;
    bool tap;
    bool doubletap;

    Accel() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    };
  private:
    Accel(const Accel &other) {};
};
