#include <stdint.h>

#pragma once

class Accel {
  public:
    float x;
    float y;
    float z;

    // ここは getter にしたほうが良い?
    bool active;
    bool freefall;
    bool tap;
    bool doubletap;

    bool debug;

    Accel() : x(0), y(0), z(0), _last_size(0), _t_lasttap(0), debug(false),
              active(false), freefall(false), tap(false), doubletap(false) {
        for (int i=0; i<30; i++) {
            _x[i] = 0;
            _y[i] = 0;
            _z[i] = 0;
            _diff[i] = 0;
            _millis[i] = 0;
        }
    };

    // 値を追加するときはこれを呼ぶこと
    void addValue(float nx, float ny, float nz);

    void debug_show(int i);
  private:
    float _x[30];
    float _y[30];
    float _z[30];
    float _diff[30]; // 累積誤差
    float _last_size; // 前フレームの 過速度の大きさの二乗

    float _t_lasttap;

    int _millis[30]; // デバッグ用

    Accel(const Accel &other) {};
};
