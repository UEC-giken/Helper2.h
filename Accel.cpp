#include <Arduino.h>
#include <Wire.h> // I2C用
#include <ADXL345.h> // 加速度センサ用
#include "Accel.h"

// val の値を min と max の値に収まるようにする
// val < min         :=> min
// min <= val <= max :=> val
// max < val         :=> max
float clamp(float val, float min, float max) {
  if (val < min) { return min; }
  if (max < val) { return max; }

  return val;
}

float Accel::x() {
  return _x[29];
};

float Accel::y() {
  return _y[29];
};

float Accel::z() {
  return _z[29];
};


bool Accel::active() {
  return _active;
};

bool Accel::freefall() {
  return _freefall;
};

bool Accel::tap() {
  return _tap;
};

bool Accel::doubletap() {
  return _doubletap;
};

void Accel::setActive(bool new_active) {
  _active = new_active;
};

void Accel::setFreefall(bool new_freefall) {
  _freefall = new_freefall;
};

void Accel::setTap(bool new_tap) {
  _tap = new_tap;
};

void Accel::setDoubletap(bool new_doubletap) {
  _doubletap = new_doubletap;
};


void Accel::addValue(float nx, float ny, float nz) {
  for (int i=0; i<29; i++) {
      _x[i] = _x[i+1];
      _y[i] = _y[i+1];
      _z[i] = _z[i+1];
      _diff[i] = _diff[i+1];
      _millis[i] = _millis[i+1];
  }

  _x[29] = nx;
  _y[29] = ny;
  _z[29] = nz;
  _millis[29] = millis();

  float new_size = nx*nx + ny*ny + nz*nz;
  _diff[29] = abs(new_size - _last_size);
  _last_size = new_size;

  _active = false;
  _freefall = false;
  _tap = false;
  _doubletap = false;

  // 検出をゆるくするため、数フレームほど比較する
  if (0.1 < abs(_diff[29] - _diff[28]) ||
      0.1 < abs(_diff[29] - _diff[27]) ||
      0.1 < abs(_diff[29] - _diff[26]) ||
      0.1 < abs(_diff[29] - _diff[25])) {
    _active = true;
  }

  if (_last_size < 0.2) {
    _freefall = true;
  }

  /**
  * 設定すべき値は a-e, p-r の8つ
  *
  * 前提として、加速度 (x, y, z) をそれぞれ30フレーム(回分)保持する
  *
  * 加速度の大きさ^2 = x^2 + y^2 + z^2 とする。
  * 変化量 = 現在のフレームの(加速度の大きさ^2) - 直前フレームの(加速度の大きさ^2) とする。
  * a フレーム前の変化量が p 未満​ かつ ​b フレーム前の変化量が q 以上​ かつ ​最新フレームの変化量が r 未満​ でタップ検知とする
  *
  * ダブルタップ検知については
  * d フレーム以内にあったタップは 同タップとする (ダブルタップとは検知しない)
  * d フレーム以上離れたタップを ダブルタップとする
  * e フレーム以上離れたタップは異なるタップとする  (ダブルタップとは検知しない)
  */
  if (_diff[0] < _TH_A && _TH_B < _diff[15] && _diff[29] < _TH_C) {
    long int t_diff = millis() - _t_lasttap;

    if (debug) {
      Serial.print("time diff: ");
      Serial.print(t_diff);
      Serial.print("  ");
    }

    if (_TH_D < t_diff) {
      _tap = true;

      if (t_diff < _TH_E) {
        _doubletap = true;
      }

      _t_lasttap = millis();
    }

    if (debug) {
      if (_doubletap) {
        Serial.print("doubletapped, _diff[15] = ");
        Serial.println(_diff[15], 2);
      } else if (_tap) {
        Serial.print("tapped, _diff[15] = ");
        Serial.println(_diff[15], 2);
      } else {
        Serial.println("ignored");
      }
    }
  }
}

void Accel::debug_print(int i) {
  Serial.print("(");
  Serial.print(_x[i], 2);
  Serial.print(", ");
  Serial.print(_y[i], 2);
  Serial.print(", ");
  Serial.print(_z[i], 2);
  Serial.print(", ");
  Serial.print(_diff[i], 2);
  Serial.print(")");
}

// I2C通信
void Accel::sendi2c(int8_t id, int8_t reg, int8_t data) {
  Wire.beginTransmission(id); // Adxl345 のアドレス: 0x1D
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
};

void Accel::initializeAccelerometer() {
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

void Accel::updateData() {
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

  addValue(x, y, z);
};
