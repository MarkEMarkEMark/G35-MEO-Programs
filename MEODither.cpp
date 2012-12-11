/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and Adafruit

  See README for complete attributions.
*/

#include <MEODither.h>

MEODither::MEODither(MEOG35& g35, uint8_t pattern)
    : MEOLightProgram(g35, pattern), intensity_(0), pattern_(pattern), colorMain_(0), wait_(0), dithStep_(0), step_(0)
{
}

uint32_t MEODither::Do()
{
	bool fourtyEight;
    switch (pattern_ % 4)
    {
	case 0:
        fourtyEight = false;
        colorMain_ = MEODither::LineRG(step_ % 32);
        break;
    case 1:
        fourtyEight = false;
        colorMain_ = MEODither::LineGB(step_ % 32);
        break;
    case 2:
        fourtyEight = false;
        colorMain_ = MEODither::LineBR(step_ % 32);
        break;
    case 3:
        fourtyEight = true;
        colorMain_ = MEODither::Wheel(step_ % 48);
        break;
    }

	// Determine highest bit needed to represent pixel index
	int hiBit = 0;
	int n = light_count_ - 1;
	for(int bit = 1; bit < 0x8000; bit <<= 1) {
		if(n & bit) hiBit = bit;
	}

	int bit, reverse;

	//for(int i = 0; i < (hiBit << 1); i++) {
		// Reverse the bits in i to create ordered dither:
		reverse = 0;
		for(bit = 1; bit <= hiBit; bit <<= 1) {
			reverse <<= 1;
			if(dithStep_ & bit) reverse |= 1;
		}
		g35_.fill_color(reverse, 1, MEOG35::MAX_INTENSITY, colorMain_);
		delay(wait_);
	//}

	dithStep_++;
	if (dithStep_ == (hiBit << 1))
	{
		dithStep_ = 0;
		//pattern_++;

		//reset at end of wheel or line
		step_++; step_++; step_++; step_++; //do 4, so not so smooth
		if (((step_ == 48) && fourtyEight) || ((step_ == 32) && !fourtyEight))
		{
			step_ = 0;
		}
	}



	return bulb_frame_;
}

uint32_t MEODither::Wheel(uint16_t WheelPos)
{
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

uint32_t MEODither::LineRG(uint16_t WheelPos)
{
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

uint32_t MEODither::LineGB(uint16_t WheelPos)
{
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

uint32_t MEODither::LineBR(uint16_t WheelPos)
{
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