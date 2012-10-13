/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and happyinmotion http://happyinmotion.livejournal.com/278357.html

  See README for complete attributions.
*/

#include <MEOSimplexNoise.h>


MEOSimplexNoise::MEOSimplexNoise(MEOG35& g35, uint8_t pattern) : MEOLightProgram(g35, pattern), rMult_(1.0), gMult_(1.0), bMult_(1.0), spaceinc_(0.1), timeinc_(0.08), yoffset_(0.0), pattern_(pattern)
{
}

#define PI 3.14159265
#define onethird 0.333333333
#define onesixth 0.166666667
#define numSpacing 18

int i, j, k, A[] = {0, 0, 0};
float u, v, w, s;
int T[] = {0x15, 0x38, 0x32, 0x2c, 0x0d, 0x13, 0x07, 0x2a};

uint32_t MEOSimplexNoise::Do()
{
    // Simplex noise for whole strip of 96 LEDs.
    // (Well, it's simplex noise for 6 LEDs and cubic interpolation between those nodes.)
    // Simplex noise parameters:
    // Useable values for time increment range from 0.005 (barely perceptible) to 0.2 (irritatingly flickery)
    // 0.02 seems ideal for relaxed screensaver
    float bulbArray_red[light_count_ + 1];
    float bulbArray_green[light_count_ + 1];
    float bulbArray_blue[light_count_ + 1];
    float bulbArray_hue[light_count_ + 1];
    float bulbArray_brightness[light_count_ + 1];
    int node_spacing = light_count_ / numSpacing;

    switch (pattern_ % 13)
    {
    case 0:
        rMult_ = 1.0;
        gMult_ = 1.0;
        bMult_ = 1.0;
        break;
    case 1:
        rMult_ = 1.0;
        gMult_ = 0.0;
        bMult_ = 1.0;
        break;
    case 2:
        rMult_ = 0.0;
        gMult_ = 1.0;
        bMult_ = 1.0;
        break;
    case 3:
        rMult_ = 1.0;
        gMult_ = 1.0;
        bMult_ = 0.0;
        break;
    case 4:
        rMult_ = 1.0;
        gMult_ = 0.0;
        bMult_ = 0.0;
        break;
    case 5:
        rMult_ = 0.0;
        gMult_ = 1.0;
        bMult_ = 0.0;
        break;
    case 6:
        rMult_ = 0.0;
        gMult_ = 0.0;
        bMult_ = 1.0;
        break;
    case 7:
        rMult_ = 0.2;
        gMult_ = 0.0;
        bMult_ = 1.0;
        break;
    case 8:
        rMult_ = 0.0;
        gMult_ = 0.2;
        bMult_ = 1.0;
        break;
    case 9:
        rMult_ = 1.0;
        gMult_ = 0.2;
        bMult_ = 0.0;
        break;
    case 10:
        rMult_ = 1.0;
        gMult_ = 0.0;
        bMult_ = 0.2;
        break;
    case 11:
        rMult_ = 0.0;
        gMult_ = 1.0;
        bMult_ = 0.2;
        break;
    case 12:
        rMult_ = 0.2;
        gMult_ = 1.0;
        bMult_ = 0.0;
        break;
    }


// MEO: put happyinmotion's control constants (timeinc, spaceinc, yoffset, repeats) into function as parameters
    // added more control to colours by putting in multipier for each of R G B (0.0 to 1.0)
    // Simplex noise parameters:
    // Useable values for time increment range from 0.005 (barely perceptible) to 0.2 (irritatingly flickery)
    // 0.02 seems ideal for relaxed screensaver
    // Useable values for space increment range from 0.8 (LEDS doing different things to their neighbours), to 0.02 (roughly one feature present in 15 LEDs).
    // 0.05 seems ideal for relaxed screensaver

    // Calculate simplex noise for LEDs that are nodes:
    // Store raw values from simplex function (-0.347 to 0.347)

    float xoffset = 0.0;
    for (int i = 0; i <= light_count_; i = i + node_spacing)
    {
        xoffset += spaceinc_;
        bulbArray_red[i] = MEOSimplexNoise::SimplexNoise(xoffset, yoffset_, 0);
        bulbArray_green[i] = MEOSimplexNoise::SimplexNoise(xoffset, yoffset_, 1);
        bulbArray_blue[i] = MEOSimplexNoise::SimplexNoise(xoffset, yoffset_, 2);
    }

    // Interpolate values for LEDs between nodes
    for (int i = 0; i < light_count_; i++)
    {
        int position_between_nodes = i % node_spacing;
        int last_node, next_node;

        // If at node, skip
        if ( position_between_nodes == 0 )
        {
            // At node for simplex noise, do nothing but update which nodes we are between
            last_node = i;
            next_node = last_node + node_spacing;
        }
        // Else between two nodes, so identify those nodes
        else
        {
            // And interpolate between the values at those nodes for red, green, and blue
            float t = float(position_between_nodes) / float(node_spacing);
            float t_squaredx3 = 3*t*t;
            float t_cubedx2 = 2*t*t*t;
            bulbArray_red[i] = bulbArray_red[last_node] * ( t_cubedx2 - t_squaredx3 + 1.0 ) + bulbArray_red[next_node] * ( -t_cubedx2 + t_squaredx3 );
            bulbArray_green[i] = bulbArray_green[last_node] * ( t_cubedx2 - t_squaredx3 + 1.0 ) + bulbArray_green[next_node] * ( -t_cubedx2 + t_squaredx3 );
            bulbArray_blue[i] = bulbArray_blue[last_node] * ( t_cubedx2 - t_squaredx3 + 1.0 ) + bulbArray_blue[next_node] * ( -t_cubedx2 + t_squaredx3 );
        }
    }

    // Convert values from raw noise to scaled r,g,b and feed to strip
    for (int i = 0; i < light_count_; i++)
    {
        int r = int(bulbArray_red[i]*403 + 16);
        int g = int(bulbArray_green[i]*403 + 16);
        int b = int(bulbArray_blue[i]*403 + 16);

        if (r > 15)
        {
            r = 15;
        }
        else if (r < 0)
        {
            r = 0;    // Adds no time at all. Conclusion: constrain() sucks.
        }

        if (g > 15)
        {
            g = 15;
        }
        else if (g < 0)
        {
            g = 0;
        }

        if (b > 15)
        {
            b = 15;
        }
        else if (b < 0 )
        {
            b = 0;
        }

        if (rMult_ > 1.0)
        {
            rMult_ = 1.0;
        }
        else if (rMult_ < 0.0)
        {
            rMult_ = 0.0;
        }

        if (gMult_ > 1.0)
        {
            gMult_ = 1.0;
        }
        else if (gMult_ < 0.0)
        {
            gMult_ = 0.0;
        }

        if (bMult_ > 1.0)
        {
            bMult_ = 1.0;
        }
        else if (bMult_ < 0.0)
        {
            bMult_ = 0.0;
        }

        g35_.fill_color(i, 1, MEOG35::MAX_INTENSITY, COLOR(int(r * rMult_), int(g * gMult_), int(b * bMult_)));
    }
    yoffset_ += timeinc_;

    return bulb_frame_;
}

