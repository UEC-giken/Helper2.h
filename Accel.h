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

    void resetFlags();
    void updateFlags();

    bool debug;

    Accel(float a = 0.02, float b = 0.20, float c = 0.02, long int d = 130, long int e = 200) :
      _ThMaxAtFrameA(a),
      _ThMinAtFrameB(b),
      _ThMaxAtLatastFrame(c),
      _ThMaximumSingleTapSpace(d),
      _ThMaximumDoubleTapSpace(e),
      _last_size(0), _t_lasttap(0), debug(false),
      _active(false), _freefall(false), _tap(false), _doubletap(false),
      _head_frame(0), _half_frame(n_frames / 2), _last_frame(n_frames - 1)
    {
      for (int i=0; i<30; i++) {
        _x[i] = 0;
        _y[i] = 0;
        _z[i] = 0;
        _diff[i] = 0;
        _millis[i] = 0;
      }
    }

    void init();
    void updateAccel();

    void debugPrint(int i);
    void debugPrintThreshold();
    void debugInputThreshold();

  private:
    float _ThMaxAtFrameA;
    float _ThMinAtFrameB;
    float _ThMaxAtLatastFrame;
    long int _ThMaximumSingleTapSpace;
    long int _ThMaximumDoubleTapSpace;

    // 加速度センサ
    ADXL345 adxl;

    bool _active;
    bool _freefall;
    bool _tap;
    bool _doubletap;

    // 累積データ配列のシフトされた最初・最後の位置
    int _head_frame;
    int _half_frame;
    int _last_frame;
    
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

    // 新しい加速度の値を追加し、最も古い加速度の値を削除します。
    void shiftValue(float nx, float ny, float nz);

    void sendi2c(int8_t id, int8_t reg, int8_t data);
    static float clamp(float val, float min, float max);
};
