//////////////////////////////////////////////////////////////////////////////
// SPI Library for Arduino, AVR 8 bit Microntrollers.
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

#ifndef Spi_h
#define Spi_h

#include "AvrMap.h"

// PC: SPI IO is statically defined for SCK, MISO, MOSI in all MCUs.
template <uint8_t CS_PIN>
struct Spi
{
  enum IO
  {
    SCK  = 1<<SPI_SCK,
    MISO = 1<<SPI_MISO,
    MOSI = 1<<SPI_MOSI,
    // SPI SS if defined in MCU, must be set as output in master mode.
    SS   = 1<<SPI_SS,
    // User defined chip select, can match SS in master mode.
    CS   = 1<<BITMap (CS_PIN)
  };

  // SPCR - SPI Control Register.
  //    7   6    5    4    3    2    1    0
  // SPIE SPE DORD MSTR CPOL CPHA SPR1 SPR0
  enum SPCR_REG
  {
    // Bit 7 - SPIE: SPI Interrupt Enable.
    SPIE_BV    = 1<<SPIE,
    // Bit 6 - SPE: SPI Enable.
    SPE_BV     = 1<<SPE,
    // Bit 5 - DORD: Data Order.
    // When the DORD bit is written to one, the LSB of the data word is 
    // transmitted first. When the DORD bit is written to zero, the MSB 
    // of the data word is transmitted first.
    LSB_FIRST  = 1<<DORD,
    MSB_FIRST  = 0<<DORD,
    // Bit 4 - MSTR: Master/Slave Select.
    MASTER     = 1<<MSTR,
    SLAVE      = 0<<MSTR,
    // Bit 3 - CPOL: Clock Polarity.
    // Bit 2 - CPHA: Clock Phase.
    CLK_MODE0  = (0<<CPOL) | (0<<CPHA),
    CLK_MODE1  = (0<<CPOL) | (1<<CPHA),
    CLK_MODE2  = (1<<CPOL) | (0<<CPHA),
    CLK_MODE3  = (1<<CPOL) | (1<<CPHA),
    // Bits 1, 0 - SPR1, SPR0: SPI Clock Rate Select 1 and 0.
    SCK_DIV4   = (0<<SPR1) | (0<<SPR0),
    SCK_DIV16  = (0<<SPR1) | (1<<SPR0),
    SCK_DIV64  = (1<<SPR1) | (0<<SPR0),
    SCK_DIV128 = (1<<SPR1) | (1<<SPR0),
  };

  // SPSR - SPI Status Register.
  // SPIF WCOL - - - - - SPI2X
  //    7    6 5 4 3 2 1     0
  enum SPSR_REG
  {
    // Bit 7 - SPIF: SPI Interrupt Flag.
    SPIF_BV  = 1<<SPIF,
    // Bit 6 - WCOL: Write Collision Flag.
    WCOL_BV  = 1<<WCOL,
    // Bit [5:1] - Reserved.
    // Bit 0 - SPI2X: Double SPI Speed Bit.
    SPI2X_BV = 1<<SPI2X
  };

  // SPDR - SPI Data Register.
  // The SPI Data Register is a read/write register used for data transfer
  // between the Register File and the SPI Shift Register. Writing to the
  // register initiates data transmission. Reading the register causes the
  // Shift Register Receive buffer to be read.

  void MasterInit ()
  {
    // Drive user defined CS high and set as output.
    PORTMap(CS_PIN) |= CS;
    DDRMap(CS_PIN) |= CS;
    // Set MOSI SCK, SS as output, MISO is input.
    SPI_DDR |= MOSI | SCK | SS;
    // Enable SPI in master mode, set clock rate fck/4.
    SPCR = SPE_BV | MASTER;
  }

  void SlaveInit ()
  {
    // Set MISO output, all others input.
    SPI_DDR |= MISO;
    // Enable SPI in slave mode.
    SPCR = SPE_BV | SLAVE;
  }

  void End ()
  {
    SPCR &= ~SPE_BV;
  }

  void SlaveRelease ()
  {
    PORTMap(CS_PIN) |= CS;
  }

  void SlaveSelect ()
  {
    PORTMap(CS_PIN) &= ~CS;
  }

  void Transmit (uint8_t data)
  {
    // Start transmission.
    SPDR = data;
    // Wait for transmission completion.
    while (!(SPSR & SPIF_BV));
  }

  uint8_t Transfer (uint8_t data)
  {
    // Start transmission.
    SPDR = data;
    // Wait for transmission completion.
    while (!(SPSR & SPIF_BV));
    // Return Data Register.
    return SPDR;
  }

  uint8_t Read (uint8_t reg)
  {
    uint8_t val;
    SlaveSelect();
    Transmit (reg);
    val = Transfer (0xFF);
    SlaveRelease();
    return val;
  }

  void Read (uint8_t reg, uint8_t *data, uint8_t size)
  {
    SlaveSelect();
    Transmit (reg);
    while (size--)
      *data++ = Transfer (0xFF);
    SlaveRelease();
  }

  void Write (uint8_t cmd)
  {
    SlaveSelect();
    Transmit (cmd);
    SlaveRelease();
  }

  void Write (uint8_t reg, uint8_t val)
  {
    SlaveSelect();
    Transmit (reg);
    Transmit (val);
    SlaveRelease();
  }

  void Write (uint8_t reg, const uint8_t *data, uint8_t size)
  {
    SlaveSelect();
    Transmit (reg);
    while (size--)
      Transmit (*data++);
    SlaveRelease();
  }
};
#endif // Spi_h
