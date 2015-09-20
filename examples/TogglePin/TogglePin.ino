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
// This example shows the basic usage of the register maps.
// Here we toggle digital pin 4 directly using the relevant AVR registers.
//////////////////////////////////////////////////////////////////////////////

#include "AvrMap.h"

void setup ()
{
  // Set Arduino digital pin 4 as output.
  DDRMap(4) |= 1<<BITMap(4);
}

void loop ()
{
  // Toggle the pin every second.
  PORTMap(4) ^= 1<<BITMap(4);
  delay(1000);
}
