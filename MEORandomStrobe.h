/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2012 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_PROGRAMS_MEO_RANDOM_STROBE_H
#define INCLUDE_G35_PROGRAMS_MEO_RANDOM_STROBE_H

#include <LightProgram.h>

class MEORandomStrobe : public LightProgram {
	public:
		MEORandomStrobe(G35& g35);
		uint32_t Do();
		uint32_t Wheel(uint16_t WheelPos);

	private:
		bool preFill_;
		bool strobe_;
		uint8_t wait_;
		uint8_t noAtATime_;
		uint32_t colorMain_;
		uint32_t colorFlash_;
		bool rainbowFlash_; //instead of single strobe color, will cycle through colour wheel
		bool rainbowFrame_; //if rainbow flash, then whether cycles colour after all bulbs flashed or with each bulb flashed
		uint8_t step_;
		uint8_t myBulb_;
};

#endif