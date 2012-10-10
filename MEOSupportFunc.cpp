/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz

  See README for complete attributions.
*/

#include <MEOSupportFunc.h>

uint32_t MEOSupportFunc::Wheel(uint16_t WheelPos) {
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

uint32_t MEOSupportFunc::LineRG(uint16_t WheelPos) {
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

uint32_t MEOSupportFunc::LineGB(uint16_t WheelPos) {
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

uint32_t MEOSupportFunc::LineBR(uint16_t WheelPos) {
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