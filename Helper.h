#pragma once

#include <stdbool.h>
#include "Dot.h"
#include "Image.h"
#include "DotMatrix.h"
#include "Accel.h"

// #include <stdint.h>

// typedef int8_t byte;

void initialize();
void initializeAccelerometer();

void updateData();

void interrupt();
void sendi2c(byte id, byte reg, byte data);
