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

MEOChasing::MEOChasing(G35& g35, uint8_t pattern)
  : LightProgram(g35, pattern), count_(1), sequence_(0), wait_(10), pattern_(pattern) {
  Serial.print("MEOChasing Pattern: ");
  Serial.println(pattern);}

uint32_t MEOChasing::Do() {
	uint8_t patternLimited = pattern_ % 24;
	switch (patternLimited) {
		case 0: g35_.fill_sequence(0, count_, sequence_, 5, G35::MAX_INTENSITY, RGBY); break;
		case 1: g35_.fill_sequence(0, count_, sequence_, 10, G35::MAX_INTENSITY, RWB); break;
		case 2: g35_.fill_sequence(0, count_, sequence_, 5, G35::MAX_INTENSITY, RC); break;
		case 3: g35_.fill_sequence(0, count_, sequence_, 5, G35::MAX_INTENSITY, GM); break;
		case 4: g35_.fill_sequence(0, count_, sequence_, 5, G35::MAX_INTENSITY, BY); break;
		case 5: g35_.fill_sequence(0, count_, sequence_, 2, G35::MAX_INTENSITY, RCGMBY); break;
		case 6: g35_.fill_sequence(0, count_, sequence_, 5, G35::MAX_INTENSITY, RG); break;
		case 7: g35_.fill_sequence(0, count_, sequence_, 5, G35::MAX_INTENSITY, GB); break;
		case 8: g35_.fill_sequence(0, count_, sequence_, 5, G35::MAX_INTENSITY, BR); break;
		case 9: g35_.fill_sequence(0, count_, sequence_, 5, G35::MAX_INTENSITY, CM); break;
		case 10: g35_.fill_sequence(0, count_, sequence_, 5, G35::MAX_INTENSITY, MY); break;
		case 11: g35_.fill_sequence(0, count_, sequence_, 5, G35::MAX_INTENSITY, YC); break;
		case 12: g35_.fill_sequence(0, count_, sequence_, 5, G35::MAX_INTENSITY, RGB); break;
		case 13: g35_.fill_sequence(0, count_, sequence_, 5, G35::MAX_INTENSITY, CYM); break;
		case 14: g35_.fill_sequence(0, count_, sequence_, 1, G35::MAX_INTENSITY, PurplyBlue); break;
		case 15: g35_.fill_sequence(0, count_, sequence_, 1, G35::MAX_INTENSITY, Valentines); break;
		case 16: g35_.fill_sequence(0, count_, sequence_, 1, G35::MAX_INTENSITY, BlueBronze); break;
		case 17: g35_.fill_sequence(0, count_, sequence_, 1, G35::MAX_INTENSITY, BlueTriad); break;
		case 18: g35_.fill_sequence(0, count_, sequence_, 1, G35::MAX_INTENSITY, BlueTetrad); break;
		case 19: g35_.fill_sequence(0, count_, sequence_, 1, G35::MAX_INTENSITY, PurpleTetrad); break;
		case 20: g35_.fill_sequence(0, count_, sequence_, 1, G35::MAX_INTENSITY, GreenTetrad); break;
		case 21: g35_.fill_sequence(0, count_, sequence_, 1, G35::MAX_INTENSITY, GreenAccentedAlalogic); break;
		case 22: g35_.fill_sequence(0, count_, sequence_, 1, G35::MAX_INTENSITY, RedAccentedAlalogic); break;
		case 23: g35_.fill_sequence(0, count_, sequence_, 1, G35::MAX_INTENSITY, BlueAccentedAlalogic); break;
		default: g35_.fill_sequence(0, count_, sequence_, 2, G35::MAX_INTENSITY, PastelRGB); break;
	}
	if (count_ < light_count_) {
		++count_;
	} else {
		++sequence_;
	}
	delay(wait_);
	return bulb_frame_;
}

// static
color_t MEOChasing::PastelRGB(uint16_t sequence) {
  sequence = sequence % 3;
  if (sequence == 0) {
    return COLOR(0xf, 0x2, 0x1);
  }
  if (sequence == 1) {
    return COLOR(0x8, 0xf, 0x2);
  }
  return COLOR(0xb, 0x5, 0xf);
}

