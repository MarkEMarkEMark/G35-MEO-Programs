/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and Adafruit

  See README for complete attributions.
*/

#include <MEOWhites.h>

MEOWhites::MEOWhites(MEOG35& g35, uint8_t pattern)
    : MEOLightProgram(g35, pattern), intensity_(0), pattern_(pattern)
{
    switch (pattern_ % 3)
    {
    case 0:
        g35_.fill_color(0, light_count_, 0, COLOR_WARMWHITE);
        break;
    case 1:
        g35_.fill_color(0, light_count_, 0, COLOR_WHITE);
        break;
    case 2:
        for (int i = 0; i < light_count_; i++)
        {
            if ((i % 2) == 0)
            {
                g35_.fill_color(i, 1, 0, COLOR_WHITE);
            }
            else
            {
                g35_.fill_color(i, 1, 0, COLOR_WARMWHITE);
            }

        }
        break;
    }
}

uint32_t MEOWhites::Do()
{
    if (intensity_ <= MEOG35::MAX_INTENSITY)
    {
        g35_.broadcast_intensity(intensity_++);
        return bulb_frame_;
    }
    return 1000;
}