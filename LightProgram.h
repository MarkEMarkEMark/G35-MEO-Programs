/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_LIGHT_PROGRAMS_H
#define INCLUDE_G35_LIGHT_PROGRAMS_H

#include <G35.h>

// Interface for light programs.
//
// A "light program" is what GE means when they say their lights include 14
// programs. An example is "Chasing Red, White, and Blue."
class LightProgram {
 public:
 LightProgram(G35& g35, uint8_t pattern)
   : g35_(g35), light_count_(g35.get_light_count()),
    bulb_frame_(g35.get_bulb_frame()) {}

  // Do a single slice of work. Returns the number of milliseconds before
  // this function should be called again.
  virtual uint32_t Do() = 0;
 protected:
  G35& g35_;
  uint8_t light_count_;
  uint8_t bulb_frame_;
};

// A collection of LightProgram classes. Putting them here makes it much
// easier on app developers because they don't have to create a switch
// statement for every set of programs they're interested in including.
class LightProgramGroup {
 public:
  virtual LightProgram* CreateProgram(G35& lights, uint8_t program_index, uint8_t pattern) = 0;
};

#endif  // INCLUDE_G35_LIGHT_PROGRAMS_H
