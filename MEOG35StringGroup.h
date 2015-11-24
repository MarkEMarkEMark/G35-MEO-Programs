/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  Original version by Paul Martis (http://www.digitalmisery.com). See
  README for complete attributions.
*/

#pragma once

#include <MEOG35.h>

// A G35StringGroup takes a set of G35 instances and presents them as a single
// virtual light string of arbitrary length.
//
// A LightProgram that is given a G35StringGroup will then be able to run
// itself over the whole virtual string, without needing to know the details
// of which physical string contains which logical bulb.
class MEOG35StringGroup : public MEOG35
{
public:
    MEOG35StringGroup();

    void AddString(MEOG35* g35);

    uint16_t get_light_count();

    void set_color(uint16_t bulb, uint8_t intensity, color_t color);
    void broadcast_intensity(uint8_t intensity);

private:
    enum { MAX_STRINGS = 16 };

    uint16_t light_count_;
    uint8_t string_count_;
    MEOG35* strings_[MAX_STRINGS];
    uint16_t string_length_[MAX_STRINGS];
};
