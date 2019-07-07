/*
  defaults.h - defaults settings configuration file
  Part of Grbl

  Copyright (c) 2012-2016 Sungeun K. Jeon for Gnea Research LLC

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

/* The defaults.h file serves as a central default settings selector for different machine
   types, from DIY CNC mills to CNC conversions of off-the-shelf machines. The settings
   files listed here are supplied by users, so your results may vary. However, this should
   give you a good starting point as you get to know your machine and tweak the settings for
   your nefarious needs.
   NOTE: Ensure one and only one of these DEFAULTS_XXX values is defined in config.h */

#ifndef defaults_h

#ifdef DEFAULTS_TB7_8
  // Grbl-tb7 settings for right and left steppers set to 1/8th microstepping.
  #define DEFAULT_X_STEPS_PER_MM 16.0 // makes it so a move of 100mm would equal 1 stepper rotation
  #define DEFAULT_Y_STEPS_PER_MM 16.0 // makes it so a move of 100mm would equal 1 stepper rotation
  #define DEFAULT_Z_STEPS_PER_MM 16.0 // makes it so a move of 100mm would equal 1 stepper rotation
  #define DEFAULT_X_MAX_RATE 84000.0 // results in max of 840 rpm
  #define DEFAULT_Y_MAX_RATE 84000.0 // results in max of 840 rpm
  #define DEFAULT_Z_MAX_RATE 84000.0 // results in max of 840 rpm
  #define DEFAULT_X_ACCELERATION (980.0*60*60) // = 980 mm/sec^2
  #define DEFAULT_Y_ACCELERATION (980.0*60*60) // = 980 mm/sec^2
  #define DEFAULT_Z_ACCELERATION (980.0*60*60) // = 980 mm/sec^2
  #define DEFAULT_X_MAX_TRAVEL 7000.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Y_MAX_TRAVEL 7000.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Z_MAX_TRAVEL 7000.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_SPINDLE_RPM_MAX 1000.0 // rpm
  #define DEFAULT_SPINDLE_RPM_MIN 0.0 // rpm
  #define DEFAULT_STEP_PULSE_MICROSECONDS 10
  #define DEFAULT_STEPPING_INVERT_MASK 0
  #define DEFAULT_DIRECTION_INVERT_MASK 0
  #define DEFAULT_STEPPER_IDLE_LOCK_TIME 25 // msec (0-254, 255 keeps steppers enabled)
  #define DEFAULT_STATUS_REPORT_MASK 1 // MPos enabled
  #define DEFAULT_JUNCTION_DEVIATION 0.01 // mm
  #define DEFAULT_ARC_TOLERANCE 0.002 // mm
  #define DEFAULT_REPORT_INCHES 0 // false
  #define DEFAULT_INVERT_ST_ENABLE 0 // false
  #define DEFAULT_INVERT_LIMIT_PINS 0 // false
  #define DEFAULT_SOFT_LIMIT_ENABLE 0 // false
  #define DEFAULT_HARD_LIMIT_ENABLE 0  // false
  #define DEFAULT_INVERT_PROBE_PIN 0 // false
  #define DEFAULT_LASER_MODE 0 // false
  #define DEFAULT_HOMING_ENABLE 0  // false
  #define DEFAULT_HOMING_DIR_MASK 0 // move positive dir
  #define DEFAULT_HOMING_FEED_RATE 25.0 // mm/min
  #define DEFAULT_HOMING_SEEK_RATE 500.0 // mm/min
  #define DEFAULT_HOMING_DEBOUNCE_DELAY 250 // msec (0-65k)
  #define DEFAULT_HOMING_PULLOFF 1.0 // mm
#endif

#ifdef DEFAULTS_TB7_16
  // Grbl generic default settings. Should work across different machines.
  #define DEFAULT_X_STEPS_PER_MM 32.0 // makes it so a move of 100mm would equal 1 stepper rotation
  #define DEFAULT_Y_STEPS_PER_MM 32.0 // makes it so a move of 100mm would equal 1 stepper rotation
  #define DEFAULT_Z_STEPS_PER_MM 32.0 // makes it so a move of 100mm would equal 1 stepper rotation
  #define DEFAULT_X_MAX_RATE 63000.0 // results in max of 630 rpm
  #define DEFAULT_Y_MAX_RATE 63000.0 // results in max of 630 rpm
  #define DEFAULT_Z_MAX_RATE 63000.0 // results in max of 630 rpm
  #define DEFAULT_X_ACCELERATION (980.0*60*60) // = 980 mm/sec^2
  #define DEFAULT_Y_ACCELERATION (980.0*60*60) // = 980 mm/sec^2
  #define DEFAULT_Z_ACCELERATION (980.0*60*60) // = 980 mm/sec^2
  #define DEFAULT_X_MAX_TRAVEL 7000.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Y_MAX_TRAVEL 7000.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Z_MAX_TRAVEL 7000.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_SPINDLE_RPM_MAX 1000.0 // rpm
  #define DEFAULT_SPINDLE_RPM_MIN 0.0 // rpm
  #define DEFAULT_STEP_PULSE_MICROSECONDS 10
  #define DEFAULT_STEPPING_INVERT_MASK 0
  #define DEFAULT_DIRECTION_INVERT_MASK 0
  #define DEFAULT_STEPPER_IDLE_LOCK_TIME 25 // msec (0-254, 255 keeps steppers enabled)
  #define DEFAULT_STATUS_REPORT_MASK 1 // MPos enabled
  #define DEFAULT_JUNCTION_DEVIATION 0.01 // mm
  #define DEFAULT_ARC_TOLERANCE 0.002 // mm
  #define DEFAULT_REPORT_INCHES 0 // false
  #define DEFAULT_INVERT_ST_ENABLE 0 // false
  #define DEFAULT_INVERT_LIMIT_PINS 0 // false
  #define DEFAULT_SOFT_LIMIT_ENABLE 0 // false
  #define DEFAULT_HARD_LIMIT_ENABLE 0  // false
  #define DEFAULT_INVERT_PROBE_PIN 0 // false
  #define DEFAULT_LASER_MODE 0 // false
  #define DEFAULT_HOMING_ENABLE 0  // false
  #define DEFAULT_HOMING_DIR_MASK 0 // move positive dir
  #define DEFAULT_HOMING_FEED_RATE 25.0 // mm/min
  #define DEFAULT_HOMING_SEEK_RATE 500.0 // mm/min
  #define DEFAULT_HOMING_DEBOUNCE_DELAY 250 // msec (0-65k)
  #define DEFAULT_HOMING_PULLOFF 1.0 // mm
#endif

#endif
