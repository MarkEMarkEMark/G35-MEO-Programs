/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and Adafruit

  See README for complete attributions.
*/

#include <MEOSwitchOff.h>

MEOSwitchOff::MEOSwitchOff(MEOG35& g35)
    : MEOLightProgram(g35, 0)
{
    g35_.fill_color(0, light_count_, 0, COLOR(0,0,0));
}

uint32_t MEOSwitchOff::Do()
{
    g35_.broadcast_intensity(MEOG35::MAX_INTENSITY);
    return bulb_frame_;
}