/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2012 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_PROGRAMS_MEO_CHASING_H
#define INCLUDE_G35_PROGRAMS_MEO_CHASING_H

#include <LightProgram.h>

class MEOChasing : public LightProgram {
	public:
		MEOChasing(G35& g35);
		uint32_t Do();
		static color_t PastelRGB(uint16_t sequence);
		static color_t RGBY(uint16_t sequence);
		static color_t RWB(uint16_t sequence);
		static color_t RC(uint16_t sequence);
		static color_t GM(uint16_t sequence);
		static color_t BY(uint16_t sequence);
		static color_t RG(uint16_t sequence);
		static color_t GB(uint16_t sequence);
		static color_t BR(uint16_t sequence);
		static color_t CM(uint16_t sequence);
		static color_t MY(uint16_t sequence);
		static color_t YC(uint16_t sequence);
		static color_t RGB(uint16_t sequence);
		static color_t CYM(uint16_t sequence);
		static color_t RCGMBY(uint16_t sequence);
		static color_t PurplyBlue(uint16_t sequence);
		static color_t Valentines(uint16_t sequence);

	private:
		uint8_t count_;
		uint16_t sequence_;
		uint16_t wait_;
		uint8_t pattern_;
};

#endif