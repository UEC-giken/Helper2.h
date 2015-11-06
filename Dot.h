#pragma once

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
