//////////////////////////////////////////////////////////////////////////////
// Arduino and AVR IO to register static mapping.
//
// Copyright (C) 2015 Pasquale Cocchini <pasquale.cocchini@ieee.org>
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
// 
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//////////////////////////////////////////////////////////////////////////////

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
