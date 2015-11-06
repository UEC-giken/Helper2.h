#include "Dot.h"

void Dot::move(byte x, byte y) {
  this->x = x;
  this->y = y;
};

void Dot::moveLeft() {
  if (1 < this->x) {
    this->x--;
  }
};

void Dot::moveRight() {
  if (this->x < 8) {
    this->x++;
  }
};

void Dot::moveUp() {
  if (this->y < 8) {
    this->y++;
  }
};

void Dot::moveDown() {
  if (1 < this->y) {
    this->y--;
  }
};

void Dot::show() {
  if (this->isFirst) {
    this->isFirst = false;
  } else {
    // 前回の show した時のドットを消す
    // もしかしたら他の描画と衝突するかもしれないです
    DotMatrix::setDot(this->old_y, this->old_x, 0);
  }

  DotMatrix::setDot(7 - (this->y - 1), 7 - (this->x - 1), 1);
  DotMatrix::show();

  this->old_x = 7 - (x - 1);
  this->old_y = 7 - (y - 1);
};

// void Dot::debug_show() {
//   printf("(%d, %d)\n", this->x, this->y);
// };
