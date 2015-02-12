#ifndef COLORSTATE.H
#define COLORSTATE.H

#include "State.h"
#include "LedDriver.h"
#include "Colors.h"


class ColorState : public State {

	// orig colors
	byte _red;
	byte _green;
	byte _blue;

	// colors displayed
	byte currentRed;
	byte currentGreen;
	byte currentBlue;

	unsigned int intensivityRed;
	unsigned int intensivityGreen;
	unsigned int intensivityBlue;

	void calcRedBrightness() {
		currentRed = convertToColor(intensivityRed);
	}
	void calcGreenBrightness() {
		currentGreen = convertToColor(intensivityGreen);
	}
	void calcBlueBrightness() {
		currentBlue = convertToColor(intensivityBlue);
	}

public:
	~ColorState() {
		LOG("~ColorState()");
	}

	ColorState(byte const & red, byte const & green, byte const & blue) {
		LOG("ColorState()");
		_red = red;
		_green = green;
		_blue = blue;

		intensivityRed = convertToIntensivity(red);
		intensivityGreen = convertToIntensivity(green);
		intensivityBlue = convertToIntensivity(blue);

		currentRed = red;
		currentGreen = green;
		currentBlue = blue;
	}

	State* clone() {
		LOG("ColorState.clone()");
		return new ColorState(*this);
	}


	// LOOP FUNCTION
	void run() {
		// LOG("ColorState.run()");
		LED.setColor(currentRed, currentGreen, currentBlue);
	}


	// TRIGGERS
	void turnLighter() {
		if(_red > 0) {
			turnRedLighter();
		}
		if(_green > 0) {
			turnGreenLighter();
		}
		if(_blue > 0) {
			turnBlueLighter();
		}
	}
	void turnRedLighter() {
		intensivityRed += intensivityRed < 16  ? 1 : 0;
		calcRedBrightness();
	}
	void turnGreenLighter() {
		intensivityGreen += intensivityGreen < 16 ? 1 : 0;
		calcGreenBrightness();
	}
	void turnBlueLighter() {
		intensivityBlue += intensivityBlue < 16 ? 1 : 0;
		calcBlueBrightness();
	}

	void turnDarker() {
		turnRedDarker();
		turnGreenDarker();
		turnBlueDarker();
	}
	void turnRedDarker() {
		intensivityRed -= intensivityRed > 1 ? 1 : 0;
		calcRedBrightness();
	}
	void turnGreenDarker() {
		intensivityGreen -= intensivityGreen > 1 ? 1 : 0;
		calcGreenBrightness();
	}
	void turnBlueDarker() {
		intensivityBlue -= intensivityBlue > 1 ? 1 : 0;
		calcBlueBrightness();
	}
};

#endif
