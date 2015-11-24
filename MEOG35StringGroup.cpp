/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  Original version by Paul Martis (http://www.digitalmisery.com). See
  README for complete attributions.
*/

#include <MEOG35StringGroup.h>

MEOG35StringGroup::MEOG35StringGroup()
    : string_count_(0), light_count_(0)
{
}

void MEOG35StringGroup::AddString(MEOG35* g35)
{
    if (string_count_ == MAX_STRINGS)
        return;

    uint16_t count = g35->get_light_count();
    string_length_[string_count_] = count;
    strings_[string_count_] = g35;
    light_count_ += count;
    string_count_++;
}

uint16_t MEOG35StringGroup::get_light_count()
{
    return light_count_;
}

void MEOG35StringGroup::set_color(uint16_t bulb, uint8_t intensity, color_t color)
{
    uint8_t string = 0;
    uint16_t orig = bulb;

    while (bulb >= string_length_[string] && string < string_count_)
        bulb -= string_length_[string++];
    if (string < string_count_) {
        strings_[string]->set_color(bulb, intensity, color);
    } else {
        Serial.print(orig);
        Serial.println(" out of bounds");
    }
}

void MEOG35StringGroup::broadcast_intensity(uint8_t intensity)
{
    for (uint8_t i = 0; i < string_count_; ++i)
    {
        strings_[i]->broadcast_intensity(intensity);
    }
}
