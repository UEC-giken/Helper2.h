#include <ADXL345.h> // 加速度センサ用

#include "Helper2.h"
#include "LED.h"
#include "Accel.h"

Accel accel;

LED led1(0);
LED led2(1);

void initialize() {
  Serial.begin(9600);
  AN_LED.begin();
  accel.init();

  // ピン初期化
  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);

  delay(500); // 初期状態確認用
}

// loop() の中で呼ばれる
void wait(int16_t msec) {
  uint32_t start = millis();

  accel.resetFlags();

  while ((millis() - start) <= msec) {
    accel.updateAccel();
    accel.updateFlags();
  }
};
