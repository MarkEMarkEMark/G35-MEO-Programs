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

#include <MEOSwitchOff.h>
#include <MEOLightProgram.h>
#include <MEORainbow.h>
#include <MEOWhites.h>
#include <MEORandomStrobe.h>
#include <MEOSineWave.h>
#include <MEOSimplexNoise.h>
#include <MEOChasing.h>
#include <MEOColorPhasing.h>
#include <MEODither.h>
//#include <MEOOscillate.h>

class MEOProgramGroup : public MEOLightProgramGroup
{
public:
    enum {ProgramCount = 8};

    virtual MEOLightProgram* CreateProgram(MEOG35& lights, uint8_t program_index, uint8_t pattern);
};

#endif  // INCLUDE_G35_MEO_PROGRAMS_H