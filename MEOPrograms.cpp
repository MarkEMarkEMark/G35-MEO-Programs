/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz

  See README for complete attributions.
*/

#include <MEOPrograms.h>

MEOLightProgram* MEOProgramGroup::CreateProgram(MEOG35& lights,
        uint8_t program_index, uint8_t pattern)
{
    if (program_index == 255)
    {
        return new MEOSwitchOff(lights);
    }
    else
    {
        switch (program_index % ProgramCount)
        {
        case 0:
            return new MEOWhites(lights, pattern);
        case 1:
            return new MEORainbow(lights, pattern);
        case 2:
            return new MEORandomStrobe(lights, pattern);
        case 3:
            return new MEOSimplexNoise(lights, pattern);
        case 4:
            return new MEOSineWave(lights, pattern);
        case 5:
            return new MEOChasing(lights, pattern);
        case 6:
            return new MEOColorPhasing(lights, pattern);
		case 7:
            return new MEODither(lights, pattern);
		case 8:
            return new MEOOscillate(lights, pattern);
        }
    }
    // not reached
    return NULL;
}