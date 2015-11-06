#pragma once

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
