/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <github.com/sowbug>.

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_MEO_PROGRAM_RUNNER_H
#define INCLUDE_G35_MEO_PROGRAM_RUNNER_H

#include <MEOLightProgram.h>

// ProgramRunner manages a collection of LightPrograms.
//
// It gives the current program a slice of time to run, decides when it's
// time to switch to the next program, and asks the program_creator callback
// to give it the next program when it's time. In Arduino terms, it's what
// you want to call in your loop() method.
//
// switch_program() is public because the application might sometimes want
// to change programs more frequently, for example if you've implemented
// a remote control receiver.

class MEOProgramRunner {
 public:
 MEOProgramRunner(MEOLightProgram* (*program_creator)(uint8_t program_index, uint8_t pattern),
	       uint8_t program_count, unsigned long program_duration_seconds)
   : program_count_(program_count),
    program_duration_seconds_(program_duration_seconds),
    program_index_(-1),
	pattern_(0),
    next_switch_millis_(0),
    program_creator_(program_creator),
    program_(NULL) {}

  void loop() {
    unsigned long now = millis();
    if (now >= next_switch_millis_) {
      switch_program(true); //hopefully this never runs, as timer is really long
    }
    if (now >= next_do_millis_) {
      next_do_millis_ = now + program_->Do();
    }
  }

 void switch_program(bool up) {
    unsigned long now = millis();
    next_switch_millis_ = now + program_duration_seconds_ * 1000;
    next_do_millis_ = now;

	Serial.print("ProgramRunner: ");
	Serial.print("    ProgramIndex_: ");
	Serial.print(program_index_);
	Serial.print("    (program_count_):");
	Serial.print(program_count_);
	Serial.print("    Pattern_: ");
	Serial.println(pattern_);

	if (up)
	{
		if (++program_index_ == program_count_) {
			program_index_ = 0;
		}
	} else {
		if (program_index_ == 0)
		{
			program_index_ = program_count_ - 1;
		} else {
			--program_index_;
		}
	}

    if (program_ != NULL) {
      delete program_;
    }
    program_ = program_creator_(program_index_, pattern_);
  }

 void switch_pattern(bool up) {
	Serial.print("ProgramRunnerSP: ");
	Serial.print("    ProgramIndex_: ");
	Serial.print(program_index_);
	Serial.print("    (program_count_):");
	Serial.print(program_count_);
	Serial.print("    Pattern_: ");
	Serial.println(pattern_);

	if (up)
	{
		if (++pattern_ == 31) {
			pattern_ = 0;
		}
	} else {
		if (pattern_ == 0)
		{
			pattern_ = pattern_ - 1;
		} else {
			--pattern_;
		}
	}

	if (program_ != NULL) {
      delete program_;
    }
    program_ = program_creator_(program_index_, pattern_);
  }

 private:
  uint8_t program_count_;
  unsigned long program_duration_seconds_;
  uint8_t program_index_;
  uint8_t pattern_;
  unsigned long next_switch_millis_;
  unsigned long next_do_millis_;
  MEOLightProgram* (*program_creator_)(uint8_t program_index, uint8_t pattern);
  MEOLightProgram* program_;
};

#endif  // INCLUDE_G35_PROGRAM_RUNNER_H