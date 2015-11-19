#include <stdbool.h>
#include <stdint.h>

#pragma once

#include "Accel.h"

// #include "LED.h"

// extern LED led1;
// extern LED led2;

extern Accel accel;

void initialize();
void initializeAccelerometer();

void updateData();

// デバッグ用 (led の現在標示中の色に関する値を返す)
double color(int led);
double brightness(int led);
double saturation(int led);

// led をレインボーに表示する。
// speed は 100
// void rainbow(int led, double period);

// led を period 秒間隔で点滅させる
// void blink(int led, double period);

// void fadein(int led, double period);
// void fadeout(int led, double period);

void on(int led);
void off(int led);
