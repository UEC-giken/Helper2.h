#include "LED.h"

#define NUM_OF_LED 2
#define NUM_OF_PINS 2

Adafruit_NeoPixel AN_LED = Adafruit_NeoPixel(NUM_OF_LED, NUM_OF_PINS, NEO_RGB + NEO_KHZ800);

bool LED::on(){
  AN_LED.setPixelColor(led_num_, red_, green_, blue_);
  AN_LED.show();

  status_ = true;

  return status_;
}

bool LED::off(){
  AN_LED.setPixelColor(led_num_, 0x000000);
  AN_LED.show();
  status_ = false;

  return status_;
}

bool LED::flip(){
  if (status_){
    return off();
  }
  else {
    return on();
  }
}

bool LED::reflection(){
  if (status_) {
  	return on();
  }
}

// bool LED::getStatus(){
//   return status_;
// }

void LED::color(float hue) {
  hue_ = fmod(hue, 1.0);

  SetRGBFromHLS();
  reflection();
}

void LED::color(uint8_t red, uint8_t green, uint8_t blue) {
  red_ = fmod(red, 255);
  green_ = fmod(green, 255);
  blue_ = fmod(blue, 255);

  SetHLSFromRGB();
  reflection();
}

void LED::brightness(float brightness) {
  brightness_ = fmod(brightness, 1.0);

  SetRGBFromHLS();
  reflection();
}

void LED::saturation(float saturation) {
	saturation_ = fmod(saturation, 1.0);

	SetRGBFromHLS();
  reflection();
}

void LED::randomcolor() {
  color(static_cast<float>(random(1000)) / 1000);
  reflection();
}

void LED::stepcolor(float span) {
  color(hue_ + span);
}

bool LED::fadeIn(float span, float max, bool loop) {
  if (brightness_ + span < max || loop){
    brightness(brightness_ + span);
    status_ = true;
    return true;
  }

  return false;
}

bool LED::fadeOut(float span, float min, bool loop) {
  if (brightness_ - span > min || loop){
    brightness(brightness_ - span);
    status_ = true;
    return true;
  }
  else {
    status_ = false;
    return false;
  }
}

void LED::debugPrint(){
  Serial.print("led");
  Serial.print(led_num_);

  Serial.print("   RGB = ");
  Serial.print(red_);
  Serial.print(", ");
  Serial.print(green_);
  Serial.print(", ");
  Serial.print(blue_);

  Serial.print("   HLS = ");
  Serial.print(hue_);
  Serial.print(", ");
  Serial.print(brightness_);
  Serial.print(", ");
  Serial.println(saturation_);
}

void LED::SetHLSFromRGB() {
	float max = max(max(red_, green_), blue_);
	float min = min(min(red_, green_), blue_);

	float h;
	if (min == max)
		h = 0;
	else if (red_== max)
		h = 60 * ((green_- blue_) / (max - min));
	else if (green_== max)
		h = 60 * ((blue_- red_) / (max - min)) + 120;
	else if (blue_== max)
		h = 60 * ((red_- green_) / (max - min)) + 240;

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
    max = 255 * l * (1 + s);
    min = 255 * l * (1 - s);
  } else {
    max = 255 * (l + (1 - l) * s);
    min = 255 * (l - (1 - l) * s);
  }

  if (h < 60) {
    red_= max;
    green_= (h / 60) * (max - min) + min;
    blue_= min;
  } else if (h < 120) {
    red_= ((120 - h) / 60) * (max - min) + min;
    green_= max;
    blue_= min;
  } else if (h < 180) {
    red_= min;
    green_= max;
    blue_= ((h - 120) / 60) * (max - min) + min;
  } else if (h < 240) {
    red_= min;
    green_= ((240 - h) / 60) * (max - min) + min;
    blue_= max;
  } else if (h < 300) {
    red_= ((h - 240) / 60) * (max - min) + min;
    green_= min;
    blue_= max;
  } else {
    red_= max;
    green_= min;
    blue_= ((360-h) / 60) * (max - min) + min;
  }
}
