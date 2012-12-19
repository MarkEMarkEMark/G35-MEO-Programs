/* -*- mode: c; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2; -*-

   G35: An Arduino library for GE Color Effects G-35 holiday lights.
   Copyright © 2011 The G35 Authors. Use, modification, and distribution are
   subject to the BSD license as described in the accompanying LICENSE file.

By Mike Tsao <github.com/sowbug>. See README for complete attributions. */
 
// and Mark Ortiz
 
//Includes multiple button handling by ladyada: http://www.adafruit.com/blog/2009/10/20/example-code-for-multi-button-checker-with-debouncing/
 
#include <MEOG35String.h>
#include <MEOG35StringGroup.h>
#include <MEOProgramRunner.h>
#include <MEOPrograms.h>
 
//Buttons initialisation
//if you want, you can even run the button checker in the background, which can make for a very easy interface. Remember that you’ll need to clear “just pressed”, etc. after checking or it will be “stuck” on
#define DEBOUNCE 10  // button debouncer, how many ms to debounce, 5+ ms is usually plenty
// here is where we define the buttons that we'll use. button "1" is the first, button "6" is the 6th, etc
byte buttons[] = {54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64}; // the analog A0-15 pins are also known as 54+ on Mega
// This handy macro lets us determine how big the array up above is, by checking the size
#define NUMBUTTONS sizeof(buttons)
// we will track if a button is just pressed, just released, or 'currently pressed'
volatile byte pressed[NUMBUTTONS], justpressed[NUMBUTTONS], justreleased[NUMBUTTONS];
 
//timer
#define PROG_DUR_LONG 86400  //24 hours
#define PROG_DUR_SHORT 120  //2 minutes
 
//Lights initialisation
MEOG35String lights_1(13, 50, 50, 0, false);
//MEOG35String lights_2(12, 50);
 
const int PROGRAM_COUNT = MEOProgramGroup::ProgramCount;
 
MEOProgramGroup programs;
MEOG35StringGroup string_group;
 
bool lightsOn = true;
//bool firstTime = true;
 
MEOLightProgram* CreateProgram(uint8_t program_index, uint8_t pattern)
{
	return programs.CreateProgram(string_group, program_index, pattern);
}
 
// How long each program should run.
uint16_t programDuration = PROG_DUR_SHORT; //set for short first, as random is first
 
MEOProgramRunner runner(CreateProgram, PROGRAM_COUNT, programDuration);
 
void setup()
{
	//Lights
	delay(50);
	 
	lights_1.enumerate();
	//lights_2.enumerate();
	 
	string_group.AddString(&lights_1);
	//string_group.AddString(&lights_2);
	 
	//Buttons
	byte i;
	 
	// Make input & enable pull-up resistors on switch pins
	for (i=0; i< NUMBUTTONS; i++)
	{
		pinMode(buttons[i], INPUT);
		digitalWrite(buttons[i], HIGH);
	}
	 
	// Run timer2 interrupt every 15 ms
	TCCR2A = 0;
	TCCR2B = 1<<CS22 | 1<<CS21 | 1<<CS20;
	 
	//Timer2 Overflow Interrupt Enable
	TIMSK2 |= 1<<TOIE2;

	randomSeed(analogRead(0));
}
 
void loop()
{
	//Lights
	//if (firstTime)
	//{
		//	//ensure not on Random (the other Ethernet Arduino could have put in any state)
		//	programDuration = PROG_DUR_LONG;
		//	runner.program_duration_seconds_ = programDuration;
		//	lightsOn = true;
		//	runner.initial_prog_patt(); //put to first program/pattern
		//	//runner.same_program();
		//	firstTime = false;
	//} else {
		runner.loop();
	//}
	 
	 
	//Buttons
	for (byte myButton = 0; myButton < NUMBUTTONS; myButton++)
	{
		if (justpressed[myButton])
		{
			justpressed[myButton] = 0;
			 
			switch (myButton)
			{
				case 0: //program Up
				runner.switch_program(true);
				break;
				case 1: //program Down
				runner.switch_program(false);
				break;
				case 2: //variation up
				runner.switch_pattern(true);
				break;
				case 3: //variation down
				runner.switch_pattern(false);
				break;
				case 9: //toggle random program
				if (programDuration == PROG_DUR_SHORT)
				{
					programDuration = PROG_DUR_LONG;
					runner.program_duration_seconds_ = programDuration;
					runner.same_program();
				}
				else
				{
					programDuration = PROG_DUR_SHORT;
					runner.program_duration_seconds_ = programDuration;
					runner.random_program();
				}
				break;
				case 10: //toggle off / on
				if (lightsOn)
				{
					lightsOn = false;
					runner.program_duration_seconds_ = PROG_DUR_LONG;
					runner.same_program();
					runner.turn_off();
				}
				else
				{
					lightsOn = true;
					runner.program_duration_seconds_ = programDuration;
					runner.same_program();
				}
				break;
			}
		}
	}
}
 
//Debounce buttons - nothing to do with lights...
SIGNAL(TIMER2_OVF_vect)
{
	check_switches();
}
 
void check_switches()
{
	static byte previousstate[NUMBUTTONS];
	static byte currentstate[NUMBUTTONS];
	static long lasttime;
	byte index;
	 
	if (millis() < lasttime)
	{
		// we wrapped around, lets just try again
		lasttime = millis();
	}
	 
	if ((lasttime + DEBOUNCE) > millis())
	{
		// not enough time has passed to debounce
		return;
	}
	 
	// ok we have waited DEBOUNCE milliseconds, lets reset the timer
	lasttime = millis();
	 
	for (index = 0; index < NUMBUTTONS; index++)
	{
		currentstate[index] = digitalRead(buttons[index]);   // read the button
		if (currentstate[index] == previousstate[index])
		{
			if ((pressed[index] == LOW) && (currentstate[index] == LOW))
			{
				// just pressed
				justpressed[index] = 1;
			}
			else if ((pressed[index] == HIGH) && (currentstate[index] == HIGH))
			{
				// just released
				justreleased[index] = 1;
			}
			pressed[index] = !currentstate[index];  // remember, digital HIGH means NOT pressed
		}
		previousstate[index] = currentstate[index];   // keep a running tally of the buttons
	}
}
 
