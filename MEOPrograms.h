/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_MEO_PROGRAMS_H
#define INCLUDE_G35_MEO_PROGRAMS_H

#include <LightProgram.h>
#include <Meteorite.h>
#include <Twinkle.h>
#include <RedGreenChase.h>
#include <Pulse.h>
#include <Orbit.h>
#include <Cylon.h>
#include <Stereo.h>
#include <Inchworm.h>
#include <MEORainbow1.h>
#include <MEORainbow2.h>
#include <MEOSteadyWarmWhite.h>
#include <MEORandomStrobe.h>
#include <MEOSineWave.h>
#include <MEOSimplexNoise.h>

class MEOProgramGroup : public LightProgramGroup {
 public:
  enum { ProgramCount = 15 };

  virtual LightProgram* CreateProgram(G35& lights, uint8_t program_index);
};

#endif  // INCLUDE_G35_MEO_PROGRAMS_H