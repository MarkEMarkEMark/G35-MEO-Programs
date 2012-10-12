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

MEOColorPhasing::MEOColorPhasing(MEOG35& g35, uint8_t pattern) : MEOLightProgram(g35, pattern), wait_(0), frequencyR_(0.06), frequencyG_(0.06), frequencyB_(0.06),
                             phaseR_(0), phaseG_(2*PI/3), phaseB_(4*PI/3), center_(8), width_(7), fStep_(0), pStep_(0), fForward_(true), turn_(0), pattern_(pattern) {
}

// neat rainbow phase 0, 2*PI/3, 4*PI/3 (120deg = 2PI/3, so 0, 120, 240)

uint32_t MEOColorPhasing::Do() {

    uint8_t patternLimited = pattern_ % 6;
	switch (patternLimited)
	{
	case 0:  //Wavey pastels
		phaseR_ = 0;
		phaseB_ = 2*PI/3;
		phaseG_ = 4*PI/3;
		frequencyR_ = float(fStep_) / 100.0;
		frequencyG_ = float(fStep_) / 100.0;
		frequencyB_ = float(fStep_) / 100.0;
		break;
	case 1: // subtly changing pastels
		phaseR_ = 0;
		phaseB_ = (2*PI/360) * pStep_;
		phaseG_ = (4*PI/360) * pStep_;
		frequencyR_ = 1.666;
		frequencyG_ = 2.666;
		frequencyB_ = 3.666;
		break;
	case 2: //White twinkle
		phaseR_ = pStep_;
		phaseB_ = pStep_;
		phaseG_ = pStep_;
		frequencyR_ = float(fStep_) / 100.0;
		frequencyG_ = float(fStep_) / 100.0;
		frequencyB_ = float(fStep_) / 100.0;
		break;
	case 3: //RGB Evolving pastel wave
		phaseR_ = 0;
		phaseG_ = (2*PI/360) * pStep_;
		phaseB_ = (4*PI/360) * pStep_;
		frequencyR_ = float(fStep_) / 100.0;
		frequencyG_ = float(fStep_) / 100.0;
		frequencyB_ = float(fStep_) / 100.0;
		break;
	case 4: //GBR Evolving pastel wave
		phaseG_ = 0;
		phaseB_ = (2*PI/360) * pStep_;
		phaseR_ = (4*PI/360) * pStep_;
		frequencyR_ = float(fStep_) / 100.0;
		frequencyG_ = float(fStep_) / 100.0;
		frequencyB_ = float(fStep_) / 100.0;
		break;
	case 5: //GRB Evolving pastel wave
		phaseG_ = 0;
		phaseR_ = (2*PI/360) * pStep_;
		phaseB_ = (4*PI/360) * pStep_;
		frequencyR_ = float(fStep_) / 100.0;
		frequencyG_ = float(fStep_) / 100.0;
		frequencyB_ = float(fStep_) / 100.0;
		break;
	}



	for (int i=0; i < light_count_; i++) {
		int red = sin(frequencyR_*i + phaseR_) * width_ + center_;
		int grn = sin(frequencyG_*i + phaseG_) * width_ + center_;
		int blu = sin(frequencyB_*i + phaseB_) * width_ + center_;
		g35_.fill_color(i, 1, MEOG35::MAX_INTENSITY, COLOR(red, grn, blu));
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
		turn_++;
		if (turn_ == 6)
		{
			turn_ = 0;
		}
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