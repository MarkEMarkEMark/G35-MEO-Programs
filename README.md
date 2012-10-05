G35-MEO-Programs
================

New programs for sowbug's G35 Ardunino 

Uses https://github.com/sowbug/G35Arduino as a framework.

Has new MEOPrograms.cpp / .h with more imaginative programs from other light projects and my own original work. The other light project programs have been modified with more options thought up by me.

- MEORainbow1 (based on Adafruit's LED light strip sample code: https://github.com/adafruit/LPD8806)
    - wait_: how fast/slow
- MEORainbow2 (based on Adafruit's LED light strip sample code: https://github.com/adafruit/LPD8806)
    - wait_: how fast/slow
- MEORandomStrobe (my own)
    - noAtATime_ : how many simultaneous lights (don't do too many - between 1 and 5 is good)
    - colorMain_ : background colour (a nice start is dark blue - COLOR(0,0,4))
    - colorFlash_ : the flashing colour (try COLOR(15,15,15))
    - rainbowFlash_ : overrides colorFlash with a gradual colour cycle
    - rainbowFrame_ : if using rainbowFlash, will either change colour with each light flash, or when all bulbs have flashed
    - wait_ : how fast/slow
- MEOSimplexNoise (based on happyinmotion's noise experiments http://happyinmotion.livejournal.com/278357.html)
    - rMult/gMult/bMult_ - how much RGB to use (e.g. 0.0 or 1.0)
- MEOSineWave (based on Adafruit's LED light strip sample code: https://github.com/adafruit/LPD8806)
    - wavesPerString_: which harmonic (i.e. waves per string)
    - colorMain_ : the main colour to use (e.g. COLOR(15,0,0))
    - colorHi_ : the peak of the wave (e.g. COLOR(12,12,12))
    - colourLo_ : the trough of the wave (e.g. COLOR(0,0,0)) - these colours give a nice candy strip effect
       - ToDo: add a rainbowWave parameter which cycles colorMain


I've a lot of parameters in the programs - however, not being a C++ programmer, I've no idea how to change these from the calling select case statements in MEOProgram.cpp. If anyone can point me in the right direction, I'd be grateful. I'd like to be able to change these parameters from push buttons that I've set up. I'm not posting the code for that and I wan't to keep this repository simple for the time being.