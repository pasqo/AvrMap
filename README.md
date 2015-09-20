# AvrMap
*Arduino and AVR IO to register static mapping.*

Occasionally there may be situations where pin input and output operations are critical to the project and we are unable to use the standard arduino digitalWrite method as it is quite inefficient taking as much as 60 clock cycles to perform a single write operation.
The simplest solution is that of directly using AVR registers, but here we would lose Arduino compatibility and the portability across arduino boards that digitalWrite provides.

To solve the problem this library provides a set of preprocessor functions that statically map AVR IO registers to corresponding pins in 8bit AVR based arduino boards, as well as standalone AVRs. By simultaneously using physical pin numbers for the definition of a project connectivity and AVR registers for programming it is possible to write Arduino compatible and portable code with efficient IO operations.
Other registers other than IO will also be included as needed in the future for portability.

The preprocessor map functions can be used either directly or through an extra level of defines, for example, or with template programming for an elegant way of specifying the pinout of a project.

For instance, consider the following example:
```
//////////////////////////////////////////////////////////////////////////////
// This example shows how to use the register maps to statically define the
// pinout of a project using templates.
//////////////////////////////////////////////////////////////////////////////

#include "AvrMap.h"

// We want to design a project that toggles two leds connected to two
// arbitrary arduino pins using AVR register. The goal here is that of
// assigning the pins only at the end when we make an instance of our
// class, letting the compiler bind the registers at compile time.
template <uint8_t LEDA_PIN, uint8_t LEDB_PIN>
struct LedToggler
{
  // For better code readability we enumerate the bit values.
  enum Io
  {
    LEDA = 1<<BITMap(LEDA_PIN),
    LEDB = 1<<BITMap(LEDB_PIN)
  };

  // Set the pins as output.
  LedToggler ()
  {
    DDRMap(LEDA_PIN) |= LEDA;
    DDRMap(LEDB_PIN) |= LEDB;
  }

  void ToggleA ()
  {
    PORTMap(LEDA_PIN) ^= LEDA;
  }

  void ToggleB ()
  {
    PORTMap(LEDB_PIN) ^= LEDB;
  }
};

// Make an instance of the toggler class on pins 3 and 4.
// The pin assignment happens here and the compiler binds the corresponding
// registers in the PORT IO instructions in the class.
LedToggler<3, 4> toggler;

void setup () {}

void loop ()
{
  // Toggle the pins every other second.
  toggler.ToggleA();
  delay(1000);
  toggler.ToggleB();
  delay(1000);
}
```

##### Acknoledgements
This work was inspired by the [digitalWriteFast](https://code.google.com/p/digitalwritefast/) project which uses preprocessor functions to provide an AVR register based direct replacement for Arduino digital IO operations.
