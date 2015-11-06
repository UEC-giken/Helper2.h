#include "Accel.h"

Accel &Accel::getInstance() {
  static Accel instance;
  return instance;
};

int8_t Accel::x() {
    Accel &a = Accel::getInstance();
    return a._x;
};

int8_t Accel::y() {
  Accel &a = Accel::getInstance();
  return a._y;
};

int8_t Accel::z() {
  Accel &a = Accel::getInstance();
  return a._z;
};

void Accel::updateAccel(int8_t *x, int8_t *y, int8_t *z) {
  Accel &a = Accel::getInstance();
  a._x = *x;
  a._y = *y;
  a._z = *z;
};