color_t MEOChasing::RGBY(uint16_t sequence) {
  sequence = sequence % 4;
  if (sequence == 0) {
    return COLOR_RED;
  }
  if (sequence == 1) {
    return COLOR_GREEN;
  }
  if (sequence == 2) {
    return COLOR_BLUE;
  }
  return COLOR_YELLOW;
}

color_t MEOChasing::RWB(uint16_t sequence) {
  sequence = sequence % 3;
  if (sequence == 0) {
    return COLOR_RED;
  }
  if (sequence == 1) {
    return COLOR_WHITE;
  }
  return COLOR_BLUE;
}

color_t MEOChasing::RC(uint16_t sequence) {
  sequence = sequence % 2;
  if (sequence == 0) {
    return COLOR_RED;
  }
  return COLOR_CYAN;
}

color_t MEOChasing::GM(uint16_t sequence) {
  sequence = sequence % 2;
  if (sequence == 0) {
    return COLOR_GREEN;
  }
  return COLOR_MAGENTA;
}

color_t MEOChasing::BY(uint16_t sequence) {
  sequence = sequence % 2;
  if (sequence == 0) {
    return COLOR_BLUE;
  }
  return COLOR_YELLOW;
}

color_t MEOChasing::RG(uint16_t sequence) {
  sequence = sequence % 2;
  if (sequence == 0) {
    return COLOR_RED;
  }
  return COLOR_GREEN;
}

color_t MEOChasing::GB(uint16_t sequence) {
  sequence = sequence % 2;
  if (sequence == 0) {
    return COLOR_GREEN;
  }
  return COLOR_BLUE;
}

color_t MEOChasing::BR(uint16_t sequence) {
  sequence = sequence % 2;
  if (sequence == 0) {
    return COLOR_BLUE;
  }
  return COLOR_RED;
}

color_t MEOChasing::CM(uint16_t sequence) {
  sequence = sequence % 2;
  if (sequence == 0) {
    return COLOR_CYAN;
  }
  return COLOR_MAGENTA;
}

color_t MEOChasing::MY(uint16_t sequence) {
  sequence = sequence % 2;
  if (sequence == 0) {
    return COLOR_MAGENTA;
  }
  return COLOR_YELLOW;
}

color_t MEOChasing::YC(uint16_t sequence) {
  sequence = sequence % 2;
  if (sequence == 0) {
    return COLOR_YELLOW;
  }
  return COLOR_CYAN;
}

color_t MEOChasing::RGB(uint16_t sequence) {
  sequence = sequence % 3;
  if (sequence == 0) {
    return COLOR_RED;
  }
  if (sequence == 1) {
    return COLOR_GREEN;
  }
  return COLOR_BLUE;
}

color_t MEOChasing::CYM(uint16_t sequence) {
  sequence = sequence % 3;
  if (sequence == 0) {
    return COLOR_CYAN;
  }
  if (sequence == 1) {
    return COLOR_YELLOW;
  }
  return COLOR_MAGENTA;
}

color_t MEOChasing::RCGMBY(uint16_t sequence) {
  sequence = sequence % 6;
  if (sequence == 0) {
    return COLOR_RED;
  }
  if (sequence == 1) {
    return COLOR_CYAN;
  }
  if (sequence == 2) {
    return COLOR_GREEN;
  }
  if (sequence == 3) {
    return COLOR_MAGENTA;
  }
  if (sequence == 4) {
    return COLOR_BLUE;
  }
  return COLOR_YELLOW;
}

color_t MEOChasing::PurplyBlue(uint16_t sequence) {
  sequence = sequence % 6;
  if (sequence == 0) {
    return COLOR(0,0,11);
  }
  if (sequence == 1) {
    return COLOR(3,0,10);
  }
  if (sequence == 2) {
    return COLOR(6,0,9);
  }
  if (sequence == 3) {
    return COLOR(8,0,8);
  }
  if (sequence == 4) {
    return COLOR(6,0,9);
  }
  return COLOR(3,0,10); //5
}

