/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2012 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and happyinmotion http://happyinmotion.livejournal.com/278357.html

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_PROGRAMS_MEO_SIMPLEX_NOISE_H
#define INCLUDE_G35_PROGRAMS_MEO_SIMPLEX_NOISE_H

#include <MEOLightProgram.h>

class MEOSimplexNoise : public MEOLightProgram
{
public:
    MEOSimplexNoise(MEOG35& g35, uint8_t pattern);
    uint32_t Do();

private:
    float SimplexNoise(float x, float y, float z);
    int fastfloor(float n);
    float k_fn(int a);
    int shuffle(int i, int j, int k);
    int b(int i, int j, int k, int B);
    int b(int N, int B);

    float rMult_;
    float gMult_;
    float bMult_;
    float spaceinc_;
    float timeinc_;
    float yoffset_;
    uint8_t pattern_;
};

#endif