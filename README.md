G35-MEO-Programs
================

New programs for sowbug's G35 Ardunino 

Uses https://github.com/sowbug/G35Arduino as a framework.

Has new MEOPrograms.cpp / .h with more imaginative programs from other light projects and my own original work. The other light project programs have been modified with more options thought up by me.

- MEORainbow (based on Adafruit's LED light strip sample code: https://github.com/adafruit/LPD8806)
    - wait_: how fast/slow
    - frame_ : spread across string
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
    - rainbowMain_: parameter which rainbow cycles colorMain
- MEOColorPhasing (my own)
    This one is really interesting and evolved by accident. I was messing around with true colour wheels (unlike the MEORainbow program which is actually a 'colour triangle' because of the linear steps) I wasn't able to get the effect that I was trying for (mostly because the G35s are 4 bit colour and they are not evenly set per channel). But by playing around with the frequency and phase, I got this nice effect. It starts out white, then the colours move and get more and more saturated. It never saturates beyond a pastel effect, but it looks really nice anyway
- MEOChasing (my own)
    This is a simple programmable chase effect that has been pre-programmed to do a nice blue-purple chasing effect. Others have been coded too, and they are pretty easy to code your own.

I've a lot of parameters in the programs - however, not being a C++ programmer, I've no idea how to change these from the calling select case statements in MEOProgram.cpp. If anyone can point me in the right direction, I'd be grateful. I'd like to be able to change these parameters from push buttons that I've set up. I'm not posting the code for that and I wan't to keep this repository simple for the time being.

Finally, I've added the .ino file example that I use on my Arduino Mega. This wires up 9 buttons to the analog pins (if not using a Mega, then re-map these pins). Currently only the first 2 buttons do anything - change the program up and down. The missing programs from here are in Sowbug's hub. Eventually this will be self contained.