// Simplex noise code:
// From an original algorythm by Ken Perlin.
// Returns a value in the range of about [-0.347 .. 0.347]
float MEOSimplexNoise::SimplexNoise(float x, float y, float z)
{
    // Skew input space to relative coordinate in simplex cell
    s = (x + y + z) * onethird;
    i = fastfloor(x+s);
    j = fastfloor(y+s);
    k = fastfloor(z+s);

    // Unskew cell origin back to (x, y , z) space
    s = (i + j + k) * onesixth;
    u = x - i + s;
    v = y - j + s;
    w = z - k + s;;

    A[0] = A[1] = A[2] = 0;

    // For 3D case, the simplex shape is a slightly irregular tetrahedron.
    // Determine which simplex we're in
int hi = u >= w ? u >= v ? 0 : 1 : v >= w ? 1 : 2;
int lo = u < w ? u < v ? 0 : 1 : v < w ? 1 : 2;

    return k_fn(hi) + k_fn(3 - hi - lo) + k_fn(lo) + k_fn(0);
}

int MEOSimplexNoise::fastfloor(float n)
{
    return n > 0 ? (int) n : (int) n - 1;
}

float MEOSimplexNoise::k_fn(int a)
{
    s = (A[0] + A[1] + A[2]) * onesixth;
    float x = u - A[0] + s;
    float y = v - A[1] + s;
    float z = w - A[2] + s;
    float t = 0.6f - x * x - y * y - z * z;
    int h = shuffle(i + A[0], j + A[1], k + A[2]);
    A[a]++;
    if (t < 0) return 0;
    int b5 = h >> 5 & 1;
    int b4 = h >> 4 & 1;
    int b3 = h >> 3 & 1;
    int b2 = h >> 2 & 1;
    int b = h & 3;
    float p = b == 1 ? x : b == 2 ? y : z;
    float q = b == 1 ? y : b == 2 ? z : x;
    float r = b == 1 ? z : b == 2 ? x : y;
    p = b5 == b3 ? -p : p;
    q = b5 == b4 ? -q: q;
    r = b5 != (b4^b3) ? -r : r;
    t *= t;
    return 8 * t * t * (p + (b == 0 ? q + r : b2 == 0 ? q : r));
}

int MEOSimplexNoise::shuffle(int i, int j, int k)
{
    return b(i, j, k, 0) + b(j, k, i, 1) + b(k, i, j, 2) + b(i, j, k, 3) + b(j, k, i, 4) + b(k, i, j, 5) + b(i, j, k, 6) + b(j, k, i, 7);
}

int MEOSimplexNoise::b(int i, int j, int k, int B)
{
    return T[b(i, B) << 2 | b(j, B) << 1 | b(k, B)];
}

int MEOSimplexNoise::b(int N, int B)
{
    return N >> B & 1;
}