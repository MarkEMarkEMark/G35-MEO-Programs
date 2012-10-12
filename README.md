G35-MEO-Programs
================

ToDo:
- add button for random program/variation every minute
- add sub-variation buttons (e.g. for chaser - Primary colours programs, and more subtle pleasing ones)
- add variations to Phasing


This is heavily based on sowbug's G35 Ardunino library (https://github.com/sowbug/G35Arduino)

However, rather than being timer based, it requires 4 push buttons to set the programs. Also it has totally new MEOPrograms.cpp / .h with more imaginative programs from other light projects I've come acress including my own original work and modifications.

This is preset for an Arduino Mega2560, but could easily be altered for other boards (sowbug has said that one program crashes his low memory board though)

Due to my modifications, the programs will no longer work with sowbug's originals, however his are easily modified to allow them to work once again.

The four buttons should be wired to A0-A3, and perform as follows:

- A0: Program Up
- A1: Program Down
- A2: Variation Up
- A3: Variation Down

The programs and variations are, as follows:

- Whites
    - Warm White
    - Cold White
    - Warm and Cold White
- Rainbow
    - Autumn Red & Green (spread across strings)
    - Ocean Green & Blue (spread across strings)
    - Pretty Blue & Red (spread across strings)
    - Full Rainbow (spread across strings)
    - Autumn Red & Green
    - Ocean Green & Blue
    - Pretty Blue & Red
    - Full Rainbow
- Random Stobe
    - Black background / White flash
    - Blue background / White flash
    - Red background / White flash
    - Green background / White flash
    - Black background / Rainbow flash - each bulb flashes before colour change
    - Black background / Rainbow flash - colour changes with each flash
    - Rainbow background / white flash - colour changes gradually
    - Rainbow background / white flash - each background a different colour
- Simplex Noise
    - Red, Green and Blue
    - Red and Blue
    - Green and Blue
    - Red and Green
    - Red
    - Green
    - Blue
    - Blue and dull Red
    - Blue and dull Green
    - Red and dull Green
    - Red and dull Blue
    - Green and dull Blue
    - Green and dull Red
- Sine Wave
    - Candystripe Red
    - Green
    - Blue
    - Yellow
    - Magenta
    - Cyan
    - Rainbow
- Chaser
    - Green Analogic
    - Red Analogic
    - Blue Analogic
    - Purply Blues
    - Valentines
    - Blue Triad
    - Blue Tetrad
    - Purple Tetrad
    - Green Tetrad
    - Red, Green, Blue & Yellow
    - Red, White & Blue
    - Red & Cyan
    - Green & Magenta
    - Blue & Yellow
    - Red, Cyan, Green, Magenta, Blue & Yellow
    - Red & Green
    - Green & Blue
    - Blue & Red
    - Cyan & Magenta
    - Magenta & Yellow
    - Yellow & Cyan
    - Red, Green & Blue
    - Cyan, Yellow & Magenta
    - Pastels
- Colour Phasing (This is really interesting and evolved by accident. I was messing around with true colour wheels (unlike the MEORainbow program which is actually a 'colour triangle' because of the linear steps) I wasn't able to get the effect that I was trying for (mostly because the G35s are 4 bit colour and they are not evenly set per channel). But by playing around with the frequency and phase, I got this nice effect. It starts out white, then the colours move and get more and more saturated. It never saturates beyond a pastel effect, but it looks really nice anyway)

There are parameters that I've allowed for that I'll eventually make into sub-variations on other buttons

- MEORainbow (based on Adafruit's LED light strip sample code: https://github.com/adafruit/LPD8806)
    - wait_: how fast/slow
    - frame_ : spread across string
    - type_: 0 to 3 - 0 is full rainbow. 1 is a nice autumnal red/green. 2 is green/blue. 3 is blue/red 
- MEORandomStrobe (my own)
    - noAtATime_ : how many simultaneous lights (don't do too many - between 1 and 5 is good)
    - colorMain_ : background colour (a nice start is dark blue - COLOR(0,0,4))
    - colorFlash_ : the flashing colour (try COLOR(15,15,15))
    - rainbowFlash_ : overrides colorFlash with a gradual colour cycle
    - rainbowFrame_ : if using rainbowFlash, will either change colour with each light flash, or when all bulbs have flashed
    - wait_ : how fast/slow
- MEOSimplexNoise (based on happyinmotion's noise experiments http://happyinmotion.livejournal.com/278357.html)
    - rMult/gMult/bMult_ - how much RGB to use (0.0 to 1.0)
- MEOSineWave (based on Adafruit's LED light strip sample code: https://github.com/adafruit/LPD8806)
    - wavesPerString_: which harmonic (i.e. waves per string)
    - colorMain_ : the main colour to use (e.g. COLOR(15,0,0))
    - colorHi_ : the peak of the wave (e.g. COLOR(12,12,12))
    - colourLo_ : the trough of the wave (e.g. COLOR(0,0,0)) - these colours give a nice candy strip effect
    - rainbowMain_: parameter which rainbow cycles colorMain
- MEOColorPhasing (my own)
- MEOChasing (my own)
    This is a simple programmable chase effect that has been pre-programmed to do a nice blue-purple chasing effect. Others have been coded too, and they are pretty easy to code your own.

Feel free to email me if you have any problems setting up.

Thanks to sowbug (Mike Tsao) and, of course, Robert Quattlebaum (DeepDarc - http://www.deepdarc.com/2010/11/27/hacking-christmas-lights/) and Scott Harris and Paul Martis