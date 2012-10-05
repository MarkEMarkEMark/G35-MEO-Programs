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

MEOSineWave::MEOSineWave(G35& g35) : LightProgram(g35), preFill_(true), strobe_(true), wait_(0), colorMain_(COLOR(15,0,0)), colorHi_(COLOR(12,12,12)), colorLo_(COLOR(0,0,0)), wavesPerString_(2), step_(0) {
}

#define PI 3.14159265

uint32_t MEOSineWave::Do() {
	float y;
	byte  rMain, gMain, bMain, rOut, gOut, bOut, rhi, ghi, bhi, rlo, glo, blo;

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

	for(int i = 0; i < light_count_; i++) {
		y = sin(PI * wavesPerString_ * (float)(step_ + i) / (float)light_count_);
		if(y >= 0.0) {
			// Peaks of sine wave are white
			y  = 1.0 - y; // Translate Y to 0.0 (top) to 1.0 (center)
			rOut = rhi - (byte)((float)(rhi - rMain) * y);
			gOut = ghi - (byte)((float)(ghi - gMain) * y);
			bOut = bhi - (byte)((float)(bhi - bMain) * y);
		} else {
			// Troughs of sine wave are black
			y += 1.0; // Translate Y to 0.0 (bottom) to 1.0 (center)
			rOut = rlo + (byte)((float)(rMain) * y) ;
			gOut = glo + (byte)((float)(gMain) * y);
			bOut = blo + (byte)((float)(bMain) * y);
		}
		g35_.fill_color(i, 1, G35::MAX_INTENSITY, COLOR(rOut, gOut, bOut));
	}
	step_++;
	delay(wait_);
	return bulb_frame_;
}