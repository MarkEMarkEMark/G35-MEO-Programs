/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.

  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  Original version by Paul Martis (http://www.digitalmisery.com). See
  README for complete attributions.

  Special thanks to Richard <rkfoote@gmail.com> and "slinky" for the unrolled-
  loop protocol code that seems to work very well!
*/

#include <MEOG35String.h>

#define MHZ_16 (1)  // standard Arduino/Teensy

#if MHZ_16
#define DELAYLONG 17    // should be ~ 20uS long
#define DELAYSHORT 7   // should be ~ 10uS long
#else  // 20MHz
#define DELAYLONG 25    // should be ~ 20uS long
#define DELAYSHORT 11   // should be ~ 10uS long
#endif
#define DELAYEND 40     // should be ~ 30uS long

#define ZERO(x) digitalWrite(x, LOW);           \
  delayMicroseconds(DELAYSHORT);                \
  digitalWrite(x, HIGH);                        \
  delayMicroseconds(DELAYLONG);

#define ONE(x) digitalWrite(x, LOW);            \
  delayMicroseconds(DELAYLONG);                 \
  digitalWrite(x, HIGH);                        \
  delayMicroseconds(DELAYSHORT);

MEOG35String::MEOG35String(uint8_t pin, uint8_t light_count,
                           uint8_t physical_light_count,
                           uint8_t bulb_zero, bool is_forward)
    : MEOG35(), pin_(pin), physical_light_count_(physical_light_count),
      bulb_zero_(bulb_zero), is_forward_(is_forward)
{
    pinMode(pin, OUTPUT);
    light_count_ = light_count;
    if (physical_light_count_ == 0)
        physical_light_count_ = light_count;
}
#define SET_OR_CLEAR(v, b) { if (v & b) { ONE(pin_); } else { ZERO(pin_); } }

void MEOG35String::set_color(uint16_t bulb, uint8_t intensity, color_t color)
{
    bulb += bulb_zero_;
    uint8_t r, g, b;
    r = color & 0x0F;
    g = (color >> 4) & 0x0F;
    b = (color >> 8) & 0x0F;

    if (intensity > MAX_INTENSITY)
        intensity = MAX_INTENSITY;

    noInterrupts();

    digitalWrite(pin_, HIGH);
    delayMicroseconds(DELAYSHORT);

    // LED Address
    SET_OR_CLEAR(bulb, 0x20);
    SET_OR_CLEAR(bulb, 0x10);
    SET_OR_CLEAR(bulb, 0x08);
    SET_OR_CLEAR(bulb, 0x04);
    SET_OR_CLEAR(bulb, 0x02);
    SET_OR_CLEAR(bulb, 0x01);

    // Brightness
    SET_OR_CLEAR(intensity, 0x80);
    SET_OR_CLEAR(intensity, 0x40);
    SET_OR_CLEAR(intensity, 0x20);
    SET_OR_CLEAR(intensity, 0x10);
    SET_OR_CLEAR(intensity, 0x08);
    SET_OR_CLEAR(intensity, 0x04);
    SET_OR_CLEAR(intensity, 0x02);
    SET_OR_CLEAR(intensity, 0x01);

    // Blue
    SET_OR_CLEAR(b, 0x08);
    SET_OR_CLEAR(b, 0x04);
    SET_OR_CLEAR(b, 0x02);
    SET_OR_CLEAR(b, 0x01);

    // Green
    SET_OR_CLEAR(g, 0x08);
    SET_OR_CLEAR(g, 0x04);
    SET_OR_CLEAR(g, 0x02);
    SET_OR_CLEAR(g, 0x01);

    // Red
    SET_OR_CLEAR(r, 0x08);
    SET_OR_CLEAR(r, 0x04);
    SET_OR_CLEAR(r, 0x02);
    SET_OR_CLEAR(r, 0x01);

    digitalWrite(pin_, LOW);
    delayMicroseconds(DELAYEND);

    interrupts();
}

void MEOG35String::enumerate()
{
    enumerate(is_forward_);
}

void MEOG35String::enumerate(bool forward)
{
    uint8_t count = physical_light_count_;
    uint8_t bulb = forward ? 0 : light_count_ - 1;
    int8_t delta = forward ? 1 : -1;
    while (count--)
    {
        set_color(bulb, MAX_INTENSITY, COLOR_RED);
        bulb += delta;
    }
}

void MEOG35String::enumerate_forward()
{
    enumerate(true);
}

void MEOG35String::enumerate_reverse()
{
    enumerate(false);
}

void MEOG35String::do_test_patterns()
{
    const uint8_t d = 1000 / light_count_;
    const uint8_t last_light = light_count_ - 1;
    fill_sequence(0, light_count_, 0, 1, 0, rainbow_color);

    for (int i = 0; i <= MAX_INTENSITY; ++i)
    {
        set_color(BROADCAST_BULB, i, COLOR_BLACK);
        delay(1);
    }

    delay(500);

    for (int i = MAX_INTENSITY; i >= 0; --i)
    {
        set_color(BROADCAST_BULB, i, COLOR_BLACK);
        delay(1);
    }

    for (uint8_t i = 0; i < light_count_; ++i)
    {
        set_color(i, MAX_INTENSITY, COLOR_GREEN);
        set_color(last_light - i, MAX_INTENSITY, COLOR_BLUE);
        if (i > 0)
        {
            set_color(i - 1, MAX_INTENSITY, COLOR_BLACK);
            set_color(last_light - i + 1, MAX_INTENSITY, COLOR_BLACK);
        }
        delay(d);
    }

    fill_color(0, light_count_, MAX_INTENSITY, COLOR_BLACK);
}
