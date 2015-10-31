#pragma once

#include <stdbool.h>

// #include <stdint.h>

// typedef int8_t byte;

void initialize();
void initializeAccelerometer();

void updateData();

void interrupt();
void sendi2c(byte id, byte reg, byte data);

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

class DotMatrix {
  public:
    byte data[8];

    static DotMatrix &getInstance();

    static void show(); // 表示に反映させる
    static void reset(); // 全消し
    static bool getDot(byte x, byte y);
    static void setDot(byte x, byte y, byte dot); // dot: 0 or 1
    static void setRow(byte row, byte data);

  private:
    DotMatrix() {};
    DotMatrix(const DotMatrix &other) {};
};

class Dot {
  public:
    byte x, y;

    Dot() { this->isFirst = true; };
    Dot(byte x, byte y) {
      this->x = x;
      this->y = y;
      this->isFirst = true;
    };

    void move(byte x, byte y);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void show();

    // void debug_show();

    Dot(const Dot &other) {};
  private:
    bool isFirst;
    byte old_x, old_y;
};

class Image {
  public:
    byte row[8];

    Image() {};
    Image(byte r1, byte r2, byte r3, byte r4,
        byte r5, byte r6, byte r7, byte r8) {
      this->row[0] = r1;
      this->row[1] = r2;
      this->row[2] = r3;
      this->row[3] = r4;
      this->row[4] = r5;
      this->row[5] = r6;
      this->row[6] = r7;
      this->row[7] = r8;
    };

    Image(const Image &other) {};

    void rotateLeft();
    void rotateRight();

    void mirrorHorizontal();
    void mirrorVertical();

    void show();

    // void debug_show();

  private:
    bool getDot(byte x, byte y);
    void setDot(byte x, byte y, byte dot); // dot: 0 or 1
};
