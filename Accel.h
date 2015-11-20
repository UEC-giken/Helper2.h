#include <stdint.h>

#pragma once

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

    Accel(float a = 0.02, float b = 0.28, float c = 0.02, float d = 100, float e = 400) :
      _TH_A(a), _TH_B(b), _TH_C(c), _TH_D(d), _TH_E(e), 
      _last_size(0), _t_lasttap(0), debug(false),
      _active(false), _freefall(false), _tap(false), _doubletap(false)
    {
        for (int i=0; i<30; i++) {
            _x[i] = 0;
            _y[i] = 0;
            _z[i] = 0;
            _diff[i] = 0;
            _millis[i] = 0;
        }
    }

    // 値を追加するときはこれを呼ぶこと
    void addValue(float nx, float ny, float nz);

    void debug_print(int i);
  private:
    const float _TH_A;
    const float _TH_B;
    const float _TH_C;
    const float _TH_D;
    const float _TH_E;
      
    bool _active;
    bool _freefall;
    bool _tap;
    bool _doubletap;

    float _x[30];
    float _y[30];
    float _z[30];
    float _diff[30]; // 累積誤差
    float _last_size; // 前フレームの 過速度の大きさの二乗

    float _t_lasttap;

    int _millis[30]; // デバッグ用

    Accel(const Accel &other) : 
      _TH_A(other._TH_A), _TH_B(other._TH_B), _TH_C(other._TH_C), _TH_D(other._TH_D), _TH_E(other._TH_E) 
    {}
};
