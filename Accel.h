#pragma once

class Accel {
  public:
    static int8_t x();
    static int8_t y();
    static int8_t z();

    static void updateAccel(int8_t *x, int8_t *y, int8_t *z);

    static Accel &getInstance();

  private:
    int8_t _x, _y, _z;

    Accel() {};
    Accel(const Accel &other) {};
};
