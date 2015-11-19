#include "LED.h"

#define NUM_OF_LED 2
#define NUM_OF_PINS 2

Adafruit_NeoPixel AN_LED = Adafruit_NeoPixel(NUM_OF_LED, NUM_OF_PINS, NEO_RGB + NEO_KHZ800);

// must initialize with begin() and show()

// void Dot::debug_show() {
//   printf("(%d, %d)\n", this->x, this->y);
// };

bool LED::on() {
  AN_LED.setPixelColor(led_num_, red_, green_, blue_);
  AN_LED.show();

  status_ = true;

  return status_;
}

bool LED::off() {
  AN_LED. setPixelColor(led_num_, 0x000000);
  AN_LED.show();
  status_ = false;

  return status_;
}

// bool LED::getStatus() {
//   return status_;
// }
//
void LED::color(float hue) {
  hue_ = fmod(hue, 360);

  SetRGBFromHLS();

  if (status_) {
  	on();
  }
}

void LED::color(uint8_t red, uint8_t green, uint8_t blue) {
  red_ = red;
  green_ = green;
  blue_ = blue;

  SetHLSFromRGB();

  if (status_) {
    on();
  }
}

void LED::brightness(float brightness) {
  brightness_ = brightness;

  SetRGBFromHLS();

  if (status_) {
  	on();
  }
}
//
void LED::saturation(float saturation) {
	saturation_ = saturation;

	SetRGBFromHLS();

	if (status_) {
		on();
	}
}
//
// void LED::randomcolor() {
//
// }

void LED::SetHLSFromRGB() {
	float r = red_;
	float g = green_;
	float b = blue_;

	float max = max(max(r, g), b);
	float min = min(min(r, g), b);

	float h;
	if (r == g && g == b)
		h = 0;
	else if (r == max)
		h = 60 * ((g - b) / (max - min));
	else if (g == max)
		h = 60 * ((b - r) / (max - min)) + 120;
	else if (b == max)
		h = 60 * ((r - g) / (max - min)) + 240;


	hue_ = fmod(h, 360) / 360;

	saturation_ = (max - min) / max;
	brightness_ = max / 255.0;
}

void LED::SetRGBFromHLS() {
  float s = saturation_;
  float l = brightness_;
  float h = hue_ * 360; // 0 - 360

  float max, min;
  if (l < 0.5) {
    max = 255 * l * (s + 1);
    min = 255 * l * (s - 1);
  } else {
    max = 255 * (l + (1 - l) * s);
    min = 255 * (l - (1 - l) * s);
  }

  uint8_t r, g, b;

  if (h < 60) {
    r = max;
    g = (h / 60) * (max - min) + min;
    b = min;
  } else if (h < 120) {
    r = ((120 - h) / 60) * (max - min) + min;
    g = max;
    b = min;
  } else if (h < 180) {
    r = min;
    g = max;
    b = ((h - 120) / 60) * (max - min) + min;
  } else if (h < 240) {
    r = min;
    g = ((240 - h) / 60) * (max - min) + min;
    b = max;
  } else if (h < 300) {
    r = ((h - 240) / 60) * (max - min) + min;
    g = min;
    b = max;
  } else {
    r = max;
    g = min;
    b = ((360-h) / 60) * (max - min) + min;
  }

  red_ = r;
  green_ = g;
  blue_ = b;
}
