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
byte buttons[] = {54, 55, 56, 57, 58, 59, 60, 61, 62}; // the analog A0-15 pins are also known as 54+ on Mega
// This handy macro lets us determine how big the array up above is, by checking the size
#define NUMBUTTONS sizeof(buttons)
// we will track if a button is just pressed, just released, or 'currently pressed' 
volatile byte pressed[NUMBUTTONS], justpressed[NUMBUTTONS], justreleased[NUMBUTTONS];


//Lights initialisation
MEOG35String lights_1(13, 50, 50, 0, false);
MEOG35String lights_2(12, 50);

const int PROGRAM_COUNT = MEOProgramGroup::ProgramCount ;//+ PlusProgramGroup::ProgramCount;

MEOProgramGroup programs;
MEOG35StringGroup string_group;

uint8_t program_index = 0; //the main program - rainbow/simplexnoise etc
uint8_t pattern = 0; //the sub-program - colour scheme etc.

MEOLightProgram* CreateProgram(uint8_t program_index, uint8_t pattern) {
	return programs.CreateProgram(string_group, program_index, pattern);
}

// How long each program should run.
uint16_t PROGRAM_DURATION_SECONDS = 86400; //24 hours

MEOProgramRunner runner(CreateProgram, PROGRAM_COUNT, PROGRAM_DURATION_SECONDS);

void setup() {
	//Lights
	delay(50);

	lights_1.enumerate();
	lights_2.enumerate();

	string_group.AddString(&lights_1);
	string_group.AddString(&lights_2);

    //Buttons
    byte i;

	// set up serial port
	Serial.begin(9600);
	Serial.print("Button checker with ");
	Serial.print(NUMBUTTONS, DEC);
	Serial.println(" buttons");

	// Make input & enable pull-up resistors on switch pins
	for (i=0; i< NUMBUTTONS; i++) {
		pinMode(buttons[i], INPUT);
		digitalWrite(buttons[i], HIGH);
	}

	// Run timer2 interrupt every 15 ms 
	TCCR2A = 0;
	TCCR2B = 1<<CS22 | 1<<CS21 | 1<<CS20;

	//Timer2 Overflow Interrupt Enable
	TIMSK2 |= 1<<TOIE2;
}

void loop() {
	//Lights
	runner.loop();

	//Buttons
	for (byte myButton = 0; myButton < NUMBUTTONS; myButton++) {
		if (justpressed[myButton]) {
			justpressed[myButton] = 0;

			Serial.print("Button: ");
			Serial.print(myButton);
			Serial.print("    ProgramIndex: ");
			Serial.print(program_index);
			Serial.print("    Pattern: ");
			Serial.println(pattern);

            switch (myButton) {
				case 0:
					program_index++;
					runner.switch_program(true);
					break;
				case 1:
					program_index--;
					runner.switch_program(false);
					break;
				case 2:
					pattern++;
					runner.switch_pattern(true);
					break;
				case 3:
					pattern--;
					runner.switch_pattern(false);
					break;
				case 7:
					if (PROGRAM_DURATION_SECONDS == 1)
					{
						PROGRAM_DURATION_SECONDS = 86400;
					} else {
						PROGRAM_DURATION_SECONDS = 1;
					}
					runner.switch_pattern(false);
					break;
			}
		}
	}
}

//Debounce buttons - nothing to do with lights...
SIGNAL(TIMER2_OVF_vect) {
	check_switches();
}

void check_switches()
{
	static byte previousstate[NUMBUTTONS];
	static byte currentstate[NUMBUTTONS];
	static long lasttime;
	byte index;

	if (millis() < lasttime) {
		// we wrapped around, lets just try again
		lasttime = millis();
	}

	if ((lasttime + DEBOUNCE) > millis()) {
		// not enough time has passed to debounce
		return;
	}

	// ok we have waited DEBOUNCE milliseconds, lets reset the timer
	lasttime = millis();

	for (index = 0; index < NUMBUTTONS; index++) {
		currentstate[index] = digitalRead(buttons[index]);   // read the button
		if (currentstate[index] == previousstate[index]) {
			if ((pressed[index] == LOW) && (currentstate[index] == LOW)) {
				// just pressed
				justpressed[index] = 1;
			}
			else if ((pressed[index] == HIGH) && (currentstate[index] == HIGH)) {
				// just released
				justreleased[index] = 1;
			}
			pressed[index] = !currentstate[index];  // remember, digital HIGH means NOT pressed
		}
		previousstate[index] = currentstate[index];   // keep a running tally of the buttons
	}
}