#include <Arduino.h>
#include "Accel.h"

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
  if (Serial.available() > 0){
    uint8_t j = 1, length = Serial.available();
    int8_t p[10] = {0};
    
    char string[length+10];
    for (uint8_t i = 0; i < length; i++){
      string[i] = Serial.read();
      if ((string[i] < '0' || string[i] > '9') && string[i] != '.'){
        string[i] = '\0';
        if (string[i-1] == '\0'){
          j--;
        }
        
        p[j] = i + 1;
        j++;
      }
    }
    
    if (j == 5){
      _TH_A = atof(&(string[p[0]]));
      _TH_B = atof(&(string[p[1]]));
      _TH_C = atof(&(string[p[2]]));
      _TH_D = atof(&(string[p[3]]));
      _TH_E = atof(&(string[p[4]]));
    }
    
    Serial.print("_TH_A : ");
    Serial.print(_TH_A);
    Serial.print(" _TH_B : ");
    Serial.print(_TH_B);
    Serial.print(" _TH_C : ");
    Serial.print(_TH_C);
    Serial.print(" _TH_D : ");
    Serial.print(_TH_D);
    Serial.print(" _TH_E : ");
    Serial.println(_TH_E);
  }

  if (i != -1){
    Serial.print("(");
    Serial.print(_x[i], 2);
    Serial.print(", ");
    Serial.print(_y[i], 2);
    Serial.print(", ");
    Serial.print(_z[i], 2);
    Serial.print(", ");
    Serial.print(_diff[i], 2);
    Serial.println(")");
  }
}