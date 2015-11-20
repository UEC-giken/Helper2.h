#include <stdint.h>

#pragma once

#include "Accel.h"
#include "LED.h"

extern LED led1;
extern LED led2;

extern Accel accel;

void initialize();

void wait(int16_t msec);
