/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz

  See README for complete attributions.
*/

#include <MEOWhites.h>

MEOWhites::MEOWhites(MEOG35& g35, uint8_t pattern)
    : MEOLightProgram(g35, pattern), intensity_(0), pattern_(pattern)
{
	uint8_t current = 0;
    switch (pattern_ % 5)
    {
    case 0: //Warm White
        g35_.fill_color(0, light_count_, 0, COLOR_WARMWHITE);
        break;
    case 1: //Cold White
        g35_.fill_color(0, light_count_, 0, COLOR_WHITE);
        break;
    case 2: // Warm & Cold White
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
	case 3: //Hint of RGB
        for (int i = 0; i < light_count_; i++)
        {
			switch (current)
			{
				case 0:
					g35_.fill_color(i, 1, 0, COLOR(0xF, 0x9, 0x9));
					current = 1;
					break;
				case 1:
					g35_.fill_color(i, 1, 0, COLOR(0x9, 0xF, 0x9));
					current = 2;
					break;
				case 2:
					g35_.fill_color(i, 1, 0, COLOR(0x9, 0x9, 0xF));
					current = 0;
					break;
			}
        }
        break;
	case 4: //Hint of CYM
        for (int i = 0; i < light_count_; i++)
        {
			switch (current)
			{
				case 0:
					g35_.fill_color(i, 1, 0, COLOR(0x9, 0xF, 0xF));
					current = 1;
					break;
				case 1:
					g35_.fill_color(i, 1, 0, COLOR(0xF, 0xF, 0x9));
					current = 2;
					break;
				case 2:
					g35_.fill_color(i, 1, 0, COLOR(0xF, 0x9, 0xF));
					current = 0;
					break;
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