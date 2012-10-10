/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and Adafruit

  See README for complete attributions.
*/

#include <MEOColorPhasing.h>

#define PI 3.14159265

MEOColorPhasing::MEOColorPhasing(G35& g35) : LightProgram(g35), wait_(0), frequencyR_(0.3333), frequencyG_(0.3333), frequencyB_(0.3333),
                             phaseR_(0), phaseG_(2*PI/3), phaseB_(4*PI/3), center_(8), width_(7), fStep_(0), pStep_(0), fForward_(true) {
}

// neat rainbow phase 0, 2*PI/3, 4*PI/3 (120deg = 2PI/3, so 0, 120, 240)

uint32_t MEOColorPhasing::Do() {
	phaseG_ = (2*PI/360) * pStep_;
	phaseB_ = (4*PI/360) * pStep_;

	frequencyR_ = float(fStep_) / 100.0;
	frequencyG_ = float(fStep_) / 100.0;
	frequencyB_ = float(fStep_) / 100.0;

	for (int i=0; i < light_count_; i++) {
		int red = sin(frequencyR_*i + phaseR_) * width_ + center_;
		int grn = sin(frequencyG_*i + phaseG_) * width_ + center_;
		int blu = sin(frequencyB_*i + phaseB_) * width_ + center_;
		g35_.fill_color(i, 1, G35::MAX_INTENSITY, COLOR(red, grn, blu));
		//Serial.println(red);
	}

	//set direction: 1 2 .. 98 99 98 .. 2 1
	if (fStep_ == 100)
	{
		fForward_ = false;
	}
	if (fStep_ == -1)
	{
		fForward_ = true;
	}

	if (fForward_)
	{
		fStep_++;
	}

	if (!fForward_)
	{
		fStep_--;
	}

	pStep_++;
	if (pStep_ == 360)
	{
		pStep_ = 0;
	}

	delay(wait_);

	return bulb_frame_;
}

//uint32_t MEOColorPhasing::MakeColorGradient(frequency1, frequency2, frequency3,
 //                            phase1, phase2, phase3,
 //                            center, width, len)
  //{
    //for (var i = 0; i < len; ++i)
    //{
       //var red = Math.sin(frequency1*i + phase1) * width + center;
       //var grn = Math.sin(frequency2*i + phase2) * width + center;
       //var blu = Math.sin(frequency3*i + phase3) * width + center;
       //document.write( '<font color="' + RGB2Color(red,grn,blu) + '">&#9608;</font>');
    //}
 // }

//function RGB2Color(r,g,b)
//  {
//    return '#' + byte2Hex(r) + byte2Hex(g) + byte2Hex(b);
//  }