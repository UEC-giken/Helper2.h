#include <Helper2.h>
#include <Wire.h>

void setup() {
	initialize();

	led1.off();
	led2.color(0);
	led2.off();
	led2.color(0.5);
}

void loop() {
	if (accel.freefall()) {
		led1.on();
	} else {
		led1.off();
	}

	if (accel.active()) {
		led2.on();
	} else {
		led2.off();
	}

	wait(20);
};
