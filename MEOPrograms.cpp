/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz

  See README for complete attributions.
*/

#include <MEOPrograms.h>

LightProgram* MEOProgramGroup::CreateProgram(G35& lights,
                                              uint8_t program_index) {
	switch (program_index % ProgramCount) {
		case 0: return new MEOSteadyWarmWhite(lights);
		case 1: return new MEORainbow(lights);
		case 2: return new MEORandomStrobe(lights);
		case 3: return new MEOSimplexNoise(lights);
		case 4: return new MEOSineWave(lights);
		case 5: return new MEOChasing(lights);
		case 6: return new MEOColorPhasing(lights);
	}
  // not reached
  return NULL;
}