/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and Adafruit

  See README for complete attributions.
*/

#include <MEOSteadyWarmWhite.h>

MEOSteadyWarmWhite::MEOSteadyWarmWhite(G35& g35)
  : LightProgram(g35), intensity_(0) {
  g35_.fill_color(0, light_count_, 0, COLOR_WARMWHITE);
}

uint32_t MEOSteadyWarmWhite::Do() {
  if (intensity_ <= G35::MAX_INTENSITY) {
    g35_.broadcast_intensity(intensity_++);
    return bulb_frame_;
  }
  return 1000;
}