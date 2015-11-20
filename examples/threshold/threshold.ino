#include <Helper2.h>
// #include <Wire.h>
// #include <TimerOne.h>

void setup() {
	Serial.begin(9600);
	initialize();

	led1.on();
	led2.color(0);
	led2.off();
	led2.color(0.5);
}

void loop() {
	if (accel.tap()) {
		led1.randomcolor();
	}

	if (accel.doubletap()) {
		led2.flip();
	}
	
	accel.debug_threshold();

	wait(200);
};
