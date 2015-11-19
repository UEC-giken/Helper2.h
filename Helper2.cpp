#include <Wire.h> // I2C用
#include <ADXL345.h> // 加速度センサ用
#include <TimerOne.h> //timer1 //timer0はdelay、timer2はtoneで使われてる(´・ω・｀)
// #include "dtmtdatas.h"

#include "Helper2_protected.h"
#include "LED.h"

Accel accel;


// val の値を min と max の値に収まるようにする
// val < min         :=> min
// min <= val <= max :=> val
// max < val         :=> max
float clamp(float val, float min, float max) {
  if (val < min) { return min; }
  if (max < val) { return max; }

  return val;
}

// I2C
// 直接接続だと 0x53, そうでないと 0x1D
#define ADXL345_ID 0x53

// 加速度センサ
ADXL345 adxl;

Accel accel;

LEDClass led1 = LEDClass(0);
LEDClass led2 = LEDClass(1);

void initialize() {
  accel = Accel();
  AN_LED.begin();


  // ピン初期化
  // pinMode(2,OUTPUT);
  // digitalWrite(2,LOW);

  // 加速度センサ初期化
  sendi2c(ADXL345_ID, 0x2C, 0b00001100); //3200Hz書き出し
  sendi2c(ADXL345_ID, 0x31, 0b00001000); //fullresmode
  initializeAccelerometer();

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

void updateData() {
  int count = 20, sumx = 0, sumy = 0, sumz = 0;
  int rawx = 0, rawy = 0, rawz = 0;
  // 水準器
  for(int i=0; i<count; i++){
    adxl.readAccel(&rawx, &rawy, &rawz);
    sumx += rawx;
    sumy += rawy;
    sumz += rawz;
  }

  // // sum(x, y, z) は -10240 - 10240 をとる?
  // // 1G で x, y: 4900, z: 4500 ぐらいの値をとる => 正規化して -1.0 - 1.0 に縮める
  // // by kyontan
  // // NOTE: 割る値 は適宜調整してください
  float x = clamp(-sumx / 4900.0, -1.0, 1.0);
  float y = clamp(-sumy / 4900.0, -1.0, 1.0);
  float z = clamp(-sumz / 4500.0, -1.0, 1.0);

  accel.x = x;
  accel.y = y;
  accel.z = z;
};

// loop() の中で呼ばれる
void wait(int16_t msec) {
  uint32_t start = millis();

  while ((millis() - start) < msec) {
    updateData();
  }
};

// timer1割り込みで走る関数
void interrupt() {
  // LEDの点滅とかはここでしても良いかも?

};

// I2C通信
void sendi2c(int8_t id, int8_t reg, int8_t data) {
  Wire.beginTransmission(id); // Adxl345 のアドレス: 0x1D
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
};

void initializeAccelerometer() {
  adxl.powerOn();

  adxl.setRangeSetting(2); //測定範囲
  // 動作した or してないの閾値を設定 (0-255)
  adxl.setActivityThreshold(75);    //値:*62.5[mg]
  adxl.setInactivityThreshold(75);  //値:*62.5[mg]
  adxl.setTimeInactivity(10);       //非動作の判定までに要する時間//値:*5[ms]

  // 動作したかを監視する軸の設定 (1 == on; 0 == off)
  //各軸の判定の論理和
  adxl.setActivityX(1);
  adxl.setActivityY(1);
  adxl.setActivityZ(1);

  // 動作してないを監視する軸の設定 (1 == on; 0 == off)
  //各軸の判定の論理積
  adxl.setInactivityX(1);
  adxl.setInactivityY(1);
  adxl.setInactivityZ(1);

  // タップされたことを検視する軸の設定 (1 == on; 0 == off)
  adxl.setTapDetectionOnX(0);
  adxl.setTapDetectionOnY(0);
  adxl.setTapDetectionOnZ(0);

  // タップ,ダブルタップに関数る閾値の設定 (0-255)
  adxl.setTapThreshold(80);         //値:*62.5[mg]
  adxl.setTapDuration(15);          //値:*625[μs]
  adxl.setDoubleTapLatency(80);     //値:*1.25[ms]
  adxl.setDoubleTapWindow(200);     //値:*1.25[ms]

  // 自由落下に関する閾値の設定 (0-255)
  //閾値と時間の論理積
  adxl.setFreeFallThreshold(0x09);  //閾値//(0x05 - 0x09) 推薦 - 値:*62.5[mg]
  adxl.setFreeFallDuration(0x0A);   //時間//(0x14 - 0.46) 推薦 - 値:*5[ms]

  //setting all interupts to take place on int pin 1
  //I had issues with int pin 2, was unable to reset it
  adxl.setInterruptMapping( ADXL345_INT_SINGLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_DOUBLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_FREE_FALL_BIT,    ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT,     ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_INACTIVITY_BIT,   ADXL345_INT1_PIN );

  //register interupt actions - 1 == on; 0 == off
  adxl.setInterrupt( ADXL345_INT_SINGLE_TAP_BIT, 0);
  adxl.setInterrupt( ADXL345_INT_DOUBLE_TAP_BIT, 0);
  adxl.setInterrupt( ADXL345_INT_FREE_FALL_BIT,  0);
  adxl.setInterrupt( ADXL345_INT_ACTIVITY_BIT,   0);
  adxl.setInterrupt( ADXL345_INT_INACTIVITY_BIT, 0);
}
