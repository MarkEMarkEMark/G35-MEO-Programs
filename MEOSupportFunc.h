/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2012 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_PROGRAMS_MEO_SUPPORTFUNC_H
#define INCLUDE_G35_PROGRAMS_MEO_SUPPORTFUNC_H

#include <LightProgram.h>

class MEOSupportFunc : public LightProgram {
	public:
		uint32_t Wheel(uint16_t WheelPos);
		uint32_t LineRG(uint16_t WheelPos);
		uint32_t LineGB(uint16_t WheelPos);
		uint32_t LineBR(uint16_t WheelPos);

	private:
		uint8_t wait_;
		uint8_t type_;
		uint8_t step_;
};

#endif