color_t MEOChasing::Valentines(uint16_t sequence) {
  sequence = sequence % 10;
  if (sequence == 0) {
    return COLOR(11,0,0);
  }
  if (sequence == 1) {
    return COLOR(11,1,1);
  }
  if (sequence == 2) {
    return COLOR(10,2,2);
  }
  if (sequence == 3) {
    return COLOR(10,3,3);
  }
  if (sequence == 4) {
    return COLOR(9,4,4);
  }
  if (sequence == 5) {
    return COLOR(9,9,9);
  }
  if (sequence == 6) {
    return COLOR(9,4,4);
  }
  if (sequence == 7) {
    return COLOR(10,3,3);
  }
  if (sequence == 8) {
    return COLOR(10,2,2);
  }
  return COLOR(11,1,1); //5
}

color_t MEOChasing::BlueBronze(uint16_t sequence) {
  sequence = sequence % 3;
  if (sequence == 0) {
    return COLOR(0x0, 0x2, 0x5);
  }
  if (sequence == 1) {
    return COLOR(0x9, 0x8, 0x1);
  }
  return COLOR(0x9, 0x5, 0x1);
}


color_t MEOChasing::BlueTriad(uint16_t sequence) {
  sequence = sequence % 6;
  if (sequence == 1) {
    return COLOR(0xF, 0x5, 0x0);
  }
  if (sequence == 5) {
    return COLOR(0xF, 0xC, 0x0);
  }
  return COLOR(0x0, 0x8, 0xF);
  }

color_t MEOChasing::BlueTetrad(uint16_t sequence) {
  sequence = sequence % 4;
  if (sequence == 0) {
    return COLOR(0x1, 0x4, 0xB);
  }
  if (sequence == 1) {
    return COLOR(0x4, 0x1, 0xB);
  }
  if (sequence == 2) {
    return COLOR(0x0, 0xA, 0xA);
  }
  return COLOR(0xF, 0xB, 0x0);
  }

color_t MEOChasing::PurpleTetrad(uint16_t sequence) {
  sequence = sequence % 4;
  if (sequence == 0) {
    return COLOR(0xF, 0x0, 0x9);
  }
  if (sequence == 1) {
    return COLOR(0xF, 0x0, 0x0);
  }
  if (sequence == 2) {
    return COLOR(0xA, 0x0, 0xF);
  }
  return COLOR(0xB, 0xF, 0x0);
  }

  color_t MEOChasing::GreenTetrad(uint16_t sequence) {
  sequence = sequence % 4;
  if (sequence == 0) {
    return COLOR(0xB, 0xF, 0x0);
  }
  if (sequence == 1) {
    return COLOR(0x3, 0xF, 0x0);
  }
  if (sequence == 2) {
    return COLOR(0xF, 0xF, 0x0);
  }
  return COLOR(0xF, 0x0, 0xA);
  }

color_t MEOChasing::RedAccentedAlalogic(uint16_t sequence) {
  sequence = sequence % 3;
  if (sequence == 0) {
    return COLOR(0xF, 0x0, 0x9);
  }
  if (sequence == 1) {
    return COLOR(0xF, 0x7, 0x0);
  }
  if (sequence == 2) {
	return COLOR(0xF, 0x0, 0x0);
  }
  return COLOR(0x0, 0xF, 0x0);
  }

color_t MEOChasing::GreenAccentedAlalogic(uint16_t sequence) {
  sequence = sequence % 3;
  if (sequence == 0) {
    return COLOR(0xA, 0xF, 0x0);
  }
  if (sequence == 1) {
    return COLOR(0x0, 0xF, 0xF);
  }
  if (sequence == 2) {
	return COLOR(0x0, 0xF, 0x0);
  }
  return COLOR(0xF, 0x0, 0x0);
  }

color_t MEOChasing::BlueAccentedAlalogic(uint16_t sequence) {
  sequence = sequence % 3;
  if (sequence == 0) {
    return COLOR(0x0, 0x9, 0xF); //30 degrees anti-clockwise of Primary
  }
  if (sequence == 1) {
    return COLOR(0x7, 0x0, 0xF); //30 degrees clockwise of Primary
  }
  if (sequence == 2) { //Primary
    return COLOR(0x0, 0x0, 0xF);
  }
  return COLOR(0xF, 0xC, 0x0); //180 degrees - Complimentary
  }