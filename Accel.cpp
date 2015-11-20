#include <Arduino.h>
#include <Wire.h> // I2C用
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
  return _x[n_frames-1];
};

float Accel::y() {
  return _y[n_frames-1];
};

float Accel::z() {
  return _z[n_frames-1];
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

void Accel::resetFlag() {
  _active = false;
  _freefall = false;
  _tap = false;
  _doubletap = false;
}

void Accel::addValue(float nx, float ny, float nz) {
  for (int i=0; i<n_frames-1; i++) {
      _x[i] = _x[i+1];
      _y[i] = _y[i+1];
      _z[i] = _z[i+1];
      _diff[i] = _diff[i+1];
      _millis[i] = _millis[i+1];
  }

  _x[n_frames-1] = nx;
  _y[n_frames-1] = ny;
  _z[n_frames-1] = nz;
  _millis[n_frames-1] = millis();

  float new_size = nx*nx + ny*ny + nz*nz;
  _diff[n_frames-1] = abs(new_size - _last_size);
  _last_size = new_size;

  // 検出をゆるくするため、数フレームほど比較する
  if (0.1 < abs(_diff[n_frames-1] - _diff[28]) ||
      0.1 < abs(_diff[n_frames-1] - _diff[27]) ||
      0.1 < abs(_diff[n_frames-1] - _diff[26]) ||
      0.1 < abs(_diff[n_frames-1] - _diff[25])) {
    _active = true;
  }

  if (_last_size < 0.2) {
    _freefall = true;
  }

  /**
  * 設定すべき値は 以下の8つです ([]内は単位)
  *
  * - ThFrameA [frame]
  * - ThFrameB [frame]
  *
  * - ThMaxAtFrameA [(m/s^2)^2]
  * - ThMinAtFrameB [(m/s^2)^2]
  * - ThMaxAtLatastFrame [(m/s^2)^2]
  *
  * - ThMaximumSingleTapSpace [ms]
  * - ThMaximumDoubleTapSpace [ms]
  *
  * 前提として、加速度 (x, y, z) をそれぞれn_frames回(フレーム)分保持する
  *
  * 変化量 = |現在のフレームの加速度|^2 - |直前フレームの加速度|^2 とする。
  * タップ検知: 以下の3条件を満たした時にタップ検知とする
  * - (ThFrameA フレーム前の変化量) < ThMaxAtFrameA
  * - ThMinAtFrameB < (ThFrameB フレーム前の変化量)
  * - (最新フレームの変化量) < ThMaxAtLatastFrame
  *
  * ダブルタップ検知:
  * - ThMaximumSingleTapSpace フレーム以内にあったタップは 同タップとする (ダブルタップとは検知しない)
  * - ThMaximumSingleTapSpace フレーム以上離れたタップを ダブルタップとする
  * - ThMaximumDoubleTapSpace フレーム以上離れたタップは 異なるタップとする  (ダブルタップとは検知しない)
  */
  if (_diff[0] < _ThMaxAtFrameA && _ThMinAtFrameB < _diff[15] && _diff[n_frames-1] < _ThMaxAtLatastFrame) {
    long int t_diff = millis() - _t_lasttap;

    if (debug) {
      Serial.print("time diff: ");
      Serial.print(t_diff);
      Serial.print("  ");
    }

    if (_ThMaximumSingleTapSpace < t_diff) {
      _tap = true;

      if (t_diff < _ThMaximumDoubleTapSpace) {
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

void Accel::init() {
  // 加速度センサ の 初期化
  sendi2c(ADXL345_ID, 0x2C, 0b00001100); // 3200Hz 書き出し
  sendi2c(ADXL345_ID, 0x31, 0b00001000); // full resolution mode

  adxl.powerOn();

  adxl.setRangeSetting(2); // 測定範囲 (何G まで測定するか)

  // 動作したかを監視する軸の設定 (1 == on; 0 == off)
  //各軸の判定の論理和
  adxl.setActivityX(0);
  adxl.setActivityY(0);
  adxl.setActivityZ(0);

  // 動作してないを監視する軸の設定 (1 == on; 0 == off)
  // 各軸の判定の論理積
  adxl.setInactivityX(0);
  adxl.setInactivityY(0);
  adxl.setInactivityZ(0);

  // タップされたことを検視する軸の設定 (1 == on; 0 == off)
  adxl.setTapDetectionOnX(0);
  adxl.setTapDetectionOnY(0);
  adxl.setTapDetectionOnZ(0);

  // setting all interupts to take place on int pin 1
  // I had issues with int pin 2, was unable to reset it
  adxl.setInterruptMapping(ADXL345_INT_SINGLE_TAP_BIT, ADXL345_INT1_PIN);
  adxl.setInterruptMapping(ADXL345_INT_DOUBLE_TAP_BIT, ADXL345_INT1_PIN);
  adxl.setInterruptMapping(ADXL345_INT_FREE_FALL_BIT,  ADXL345_INT1_PIN);
  adxl.setInterruptMapping(ADXL345_INT_ACTIVITY_BIT,   ADXL345_INT1_PIN);
  adxl.setInterruptMapping(ADXL345_INT_INACTIVITY_BIT, ADXL345_INT1_PIN);

  // register interupt actions - 1 == on; 0 == off
  adxl.setInterrupt(ADXL345_INT_SINGLE_TAP_BIT, 0);
  adxl.setInterrupt(ADXL345_INT_DOUBLE_TAP_BIT, 0);
  adxl.setInterrupt(ADXL345_INT_FREE_FALL_BIT,  0);
  adxl.setInterrupt(ADXL345_INT_ACTIVITY_BIT,   0);
  adxl.setInterrupt(ADXL345_INT_INACTIVITY_BIT, 0);
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


}
