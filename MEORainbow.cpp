/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and Adafruit

  See README for complete attributions.
*/

#include <MEORainbow.h>

MEORainbow::MEORainbow(G35& g35) : LightProgram(g35), wait_(0), type_(1), frame_(true), step_(0) {
}

uint32_t MEORainbow::Do() {
	for (int i=0; i < light_count_; i++) {
		switch(type_)
		{
			case 1:
				if (frame_)
				{
					g35_.fill_color(i, 1, G35::MAX_INTENSITY, MEORainbow::LineRG((i + step_) % 32));
				} else {
					g35_.fill_color(i, 1, G35::MAX_INTENSITY, MEORainbow::LineRG(((i * 32 / light_count_) + step_) % 32));
				}
				break;
			case 2:
				if (frame_)
				{
					g35_.fill_color(i, 1, G35::MAX_INTENSITY, MEORainbow::LineGB((i + step_) % 32));
				} else {
					g35_.fill_color(i, 1, G35::MAX_INTENSITY, MEORainbow::LineGB(((i * 32 / light_count_) + step_) % 32));
				}
				break;
			case 3:
				if (frame_)
				{
					g35_.fill_color(i, 1, G35::MAX_INTENSITY, MEORainbow::LineBR((i + step_) % 32));
				} else {
					g35_.fill_color(i, 1, G35::MAX_INTENSITY, MEORainbow::LineBR(((i * 32 / light_count_) + step_) % 32));
				}
				break;
			default:
				if (frame_)
				{
					g35_.fill_color(i, 1, G35::MAX_INTENSITY, MEORainbow::Wheel((i + step_) % 48));
				} else {
					g35_.fill_color(i, 1, G35::MAX_INTENSITY, MEORainbow::Wheel(((i * 48 / light_count_) + step_) % 48));
				}
				break;
		}
	}

	//reset at end of wheel or line
	step_++;
	if ((step_ == 48) || ((step_ == 32) && type_ >= 1 && type_ <= 3))// all 48 colors in the wheel
	{
		step_ = 0;
	}

	delay(wait_);

	return bulb_frame_;
}

uint32_t MEORainbow::Wheel(uint16_t WheelPos) {
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

uint32_t MEORainbow::LineRG(uint16_t WheelPos) {
	byte r, g, b;
	switch(WheelPos / 16)
	{
	case 0:
		r = 15 - WheelPos % 16; // red down
		g = WheelPos % 16;       // green up
		b = 0;					// blue off
		break;
	case 1:
		r = WheelPos % 16;       // red up
		g = 15 - WheelPos % 16; // green down
		b = 0;					// blue off
		break;
	}
	return(COLOR(r,g,b));
}

uint32_t MEORainbow::LineGB(uint16_t WheelPos) {
	byte r, g, b;
	switch(WheelPos / 16)
	{
	case 0:
		r = 0;                    // red off
		g = 15 - WheelPos % 16; // green down
		b = WheelPos % 16;       // blue up
		break;
	case 1:
		r = 0;                    // red off
		g = WheelPos % 16;       // green up
		b = 15 - WheelPos % 16; // blue down
		break;
	}
	return(COLOR(r,g,b));
}

uint32_t MEORainbow::LineBR(uint16_t WheelPos) {
	byte r, g, b;
	switch(WheelPos / 16)
	{
	case 0:
		r = WheelPos % 16;       // red up
		g = 0;                    // green off
		b = 15 - WheelPos % 16; // blue down
		break;
	case 1:
		r = 15 - WheelPos % 16; // red down
		g = 0;                    // green off
		b = WheelPos % 16;       // blue up
		break;
	}
	return(COLOR(r,g,b));
}