#include <stdint.h>

#pragma once

class Accel {
  public:
    float x;
    float y;
    float z;

    // ここは getter にしたほうが良い?
    bool active;
    bool freefall;
    bool tap;
    bool doubletap;

    Accel() {
        this->x = 0;
        this->y = 0;
        this->z = 0;

        this->active = false;
        this->freefall = false;
        this->tap = false;
        this->doubletap = false;
    };
  private:
    Accel(const Accel &other) {};
};
