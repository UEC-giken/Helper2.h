#pragma once

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
