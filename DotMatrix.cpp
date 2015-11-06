#include "DotMatrix.h"

DotMatrix &DotMatrix::getInstance() {
  static DotMatrix instance;
  return instance;
};

void DotMatrix::show() {
  DotMatrix &dt = DotMatrix::getInstance();
  ///*
  for(int r=0; r<8; r++) {
    digitalWrite(rowpin[r], HIGH);

    for(int c=0; c<8; c++) {
      //digitalWrite(colpin[c], DotMatrix::getDot(7-r,c) ? LOW : HIGH);
      digitalWrite(colpin[c], DotMatrix::getDot(c,r) ? LOW : HIGH);
    }

    for(int c=0; c<8; c++) {
      digitalWrite(colpin[c], HIGH);
    }

    digitalWrite(rowpin[r], LOW);
  }//*/
  /*
  for(int r = 0;r<8;r++)
{
  for(int c = 0;c<8;c++)
  {
    if( DotMatrix::getDot(7-c,7-r) )
    {
        digitalWrite(rowpin[r],HIGH);
        digitalWrite(colpin[c],LOW);
        //一瞬つける
        //無理やり残像を作るこの強引さ
        digitalWrite(colpin[c],HIGH);
        digitalWrite(rowpin[r],LOW);
    }
  }//col
}//row*/
};

void DotMatrix::reset() {
  DotMatrix &dt = DotMatrix::getInstance();
  Timer1.stop();
  for(int r=0; r<8; r++) {
    dt.data[r] = 0;
  }
  dt.show();
  Timer1.resume();
};

bool DotMatrix::getDot(byte x, byte y) {
  DotMatrix &dt = DotMatrix::getInstance();
  //return dt.data[x] & (1 << y);
  return dt.data[7-x] & (1 << (7-y));
};

void DotMatrix::setDot(byte x, byte y, byte dot) { // dot: 0 or 1
  DotMatrix &dt = DotMatrix::getInstance();

  if (dot == 1) {
    dt.data[x] |= 1 << y;
  } else { // 0
    dt.data[x] &= ~(1 << y);
  }
};

void DotMatrix::setRow(byte row, byte data) {
  DotMatrix &dt = DotMatrix::getInstance();
  dt.data[row] = data;
};