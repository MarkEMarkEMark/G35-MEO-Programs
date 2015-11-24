/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and Adafruit

  See README for complete attributions.
*/

#include <MEOSineWave.h>

MEOSineWave::MEOSineWave(MEOG35& g35, uint8_t pattern) : MEOLightProgram(g35, pattern), preFill_(true), strobe_(true), wait_(0), colorMain_(COLOR(0,0,15)), colorHi_(COLOR(12,12,12)), colorLo_(COLOR(0,0,0)), wavesPerString_(2), rainbowMain_(true), step_(0), step2_(0), pattern_(pattern), graduated_(false)
{
}

#ifndef PI
#define PI 3.14159265
#endif

uint32_t MEOSineWave::Do()
{
    switch (pattern_ % 8)
    {
    case 0: //red - candy stripe
        rainbowMain_ = false;
        colorMain_ = COLOR(10,0,0);
        break;
    case 1: //green
        rainbowMain_ = false;
        colorMain_ = COLOR(0,10,0);
        break;
    case 2: //blue
        rainbowMain_ = false;
        colorMain_ = COLOR(0,0,10);
        break;
    case 3: //yellow
        rainbowMain_ = false;
        colorMain_ = COLOR(8,8,0);
        break;
    case 4: //magenta
        rainbowMain_ = false;
        colorMain_ = COLOR(8,0,8);
        break;
    case 5: //cyan
        rainbowMain_ = false;
        colorMain_ = COLOR(0,8,8);
        break;
    case 6: //solid changing rainbow
        rainbowMain_ = true;
		graduated_ = false;
        break;
    case 7: //graduated rainbow
        rainbowMain_ = true;
		graduated_ = true;
        break;
    }

    float y;
    byte  rMain, gMain, bMain, rOut, gOut, bOut, rhi, ghi, bhi, rlo, glo, blo, rRainbow, gRainbow, bRainbow;

    // Need to decompose colors into their r, g, b elements
    bMain = (colorMain_ >> 8) & 0xf;
    gMain = (colorMain_ >>  4) & 0xf;
    rMain =  colorMain_        & 0xf;

    bhi = (colorHi_ >> 8) & 0xf;
    ghi = (colorHi_ >>  4) & 0xf;
    rhi =  colorHi_        & 0xf;

    blo = (colorLo_ >> 8) & 0xf;
    glo = (colorLo_ >>  4) & 0xf;
    rlo =  colorLo_        & 0xf;

    uint32_t colorRainbow;
    colorRainbow = MEOSineWave::Wheel(step2_ % 48);

    bRainbow = (colorRainbow >> 8) & 0xf;
    gRainbow = (colorRainbow >>  4) & 0xf;
    rRainbow =  colorRainbow  & 0xf;

    for(int i = 0; i < light_count_; i++)
    {
        y = sin(PI * wavesPerString_ * (float)(step_ + i) / (float)light_count_);
        if(y >= 0.0)
        {
            // Peaks of sine wave are white
            y  = 1.0 - y; // Translate Y to 0.0 (top) to 1.0 (center)
            if (rainbowMain_)
            {
				if (graduated_)  //override solid rainbow with graduated one
				{ //ideally would be spread across lights, but currently fixed to 48 bulbs
					colorRainbow = MEOSineWave::Wheel(i % 48);

				    bRainbow = (colorRainbow >> 8) & 0xf;
				    gRainbow = (colorRainbow >>  4) & 0xf;
				    rRainbow =  colorRainbow  & 0xf;
				}
				rOut = rhi - (byte)((float)(rhi - rRainbow) * y);
				gOut = ghi - (byte)((float)(ghi - gRainbow) * y);
				bOut = bhi - (byte)((float)(bhi - bRainbow) * y);
            }
            else
            {
                rOut = rhi - (byte)((float)(rhi - rMain) * y);
                gOut = ghi - (byte)((float)(ghi - gMain) * y);
                bOut = bhi - (byte)((float)(bhi - bMain) * y);
            }
        }
        else
        {
            // Troughs of sine wave are black
            y += 1.0; // Translate Y to 0.0 (bottom) to 1.0 (center)
            if (rainbowMain_)
            {
				if (graduated_) //override solid rainbow with graduated one
				{
					colorRainbow = MEOSineWave::Wheel(i % 48);

				    bRainbow = (colorRainbow >> 8) & 0xf;
				    gRainbow = (colorRainbow >>  4) & 0xf;
				    rRainbow =  colorRainbow  & 0xf;
				}
                rOut = rlo + (byte)((float)(rRainbow) * y);
                gOut = glo + (byte)((float)(gRainbow) * y);
                bOut = blo + (byte)((float)(bRainbow) * y);
            }
            else
            {
                rOut = rlo + (byte)((float)(rMain) * y);
                gOut = glo + (byte)((float)(gMain) * y);
                bOut = blo + (byte)((float)(bMain) * y);
            }
        }
        g35_.fill_color(i, 1, MEOG35::MAX_INTENSITY, COLOR(rOut, gOut, bOut));
    }

    step_++;
    step2_++;
    if (step2_ == 48) // all 48 colors in the wheel
    {
        step2_ = 0;
    }

    delay(wait_);
    return bulb_frame_;
}

uint32_t MEOSineWave::Wheel(uint16_t WheelPos)
{
    byte r, g, b;
    switch(WheelPos / 16)
    {
    case 0:
        r = 15 - WheelPos % 16; // red down
        g = WheelPos % 16;       // green up
        b = 0;                    // blue off
        break;
    case 1:
        g = 15 - WheelPos % 16; // green down
        b = WheelPos % 16;       // blue up
        r = 0;                    // red off
        break;
    case 2:
        b = 15 - WheelPos % 16; // blue down
        r = WheelPos % 16;       // red up
        g = 0;                    // green off
        break;
    }
    return(COLOR(r,g,b));
}