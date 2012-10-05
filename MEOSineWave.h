/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2012 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_PROGRAMS_MEO_SINE_WAVE_H
#define INCLUDE_G35_PROGRAMS_MEO_SINE_WAVE_H

#include <LightProgram.h>

class MEOSineWave : public LightProgram {
 public:
  MEOSineWave(G35& g35);
  uint32_t Do();

 private:
  bool preFill_;
  bool strobe_;
  uint8_t wait_;
  uint32_t colorMain_;
  uint32_t colorHi_;
  uint32_t colorLo_;
  uint8_t wavesPerString_;
  uint32_t step_;
};

#endif