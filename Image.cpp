#include "Image.h"

void Image::rotateLeft() {
  byte new_row[8][8];
  for (int i=0; i<8; i++) {
    for (int j=0; j<8; j++) {
      new_row[i][j] = this->getDot(j, 7-i);
    }
  }

  for (int i=0; i<8; i++) {
    for (int j=0; j<8; j++) {
      this->setDot(i, j, new_row[i][j]);
    }
  }
};

void Image::rotateRight() {
  byte new_row[8][8];
  for (int i=0; i<8; i++) {
    for (int j=0; j<8; j++) {
      new_row[i][j] = this->getDot(7-j, i);
    }
  }

  for (int i=0; i<8; i++) {
    for (int j=0; j<8; j++) {
      this->setDot(i, j, new_row[i][j]);
    }
  }
};


void Image::mirrorHorizontal() {
  byte new_row[8][8];
  for (int i=0; i<8; i++) {
    for (int j=0; j<8; j++) {
      new_row[i][j] = this->getDot(i, 7-j);
    }
  }

  for (int i=0; i<8; i++) {
    for (int j=0; j<8; j++) {
      this->setDot(i, j, new_row[i][j]);
    }
  }
};

void Image::mirrorVertical() {
  byte new_row[8][8];
  for (int i=0; i<8; i++) {
    for (int j=0; j<8; j++) {
      new_row[i][j] = this->getDot(7-i, j);
    }
  }

  for (int i=0; i<8; i++) {
    for (int j=0; j<8; j++) {
      this->setDot(i, j, new_row[i][j]);
    }
  }
};

void Image::show() {
  for (int i=0; i<8; i++) {
    DotMatrix::setRow(i, this->row[i]);
  }

  DotMatrix::show();
};

bool Image::getDot(byte x, byte y) {
  return this->row[x] & (1 << y);
};

void Image::setDot(byte x, byte y, byte dot) { // dot: 0 or 1
  if (dot == 1) {
    this->row[x] |= 1 << y;
  } else { // 0
    this->row[x] &= ~(1 << y);
  }
};

// void Image::debug_show() {
//   for (int i=0; i<8; i++) {
//     for (int j=0; j<8; j++) {
//       printf("%d", this->getDot(i, j));
//     }
//     printf("\n");
//   }
// };
