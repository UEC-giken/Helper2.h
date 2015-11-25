#include <Helper2.h>
#include <Wire.h>

void setup() {
	initialize();

	accel.debug = true;

	led1.brightness(0.3);
	led2.brightness(0.3);
	led1.on();
	led2.on();
}

void loop() {
	if (accel.freefall()) {
		led1.stepColor(0.05);
		led2.stepColor(0.05);
	}
	else if (accel.active()) {
		while (accel.active()) {
			led1.flip();
			led2.flip();
			wait(200);
    	}
		led1.on();
		led2.on();
	}
	
	if (accel.doubletap()) {
		while(led1.fadeOut(0.05) && led2.fadeOut(0.05)){
			wait(30);
		}
	}
	else if (accel.tap()) {
		while(led1.fadeIn(0.05, 0.3) && led2.fadeIn(0.05, 0.3)){
			wait(30);
		}
	}
	
	accel.debugPrint(1);

	wait(200);
};
