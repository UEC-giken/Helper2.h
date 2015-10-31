#include <Arduino.h>
#include "Buzzer.h"
#define BUZZER 12

// Buzzer.cpp
Buzzer &Buzzer::getInstance() {
  static Buzzer instance;
  return instance;
};

void Buzzer::tone(unsigned int frequency) {
  ::tone(BUZZER, frequency);
};

void Buzzer::tone(unsigned int frequency, unsigned long duration) {
  ::tone(BUZZER, frequency, duration);
};

void Buzzer::stop() {
  ::noTone(BUZZER);
};
