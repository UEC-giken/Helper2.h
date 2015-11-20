#include <stdint.h>
#include <ADXL345.h> // 加速度センサ用

#pragma once

// I2C
// 直接接続だと 0x53, そうでないと 0x1D
const uint8_t ADXL345_ID = 0x53;
const uint8_t n_frames = 30;

class Accel {
  public:
    float x();
    float y();
    float z();

    bool active();
    bool freefall();
    bool tap();
    bool doubletap();

    void setActive(bool new_active);
    void setFreefall(bool new_freefall);
    void setTap(bool new_tap);
    void setDoubletap(bool new_doubletap);

    bool debug;

    Accel(float a = 0.02, float b = 0.20, float c = 0.02, float d = 130, float e = 200) :
      _ThMaxAtFrameA(a),
      _ThMinAtFrameB(b),
      _ThMaxAtLatastFrame(c),
      _ThMaximumSingleTapSpace(d),
      _ThMaximumDoubleTapSpace(e),
      _last_size(0), _t_lasttap(0), debug(false),
      _active(false), _freefall(false), _tap(false), _doubletap(false)
    {
      // // 加速度センサ初期化
      // sendi2c(ADXL345_ID, 0x2C, 0b00001100); //3200Hz書き出し
      // sendi2c(ADXL345_ID, 0x31, 0b00001000); //fullresmode
      // initializeAccelerometer();

      for (int i=0; i<30; i++) {
        _x[i] = 0;
        _y[i] = 0;
        _z[i] = 0;
        _diff[i] = 0;
        _millis[i] = 0;
      }
    }

    // 値を追加するときはこれを呼ぶこと
    void updateData();
    void addValue(float nx, float ny, float nz);
    void init();

    void debug_print(int i);

  private:
    const float _ThMaxAtFrameA;
    const float _ThMinAtFrameB;
    const float _ThMaxAtLatastFrame;
    const float _ThMaximumSingleTapSpace;
    const float _ThMaximumDoubleTapSpace;

    // 加速度センサ
    ADXL345 adxl;

    bool _active;
    bool _freefall;
    bool _tap;
    bool _doubletap;

    float _x[n_frames];
    float _y[n_frames];
    float _z[n_frames];
    float _diff[n_frames]; // 累積誤差
    float _last_size; // 前フレームの 過速度の大きさの二乗

    float _t_lasttap;

    int _millis[n_frames]; // デバッグ用

    Accel(const Accel &other) :
      _ThMaxAtFrameA(other._ThMaxAtFrameA),
      _ThMinAtFrameB(other._ThMinAtFrameB),
      _ThMaxAtLatastFrame(other._ThMaxAtLatastFrame),
      _ThMaximumSingleTapSpace(other._ThMaximumSingleTapSpace),
      _ThMaximumDoubleTapSpace(other._ThMaximumDoubleTapSpace)
    {}

    void sendi2c(int8_t id, int8_t reg, int8_t data);
    void initializeAccelerometer();

};
