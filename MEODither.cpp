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
    : MEOLightProgram(g35, pattern), intensity_(0), pattern_(pattern), colorMain_(0), wait_(10), step_(0)
{
}

uint32_t MEODither::Do()
{
    switch (pattern_ % 8)
    {
    case 0:
        colorMain_ = COLOR(15,0,0);
        break;
    case 1:
        colorMain_ = COLOR(11,0,3);
        break;
    case 2:
        colorMain_ = COLOR(7,0,7);
        break;
    case 3:
        colorMain_ = COLOR(3,0,11);
        break;
    case 4:
        colorMain_ = COLOR(0,0,15);
        break;
    case 5:
        colorMain_ = COLOR(3,0,11);
        break;
	case 6:
        colorMain_ = COLOR(7,0,7);
        break;
    case 7:
        colorMain_ = COLOR(11,0,3);
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
			if(step_ & bit) reverse |= 1;
		}
		g35_.fill_color(reverse, 1, MEOG35::MAX_INTENSITY, colorMain_);
		delay(wait_);
	//}

	step_++;
	if (step_ == (hiBit << 1))
	{
		step_ = 0;
		pattern_++;
	}

	return bulb_frame_;
}