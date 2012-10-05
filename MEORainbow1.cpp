/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and Adafruit

  See README for complete attributions.
*/

#include <MEORainbow1.h>

MEORainbow1::MEORainbow1(G35& g35) : LightProgram(g35), wait_(500), step_(0) {
}

uint32_t MEORainbow1::Do() {
	for (int i=0; i < light_count_; i++) {
		g35_.fill_color(i, 1, G35::MAX_INTENSITY, MEORainbow1::Wheel(((i * 48 / light_count_) + step_) % 48));
	}

	step_++;
	if (step_ == 48) // all 48 colors in the wheel
	{
		step_ = 0;
	}

	delay(wait_);

	return bulb_frame_;
}

uint32_t MEORainbow1::Wheel(uint16_t WheelPos) {
	byte r, g, b;
	switch(WheelPos / 16)
	{
	case 0:
		r = 15 - WheelPos % 16; // red down
		g = WheelPos % 16;       // green up
		b = 0;                    // blue off
		break;
	case 1:
		g = 15 - WheelPos % 16; // green down
		b = WheelPos % 16;       // blue up
		r = 0;                    // red off
		break;
	case 2:
		b = 15 - WheelPos % 16; // blue down
		r = WheelPos % 16;       // red up
		g = 0;                    // green off
		break;
	}
	return(COLOR(r,g,b));
}