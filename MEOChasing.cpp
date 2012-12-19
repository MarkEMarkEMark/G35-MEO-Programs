/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.
  and Mark Ortiz

  The 1st 13 patterns are obvious primary/secondary colour combos
  14/15 are my own attempts at pleasing colours schemes
  16+ are attempts to use colour theory to form triads and tetrads of colour (see http://colorschemedesigner.com/)
  I hope to programmatically create triads and tetrads in a future version, so I can rotate them around the colour wheel
  I've ordered the colours in AccentedAnalogic, so that if the sequence size is 4 you get the full primary, secondaries and complimentary
  , but 3 removes complimentary, and 2 removes primary

  See README for complete attributions.
*/

#include <MEOChasing.h>

MEOChasing::MEOChasing(MEOG35& g35, uint8_t pattern)
    : MEOLightProgram(g35, pattern), count_(1), sequence_(0), wait_(10), pattern_(pattern) //, cR1_(0), cG1_(0), cB1_(0), cR2_(0), cG2_(0), cB2_(0), cR3_(0), cG3_(0), cB3_(0), cR4_(0), cG4_(0), cB4_(0), firstTime_(true))
{
    Serial.print("MEOChasing Pattern: ");
    Serial.println(pattern);
}

uint32_t MEOChasing::Do()
{
	wait_ = 10; //default
    switch (pattern_ % 26)
    {
    case 0:
        g35_.fill_sequence(0, count_, sequence_, 5, MEOG35::MAX_INTENSITY, ColourCycle);
        break;
    case 1:
        g35_.fill_sequence(0, count_, sequence_, 5, MEOG35::MAX_INTENSITY, RedAccentedAlalogic);
        break;
    case 2:
		g35_.fill_sequence(0, count_, sequence_, 5, MEOG35::MAX_INTENSITY, GreenAccentedAlalogic);
        break;
    case 3:
		g35_.fill_sequence(0, count_, sequence_, 5, MEOG35::MAX_INTENSITY, BlueAccentedAlalogic);
        break;
    case 4:
        g35_.fill_sequence(0, count_, sequence_, 3, MEOG35::MAX_INTENSITY, Valentines);
        break;
    case 5:
        g35_.fill_sequence(0, count_, sequence_, 3, MEOG35::MAX_INTENSITY, BlueTriad);
        break;
    case 6:
        g35_.fill_sequence(0, count_, sequence_, 3, MEOG35::MAX_INTENSITY, BlueTetrad);
        break;
    case 7:
        g35_.fill_sequence(0, count_, sequence_, 3, MEOG35::MAX_INTENSITY, PurpleTetrad);
        break;
    case 8:
        g35_.fill_sequence(0, count_, sequence_, 3, MEOG35::MAX_INTENSITY, GreenTetrad);
        break;
    case 9:
        g35_.fill_sequence(0, count_, sequence_, 5, MEOG35::MAX_INTENSITY, RGBY);
        break;
    case 10:
        g35_.fill_sequence(0, count_, sequence_, 10, MEOG35::MAX_INTENSITY, RWB);
        break;
    case 11:
        g35_.fill_sequence(0, count_, sequence_, 5, MEOG35::MAX_INTENSITY, RC);
        break;
    case 12:
        g35_.fill_sequence(0, count_, sequence_, 5, MEOG35::MAX_INTENSITY, GM);
        break;
    case 13:
        g35_.fill_sequence(0, count_, sequence_, 5, MEOG35::MAX_INTENSITY, BY);
        break;
    case 14:
        g35_.fill_sequence(0, count_, sequence_, 2, MEOG35::MAX_INTENSITY, RCGMBY);
		wait_ = 30;
        break;
    case 15:
        g35_.fill_sequence(0, count_, sequence_, 5, MEOG35::MAX_INTENSITY, RG);
        break;
    case 16:
        g35_.fill_sequence(0, count_, sequence_, 5, MEOG35::MAX_INTENSITY, GB);
        break;
    case 17:
        g35_.fill_sequence(0, count_, sequence_, 5, MEOG35::MAX_INTENSITY, BR);
        break;
    case 18:
        g35_.fill_sequence(0, count_, sequence_, 5, MEOG35::MAX_INTENSITY, CM);
        break;
    case 19:
        g35_.fill_sequence(0, count_, sequence_, 5, MEOG35::MAX_INTENSITY, MY);
        break;
    case 20:
        g35_.fill_sequence(0, count_, sequence_, 5, MEOG35::MAX_INTENSITY, YC);
        break;
    case 21:
        g35_.fill_sequence(0, count_, sequence_, 5, MEOG35::MAX_INTENSITY, RGB);
        break;
    case 22:
        g35_.fill_sequence(0, count_, sequence_, 5, MEOG35::MAX_INTENSITY, CYM);
        break;
    case 23:
        g35_.fill_sequence(0, count_, sequence_, 4, MEOG35::MAX_INTENSITY, PastelRGB);
        break;
	case 24:
        g35_.fill_sequence(0, count_, sequence_, 3, MEOG35::MAX_INTENSITY, RWG);
        break;
    case 25:
        g35_.fill_sequence(0, count_, sequence_, 3, MEOG35::MAX_INTENSITY, PurplyBlue);
        break;
    }
    if (count_ < light_count_)
    {
        ++count_;
    }
    else
    {
        ++sequence_;
    }
    delay(wait_);
    return bulb_frame_;
}

// static
color_t MEOChasing::PastelRGB(uint16_t sequence)
{
    sequence = sequence % 3;
    if (sequence == 0)
    {
        return COLOR(0xf, 0x2, 0x1);
    }
    if (sequence == 1)
    {
        return COLOR(0x8, 0xf, 0x2);
    }
    return COLOR(0xb, 0x5, 0xf);
}

color_t MEOChasing::RGBY(uint16_t sequence)
{
    sequence = sequence % 4;
    if (sequence == 0)
    {
        return COLOR_RED;
    }
    if (sequence == 1)
    {
        return COLOR_GREEN;
    }
    if (sequence == 2)
    {
        return COLOR_BLUE;
    }
    return COLOR_YELLOW;
}

color_t MEOChasing::RWB(uint16_t sequence)
{
    sequence = sequence % 3;
    if (sequence == 0)
    {
        return COLOR_RED;
    }
    if (sequence == 1)
    {
        return COLOR_WHITE;
    }
    return COLOR_BLUE;
}

color_t MEOChasing::RWG(uint16_t sequence)
{
    sequence = sequence % 3;
    if (sequence == 0)
    {
        return COLOR_RED;
    }
    if (sequence == 1)
    {
        return COLOR_WHITE;
    }
    return COLOR_GREEN;
}

color_t MEOChasing::RC(uint16_t sequence)
{
    sequence = sequence % 2;
    if (sequence == 0)
    {
        return COLOR_RED;
    }
    return COLOR_CYAN;
}

color_t MEOChasing::GM(uint16_t sequence)
{
    sequence = sequence % 2;
    if (sequence == 0)
    {
        return COLOR_GREEN;
    }
    return COLOR_MAGENTA;
}

color_t MEOChasing::BY(uint16_t sequence)
{
    sequence = sequence % 2;
    if (sequence == 0)
    {
        return COLOR_BLUE;
    }
    return COLOR_YELLOW;
}

color_t MEOChasing::RG(uint16_t sequence)
{
    sequence = sequence % 2;
    if (sequence == 0)
    {
        return COLOR_RED;
    }
    return COLOR_GREEN;
}

color_t MEOChasing::GB(uint16_t sequence)
{
    sequence = sequence % 2;
    if (sequence == 0)
    {
        return COLOR_GREEN;
    }
    return COLOR_BLUE;
}

color_t MEOChasing::BR(uint16_t sequence)
{
    sequence = sequence % 2;
    if (sequence == 0)
    {
        return COLOR_BLUE;
    }
    return COLOR_RED;
}

color_t MEOChasing::CM(uint16_t sequence)
{
    sequence = sequence % 2;
    if (sequence == 0)
    {
        return COLOR_CYAN;
    }
    return COLOR_MAGENTA;
}

color_t MEOChasing::MY(uint16_t sequence)
{
    sequence = sequence % 2;
    if (sequence == 0)
    {
        return COLOR_MAGENTA;
    }
    return COLOR_YELLOW;
}

color_t MEOChasing::YC(uint16_t sequence)
{
    sequence = sequence % 2;
    if (sequence == 0)
    {
        return COLOR_YELLOW;
    }
    return COLOR_CYAN;
}

color_t MEOChasing::RGB(uint16_t sequence)
{
    sequence = sequence % 3;
    if (sequence == 0)
    {
        return COLOR_RED;
    }
    if (sequence == 1)
    {
        return COLOR_GREEN;
    }
    return COLOR_BLUE;
}

color_t MEOChasing::CYM(uint16_t sequence)
{
    sequence = sequence % 3;
    if (sequence == 0)
    {
        return COLOR_CYAN;
    }
    if (sequence == 1)
    {
        return COLOR_YELLOW;
    }
    return COLOR_MAGENTA;
}

color_t MEOChasing::RCGMBY(uint16_t sequence)
{
    sequence = sequence % 6;
    if (sequence == 0)
    {
        return COLOR_RED;
    }
    if (sequence == 1)
    {
        return COLOR_YELLOW;
    }
    if (sequence == 2)
    {
        return COLOR_GREEN;
    }
    if (sequence == 3)
    {
        return COLOR_CYAN;
    }
    if (sequence == 4)
    {
        return COLOR_BLUE;
    }
    return COLOR_MAGENTA;
}

color_t MEOChasing::PurplyBlue(uint16_t sequence)
{
    sequence = sequence % 6;
    if (sequence == 0)
    {
        return COLOR(0,0,11);
    }
    if (sequence == 1)
    {
        return COLOR(3,0,10);
    }
    if (sequence == 2)
    {
        return COLOR(6,0,9);
    }
    if (sequence == 3)
    {
        return COLOR(8,0,8);
    }
    if (sequence == 4)
    {
        return COLOR(6,0,9);
    }
    return COLOR(3,0,10); //5
}

color_t MEOChasing::Valentines(uint16_t sequence)
{
    sequence = sequence % 10;
    if (sequence == 0)
    {
        return COLOR(11,0,0);
    }
    if (sequence == 1)
    {
        return COLOR(11,1,1);
    }
    if (sequence == 2)
    {
        return COLOR(10,2,2);
    }
    if (sequence == 3)
    {
        return COLOR(10,3,3);
    }
    if (sequence == 4)
    {
        return COLOR(9,4,4);
    }
    if (sequence == 5)
    {
        return COLOR(9,9,9);
    }
    if (sequence == 6)
    {
        return COLOR(9,4,4);
    }
    if (sequence == 7)
    {
        return COLOR(10,3,3);
    }
    if (sequence == 8)
    {
        return COLOR(10,2,2);
    }
    return COLOR(11,1,1); //5
}

color_t MEOChasing::BlueBronze(uint16_t sequence)
{
    sequence = sequence % 3;
    if (sequence == 0)
    {
        return COLOR(0x0, 0x2, 0x5);
    }
    if (sequence == 1)
    {
        return COLOR(0x9, 0x8, 0x1);
    }
    return COLOR(0x9, 0x5, 0x1);
}


color_t MEOChasing::BlueTriad(uint16_t sequence)
{
    sequence = sequence % 6;
    if (sequence == 1)
    {
        return COLOR(0xF, 0x5, 0x0);
    }
    if (sequence == 5)
    {
        return COLOR(0xF, 0xC, 0x0);
    }
    return COLOR(0x0, 0x8, 0xF);
}

color_t MEOChasing::BlueTetrad(uint16_t sequence)
{
    sequence = sequence % 4;
    if (sequence == 0)
    {
        return COLOR(0x1, 0x4, 0xB);
    }
    if (sequence == 1)
    {
        return COLOR(0x4, 0x1, 0xB);
    }
    if (sequence == 2)
    {
        return COLOR(0x0, 0xA, 0xA);
    }
    return COLOR(0xF, 0xB, 0x0);
}

color_t MEOChasing::PurpleTetrad(uint16_t sequence)
{
    sequence = sequence % 4;
    if (sequence == 0)
    {
        return COLOR(0xF, 0x0, 0x9);
    }
    if (sequence == 1)
    {
        return COLOR(0xF, 0x0, 0x0);
    }
    if (sequence == 2)
    {
        return COLOR(0xA, 0x0, 0xF);
    }
    return COLOR(0xB, 0xF, 0x0);
}

color_t MEOChasing::GreenTetrad(uint16_t sequence)
{
    sequence = sequence % 4;
    if (sequence == 0)
    {
        return COLOR(0xB, 0xF, 0x0);
    }
    if (sequence == 1)
    {
        return COLOR(0x3, 0xF, 0x0);
    }
    if (sequence == 2)
    {
        return COLOR(0xF, 0xF, 0x0);
    }
    return COLOR(0xF, 0x0, 0xA);
}

color_t MEOChasing::RedAccentedAlalogic(uint16_t sequence) 
{
    sequence = sequence % 3;  //accent removed - % 4 for accent
    if (sequence == 0)
    {
        return COLOR(0xF, 0x0, 0x9);
    }
    if (sequence == 1)
    {
        return COLOR(0xF, 0x7, 0x0);
    }
    if (sequence == 2)
    {
        return COLOR(0xF, 0x0, 0x0);
    }
	return COLOR(0x0, 0xF, 0x0);
}

color_t MEOChasing::GreenAccentedAlalogic(uint16_t sequence)
{
    sequence = sequence % 3;
    if (sequence == 0)
    {
        return COLOR(0xA, 0xF, 0x0);
    }
    if (sequence == 1)
    {
        return COLOR(0x0, 0xF, 0xF);
    }
    if (sequence == 2)
    {
        return COLOR(0x0, 0xF, 0x0);
    }
	return COLOR(0xF, 0x0, 0x0);
}

color_t MEOChasing::BlueAccentedAlalogic(uint16_t sequence)
{
    sequence = sequence % 3;
    if (sequence == 0)
    {
        return COLOR(0x0, 0x9, 0xF); //30 degrees anti-clockwise of Primary
    }
    if (sequence == 1)
    {
        return COLOR(0x7, 0x0, 0xF); //30 degrees clockwise of Primary
    }
    if (sequence == 2)   //Primary
    {
        return COLOR(0x0, 0x0, 0xF);
    }
	return COLOR(0xF, 0xC, 0x0); //180 degrees - Complimentary
}

color_t MEOChasing::ColourCycle(uint16_t sequence)
{
	double cR1;
	double cG1;
	double cB1;
	double cR2;
	double cG2;
	double cB2;
	double cR3;
	double cG3;
	double cB3;
	double cR4;
	double cG4;
	double cB4;

	double hue;
	double sat;
	double lum;

	cR1 = (double) 0x0;
	cG1 = (double) 0x9;
	cB1 = (double) 0xF;
	cR2 = (double) 0x7;
	cG2 = (double) 0x0;
	cB2 = (double) 0xF;
	cR3 = (double) 0x0;
	cG3 = (double) 0x0;
	cB3 = (double) 0xF;
	cR4 = (double) 0xF;
	cG4 = (double) 0xC;

	uint8_t hueShift;
	hueShift = sequence % 16;

    sequence = sequence % 4;
    if (sequence == 0)
    {
		//MEOChasing::RGB_to_HSL(cR1, cG1, cB1, *hue, *sat, *lum);
		//lum = (double)(((uint8_t)lum + hueShift) % 16);
		//MEOChasing::HSL_to_RGB(hue, sat, lum, *cR1, *cG1, *cB1);
        return COLOR((int)cR1, (int)cG1, (int)cB1); //30 degrees anti-clockwise of Primary
    }
    if (sequence == 1)
    {
		//MEOChasing::RGB_to_HSL(cR2, cG2, cB2, *hue, *sat, *lum);
		//lum = (double)(((uint8_t)lum + hueShift) % 16);
		//MEOChasing::HSL_to_RGB(hue, sat, lum, *cR2, *cG2, *cB2);
        return COLOR((int)cR2, (int)cG2, (int)cB2); //30 degrees clockwise of Primary
    }
    if (sequence == 2)   //Primary
    {
		//MEOChasing::RGB_to_HSL(cR3, cG3, cB3, *hue, *sat, *lum);
		//lum = (double)(((uint8_t)lum + hueShift) % 16);
		//MEOChasing::HSL_to_RGB(hue, sat, lum, *cR3, *cG3, *cB3);
        return COLOR((int)cR3, (int)cG3, (int)cB3);
    }
	if (sequence == 3) //180 degrees - Complimentary
    {
		//MEOChasing::RGB_to_HSL(cR4, cG4, cB4, *hue, *sat, *lum);
		//lum = (double)(((uint8_t)lum + hueShift) % 16);
		//MEOChasing::HSL_to_RGB(hue, sat, lum, *cR4, *cG4, *cB4);
		return COLOR((int)cR4, (int)cG4, (int)cB4);
    }
}


/*
A Fast HSL-to-RGB Transform
by Ken Fishkin
from "Graphics Gems", Academic Press, 1990
*/
    /*
     * RGB-HSL transforms.
     * Ken Fishkin, Pixar Inc., January 1989.
     */

    /*
    * given r,g,b on [0 ... 1],
    * return (h,s,l) on [0 ... 1]
    */
void MEOChasing::RGB_to_HSL	(double r, double g, double b, double *h, double *s, double *l)
//double 	r,g,b;
//double *h, *s, *l;
{
    double v;
    double m;
    double vm;
    double r2, g2, b2;

    v = max(r,g);
    v = max(v,b);
    m = min(r,g);
    m = min(m,b);

    if ((*l = (m + v) / 2.0) <= 0.0) return;
    if ((*s = vm = v - m) > 0.0) {
		*s /= (*l <= 0.5) ? (v + m ) :
			(2.0 - v - m) ;
    } else
	return;


    r2 = (v - r) / vm;
    g2 = (v - g) / vm;
    b2 = (v - b) / vm;

    if (r == v)
		*h = (g == m ? 5.0 + b2 : 1.0 - g2);
    else if (g == v)
		*h = (b == m ? 1.0 + r2 : 3.0 - b2);
    else
		*h = (r == m ? 3.0 + g2 : 5.0 - r2);

    	*h /= 6;
	}

    /*
     * given h,s,l on [0..1],
     * return r,g,b on [0..1]
     */

void MEOChasing::HSL_to_RGB(double h, double sl, double l, double *r, double *g, double *b)
//double 	h,sl,l;
//double 	*r, *g, *b;
{
    double v;

    v = (l <= 0.5) ? (l * (1.0 + sl)) : (l + sl - l * sl);
    if (v <= 0) {
		*r = *g = *b = 0.0;
    } else {
		double m;
		double sv;
		int sextant;
		double fract, vsf, mid1, mid2;

		m = l + l - v;
		sv = (v - m ) / v;
		h *= 6.0;
		sextant = h;	
		fract = h - sextant;
		vsf = v * sv * fract;
		mid1 = m + vsf;
		mid2 = v - vsf;
		switch (sextant) {
			case 0: *r = v; *g = mid1; *b = m; break;
			case 1: *r = mid2; *g = v; *b = m; break;
			case 2: *r = m; *g = v; *b = mid1; break;
			case 3: *r = m; *g = mid2; *b = v; break;
			case 4: *r = mid1; *g = m; *b = v; break;
			case 5: *r = v; *g = m; *b = mid2; break;
		}
    }
}
