#pragma once

#include "Helper2.h"
#include "LED.h"

void interrupt();
void sendi2c(int8_t id, int8_t reg, int8_t data);
