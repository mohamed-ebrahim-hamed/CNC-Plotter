/*
  cpu_map_atmega328p.h - CPU and pin mapping configuration file
  Part of Grbl

  Copyright (c) 2012-2015 Sungeun K. Jeon

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

/* Grbl officially supports the Arduino Uno, but the other supplied pin mappings are
   supplied by users, so your results may vary. This cpu_map file serves as a central
   pin mapping settings file for AVR 328p used on the Arduino Uno.  */

// Virtual Ports for 28BYJ change
uint8_t VPORTB;
uint8_t VPORTC;
uint8_t VPORTD;
uint8_t VDDRB;
uint8_t VDDRC;
uint8_t VDDRD;
   
#ifdef GRBL_PLATFORM
#error "cpu_map already defined: GRBL_PLATFORM=" GRBL_PLATFORM
#endif


#define GRBL_PLATFORM "Atmega328p"

// Define serial port pins and interrupt vectors.
#define SERIAL_RX     USART_RX_vect
#define SERIAL_UDRE   USART_UDRE_vect

// Define step pulse output pins. NOTE: All step bit pins must be on the same port.
#define STEP_DDR        VDDRD
#define STEP_PORT       VPORTD
#define X_STEP_BIT      0//2  // Uno Digital Pin 2
#define Y_STEP_BIT      0//3  // Uno Digital Pin 3
#define Z_STEP_BIT      0//4  // Uno Digital Pin 4
#define STEP_MASK       ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)) // All step bits

// Define step direction output pins. NOTE: All direction pins must be on the same port.
#define DIRECTION_DDR     VDDRD
#define DIRECTION_PORT    VPORTD
#define X_DIRECTION_BIT   6//5  // Uno Digital Pin 5
#define Y_DIRECTION_BIT   7//6  // Uno Digital Pin 6
#define Z_DIRECTION_BIT   0//7  // Uno Digital Pin 7
#define DIRECTION_MASK    ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)) // All direction bits

// Define stepper driver enable/disable output pin.
#define STEPPERS_DISABLE_DDR    VDDRB
#define STEPPERS_DISABLE_PORT   VPORTB
#define STEPPERS_DISABLE_BIT    5//0  // Uno Digital Pin 8
#define STEPPERS_DISABLE_MASK   (1<<STEPPERS_DISABLE_BIT)

// Define homing/hard limit switch input pins and limit interrupt vectors. 
// NOTE: All limit bit pins must be on the same port, but not on a port with other input pins (CONTROL).
#define LIMIT_DDR        VDDRB
#define LIMIT_PIN        PINB
#define LIMIT_PORT       VPORTB
#define X_LIMIT_BIT      1  // Uno Digital Pin 9
#define Y_LIMIT_BIT      2  // Uno Digital Pin 10
#ifdef VARIABLE_SPINDLE // Z Limit pin and spindle enabled swapped to access hardware PWM on Pin 11.  
  #define Z_LIMIT_BIT	   4 // Uno Digital Pin 12
#else
  #define Z_LIMIT_BIT    3  // Uno Digital Pin 11
#endif
#define LIMIT_MASK       ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)) // All limit bits
#define LIMIT_INT        PCIE0  // Pin change interrupt enable pin
#define LIMIT_INT_vect   PCINT0_vect 
#define LIMIT_PCMSK      PCMSK0 // Pin change interrupt register

// Define spindle enable and spindle direction output pins.
#define SPINDLE_ENABLE_DDR    VDDRB
#define SPINDLE_ENABLE_PORT   VPORTB
// Z Limit pin and spindle PWM/enable pin swapped to access hardware PWM on Pin 11.
#ifdef VARIABLE_SPINDLE 
  #ifdef USE_SPINDLE_DIR_AS_ENABLE_PIN
    // If enabled, spindle direction pin now used as spindle enable, while PWM remains on D11.
    #define SPINDLE_ENABLE_BIT    5  // Uno Digital Pin 13 (NOTE: D13 can't be pulled-high input due to LED.)
  #else
    #define SPINDLE_ENABLE_BIT    3  // Uno Digital Pin 11
  #endif
#else
  #define SPINDLE_ENABLE_BIT    4  // Uno Digital Pin 12
#endif
#ifndef USE_SPINDLE_DIR_AS_ENABLE_PIN
  #define SPINDLE_DIRECTION_DDR   VDDRB
  #define SPINDLE_DIRECTION_PORT  VPORTB
  #define SPINDLE_DIRECTION_BIT   5  // Uno Digital Pin 13 (NOTE: D13 can't be pulled-high input due to LED.)
#endif
  
// Define flood and mist coolant enable output pins.
// NOTE: Uno analog pins 4 and 5 are reserved for an i2c interface, and may be installed at
// a later date if flash and memory space allows.
#define COOLANT_FLOOD_DDR   VDDRC
#define COOLANT_FLOOD_PORT  VPORTC
#define COOLANT_FLOOD_BIT   3  // Uno Analog Pin 3
#ifdef ENABLE_M7 // Mist coolant disabled by default. See config.h to enable/disable.
  #define COOLANT_MIST_DDR   VDDRC
  #define COOLANT_MIST_PORT  VPORTC
  #define COOLANT_MIST_BIT   4 // Uno Analog Pin 4
#endif  

// Define user-control controls (cycle start, reset, feed hold) input pins.
// NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
#define CONTROL_DDR       VDDRC
#define CONTROL_PIN       PINC
#define CONTROL_PORT      VPORTC
#define RESET_BIT         6//0  // Uno Analog Pin 0
#define FEED_HOLD_BIT     6//1  // Uno Analog Pin 1
#define CYCLE_START_BIT   6//2  // Uno Analog Pin 2
#define SAFETY_DOOR_BIT   6//1  // Uno Analog Pin 1 NOTE: Safety door is shared with feed hold. Enabled by config define.
#define CONTROL_INT       PCIE1  // Pin change interrupt enable pin
#define CONTROL_INT_vect  PCINT1_vect
#define CONTROL_PCMSK     PCMSK1 // Pin change interrupt register
#define CONTROL_MASK ((1<<RESET_BIT)|(1<<FEED_HOLD_BIT)|(1<<CYCLE_START_BIT)|(1<<SAFETY_DOOR_BIT))
#define CONTROL_INVERT_MASK CONTROL_MASK // May be re-defined to only invert certain control pins.
  
// Define probe switch input pin.
#define PROBE_DDR       VDDRC
#define PROBE_PIN       PINC
#define PROBE_PORT      VPORTC
#define PROBE_BIT       5  // Uno Analog Pin 5
#define PROBE_MASK      (1<<PROBE_BIT)

// Start of PWM & Stepper Enabled Spindle
#ifdef VARIABLE_SPINDLE
  // Advanced Configuration Below You should not need to touch these variables
  #define PWM_MAX_VALUE    255.0
  #define TCCRA_REGISTER	 TCCR2A
  #define TCCRB_REGISTER	 TCCR2B
  #define OCR_REGISTER     OCR2A
  
  #define COMB_BIT	     COM2A1
  #define WAVE0_REGISTER	 WGM20
  #define WAVE1_REGISTER	 WGM21
  #define WAVE2_REGISTER	 WGM22
  #define WAVE3_REGISTER	 WGM23
      
  // NOTE: On the 328p, these must be the same as the SPINDLE_ENABLE settings.
  #define SPINDLE_PWM_DDR	  VDDRB
  #define SPINDLE_PWM_PORT  VPORTB
  #define SPINDLE_PWM_BIT	  3    // Uno Digital Pin 11
#endif // End of VARIABLE_SPINDLE
