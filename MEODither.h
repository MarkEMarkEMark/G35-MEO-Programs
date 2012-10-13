/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2012 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and Adafruit

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_PROGRAMS_MEO_DITHER_H
#define INCLUDE_G35_PROGRAMS_MEO_DITHER_H

#include <MEOLightProgram.h>

class MEODither : public MEOLightProgram
{
public:
    MEODither(MEOG35& g35, uint8_t pattern);
    uint32_t Do();

private:
    uint8_t intensity_;
    uint8_t pattern_;
	uint16_t colorMain_;
	uint16_t wait_;
	uint16_t step_;
};

#endif