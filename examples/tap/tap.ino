#include <Helper2.h>
#include <Wire.h>
#include <TimerOne.h>

void setup() {
	initialize();

	led1.on();
	led1.color(10, 10, 0);
	led2.off();
	led1.color(20, 0, 20);
}

void loop() {
	if (accel.tap()) {
		led1.randomcolor();
	}

	if (accel.doubletap()) {
		led2.flip();
	}

	wait(200);
};
