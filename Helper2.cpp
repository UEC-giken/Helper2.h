// #include <Wire.h> // I2C用
#include <TimerOne.h> //timer1 //timer0はdelay、timer2はtoneで使われてる(´・ω・｀)
#include <ADXL345.h> // 加速度センサ用
// #include "dtmtdatas.h"

#include "Helper2_protected.h"
#include "LED.h"
#include "Accel.h"

Accel accel;

LED led1(0);
LED led2(1);

void initialize() {
  AN_LED.begin();
  accel.init();

  // ピン初期化
  // pinMode(2,OUTPUT);
  // digitalWrite(2,LOW);

  // タイマー1
  //割り込み周期[usec]//887@16MH動作//8Mhz動作なら単純に考えて倍
  Timer1.initialize(800);
  // Timer1.initialize(6000);
  Timer1.attachInterrupt(interrupt); //割り込みする関数

  // debug用
  // Serial.begin(9600);
  // Serial.println("started");

  delay(1000);//初期状態確認用
}

// loop() の中で呼ばれる
void wait(int16_t msec) {
  uint32_t start = millis();

  // bool is_tapped = false;
  // bool is_doubletapped = false;
  // bool is_active = false;
  // bool is_freefall = false;
  accel.resetFlag();

  while ((millis() - start) <= msec) {
    accel.updateData();

  //   if (accel.tap())
  //     is_tapped = true;
  //   if (accel.doubletap())
  //     is_doubletapped = true;
  //   if (accel.active())
  //     is_active = true;
  //   if (accel.freefall())
  //     is_freefall = true;
  }

  // accel.setTap(is_tapped);
  // accel.setDoubletap(is_doubletapped);
  // accel.setActive(is_active);
  // accel.setFreefall(is_freefall);
};

// timer1割り込みで走る関数
void interrupt() {
  // LEDの点滅とかはここでしても良いかも?

};
