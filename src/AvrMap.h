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

#ifndef AvrMap_h
#define AvrMap_h

#include <avr/io.h>

typedef volatile unsigned char reg8_t;

// Arduino pin maps match digital pins starting at 0. Analog pins are appended
// to the sequence so pin numbering will be relative to the last digital pin. 
// For instance if the last digital pin is 13 analog pin 0 is pin 14, analog
// pin 1 is 15 and so on and so forth.
// AVR pin maps are for the physical pin location on the chip.
// Note on SPI Slave Select (SS): if specifically defined in the MCU, SS must 
// be set as output in master mode otherwise SPI will not function as SS will
// by default be in input mode.
#define NOREG SREG
#define NOPIN 8

//////////////////////////////////////////////////////////////////////////////
// Arduino Uno, Nano, Pro, etc.
//////////////////////////////////////////////////////////////////////////////
#if defined __AVR_ATmega328P__ || \
    defined __AVR_ATmega328__  || \
    defined __AVR_ATmega168__

//                  +-\/-+
//      RESET PC6  1|    |28  PC5 (AI 5) SCL
//   RX (D 0) PD0  2|    |27  PC4 (AI 4) SDA
//   TX (D 1) PD1  3|    |26  PC3 (AI 3)
//      (D 2) PD2  4|    |25  PC2 (AI 2)
//      (D 3) PD3  5|    |24  PC1 (AI 1)
//      (D 4) PD4  6|    |23  PC0 (AI 0)
//            VCC  7|    |22  GND
//            GND  8|    |21  AREF
//            PB6  9|    |20  AVCC
//            PB7 10|    |19  PB5 (D 13) SCK
//      (D 5) PD5 11|    |18  PB4 (D 12) MISO
//      (D 6) PD6 12|    |17  PB3 (D 11) MOSI
//      (D 7) PD7 13|    |16  PB2 (D 10) SS
//      (D 8) PB0 14|    |15  PB1 (D  9)
//                  +----+

#define SPI_PORT PORTB
#define SPI_DDR  DDRB
#define SPI_PIN  PINB
#define SPI_SCK  5
#define SPI_MISO 4
#define SPI_MOSI 3
#define SPI_SS   2

#ifdef AVR_PINOUT

#define PORTMap(P) \
((P) >=  2 && (P) <=  6 || (P) >= 11 && (P) <= 13 ? PORTD : \
 (P) >=  9 && (P) <= 10 || (P) >= 14 && (P) <= 19 ? PORTB : \
 (P) >= 23 && (P) <= 28 ||              (P) ==  1 ? PORTC : NOREG)

#define DDRMap(P) \
((P) >=  2 && (P) <=  6 || (P) >= 11 && (P) <= 13 ? DDRD : \
 (P) >=  9 && (P) <= 10 || (P) >= 14 && (P) <= 19 ? DDRB : \
 (P) >= 23 && (P) <= 28 ||              (P) ==  1 ? DDRC : NOREG)

#define PINMap(P) \
((P) >=  2 && (P) <=  6 || (P) >= 11 && (P) <= 13 ? PIND : \
 (P) >=  9 && (P) <= 10 || (P) >= 14 && (P) <= 19 ? PINB : \
 (P) >= 23 && (P) <= 28 ||              (P) ==  1 ? PINC : NOREG)

#define BITMap(P) \
((P) >=  2 && (P) <=  6 ? (P)- 2 : \
 (P) >= 11 && (P) <= 13 ? (P)- 6 : \
 (P) >=  9 && (P) <= 10 ? (P)- 3 : \
 (P) >= 14 && (P) <= 19 ? (P)-14 : \
 (P) >= 23 && (P) <= 28 ? (P)-23 : \
              (P) ==  1 ?      6 : NOPIN)

#else // Arduino pinout.

#define PORTMap(P) \
((P) >=  0 && (P) <=  7 ? PORTD : \
 (P) >=  8 && (P) <= 13 ? PORTB : \
 (P) >= 14 && (P) <= 19 ? PORTC : NOREG)

#define DDRMap(P) \
((P) >=  0 && (P) <=  7 ?  DDRD : \
 (P) >=  8 && (P) <= 13 ?  DDRB : \
 (P) >= 14 && (P) <= 19 ?  DDRC : NOREG)

#define PINMap(P) \
((P) >=  0 && (P) <=  7 ?  PIND : \
 (P) >=  8 && (P) <= 13 ?  PINB : \
 (P) >= 14 && (P) <= 19 ?  PINC : NOREG)

#define BITMap(P) \
((P) >=  0 && (P) <=  7 ? (P)    : \
 (P) >=  8 && (P) <= 13 ? (P)- 8 : \
 (P) >= 14 && (P) <= 19 ? (P)-14 : NOPIN)

#endif // AVR_PINOUT

//////////////////////////////////////////////////////////////////////////////
// Arduino Leonardo.
//////////////////////////////////////////////////////////////////////////////
#elif defined __AVR_ATmega16U4__ || \
      defined __AVR_ATmega32U4__

#define SPI_PORT PORTB
#define SPI_DDR  DDRB
#define SPI_PIN  PINB
#define SPI_SCK  1
#define SPI_MISO 3
#define SPI_MOSI 2
#define SPI_SS   0

#ifdef AVR_PINOUT
#error "AVR pin mapping not implemented"
#else // Arduino pinout.

#define PORTMap(P) \
((P) >=  0 && (P) <=  4 || \
 (P) ==  6 || (P) == 12 ? PORTD : \
 (P) >=  8 || (P) <= 11 ? PORTB : \
 (P) ==  5 || (P) == 13 ? PORTC : \
              (P) ==  7 ? PORTE : NOREG)

#define DDRMap(P) \
((P) >=  0 && (P) <=  4 || \
 (P) ==  6 || (P) == 12 ? DDRD : \
 (P) >=  8 || (P) <= 11 ? DDRB : \
 (P) ==  5 || (P) == 13 ? DDRC : \
              (P) ==  7 ? DDRE : NOREG)

#define PINMap(P) \
((P) >=  0 && (P) <=  4 || \
 (P) ==  6 || (P) == 12 ? PIND : \
 (P) >=  8 || (P) <= 11 ? PINB : \
 (P) ==  5 || (P) == 13 ? PINC : \
              (P) ==  7 ? PINE : NOREG)

#define BITMap(P) \
((P) >=  0 && (P) <=  1 ? (P)+2 : \
 (P) >=  2 && (P) <=  3 ? 3-(P) : \
 (P) ==  4 ? 4 : \
 (P) >=  5 && (P) <=  6 ? (P)+1 : \
 (P) ==  7 ? 6 : \
 (P) >=  8 && (P) <= 11 ? (P)-4 : \
 (P) >= 12 && (P) <= 13 ? (P)-6 : NOPIN)

#endif // AVR_PINOUT

//////////////////////////////////////////////////////////////////////////////
// Arduino MEGA.
//////////////////////////////////////////////////////////////////////////////
#elif defined __AVR_ATmega1280__ || \
      defined __AVR_ATmega2560__

#define SPI_PORT PORTB
#define SPI_DDR  DDRB
#define SPI_PIN  PINB
#define SPI_SCK  1
#define SPI_MISO 3
#define SPI_MOSI 2
#define SPI_SS   0

#ifdef AVR_PINOUT
#error "AVR pin mapping not implemented"
#else // Arduino pinout.

#define PORTMap(P) \
((P) >= 22 && (P) <= 29 ? PORTA : \
 (P) >= 10 && (P) <= 13 || \
 (P) >= 50 && (P) <= 53 ? PORTB : \
 (P) >= 30 && (P) <= 37 ? PORTC : \
 (P) >= 18 && (P) <= 21 || \
              (P) == 38 ? PORTD : \
 (P) >=  0 && (P) <=  3 || \
              (P) ==  5 ? PORTE : \
 (P) >= 54 && (P) <= 61 ? PORTF : \
 (P) >= 39 && (P) <= 41 || \
              (P) ==  4 ? PORTG : \
 (P) >=  6 && (P) <=  9 || \
 (P) >= 16 && (P) <= 17 ? PORTH : \
 (P) >= 14 && (P) <= 15 ? PORTJ : \
 (P) >= 62 && (P) <= 69 ? PORTK : \
 (P) >= 42 && (P) <= 49 ? PORTL : NOREG)

#define DDRMap(P) \
((P) >= 22 && (P) <= 29 ? DDRA : \
 (P) >= 10 && (P) <= 13 || \
 (P) >= 50 && (P) <= 53 ? DDRB : \
 (P) >= 30 && (P) <= 37 ? DDRC : \
 (P) >= 18 && (P) <= 21 || \
              (P) == 38 ? DDRD : \
 (P) >=  0 && (P) <=  3 || \
              (P) ==  5 ? DDRE : \
 (P) >= 54 && (P) <= 61 ? DDRF : \
 (P) >= 39 && (P) <= 41 || \
              (P) ==  4 ? DDRG : \
 (P) >=  6 && (P) <=  9 || \
 (P) >= 16 && (P) <= 17 ? DDRH : \
 (P) >= 14 && (P) <= 15 ? DDRJ : \
 (P) >= 62 && (P) <= 69 ? DDRK : \
 (P) >= 42 && (P) <= 49 ? DDRL : NOREG)

#define PINMap(P) \
((P) >= 22 && (P) <= 29 ? PINA : \
 (P) >= 10 && (P) <= 13 || \
 (P) >= 50 && (P) <= 53 ? PINB : \
 (P) >= 30 && (P) <= 37 ? PINC : \
 (P) >= 18 && (P) <= 21 || \
              (P) == 38 ? PIND : \
 (P) >=  0 && (P) <=  3 || \
              (P) ==  5 ? PINE : \
 (P) >= 54 && (P) <= 61 ? PINF : \
 (P) >= 39 && (P) <= 41 || \
              (P) ==  4 ? PING : \
 (P) >=  6 && (P) <=  9 || \
 (P) >= 16 && (P) <= 17 ? PINH : \
 (P) >= 14 && (P) <= 15 ? PINJ : \
 (P) >= 62 && (P) <= 69 ? PINK : \
 (P) >= 42 && (P) <= 49 ? PINL : NOREG)

#define BITMap(P) \
((P) >=  0 && (P) <=  1 ?    (P) : \
 (P) ==  2              ?      4 : \
 (P) >=  3 && (P) <=  4 ?      5 : \
 (P) >=  5 && (P) <=  6 ?      3 : \
 (P) >=  7 && (P) <=  9 ? (P)- 3 : \
 (P) >= 10 && (P) <= 13 ? (P)- 6 : \
 (P) >= 14 && (P) <= 15 ? 15-(P) : \
 (P) >= 16 && (P) <= 17 ? 17-(P) : \
 (P) >= 18 && (P) <= 21 ? 21-(P) : \
 (P) >= 22 && (P) <= 29 ? (P)-22 : \
 (P) >= 30 && (P) <= 37 ? 37-(P) : \
 (P) == 38              ?      7 : \
 (P) >= 39 && (P) <= 41 ? 41-(P) : \
 (P) >= 42 && (P) <= 49 ? 49-(P) : \
 (P) >= 50 && (P) <= 53 ? 53-(P) : \
 (P) >= 54 && (P) <= 61 ? (P)-54 : \
 (P) >= 62 && (P) <= 69 ? (P)-62 : NOPIN)

#endif // AVR_PINOUT

//////////////////////////////////////////////////////////////////////////////
// ATtinyX5: chip pinout.
//////////////////////////////////////////////////////////////////////////////
#elif defined __AVR_ATtiny25__ || \
      defined __AVR_ATtiny45__ || \
      defined __AVR_ATtiny85__

//                   +-\/-+
//         RST PB5  1|o   |8  VCC  VCC
//             PB3  2|    |7  PB2  SCK USCK SCL
//             PB4  3|    |6  PB1 MISO   DO
//             GND  4|    |5  PB0 MOSI   DI SDA
//                   +----+

#define SPI_PORT PORTB
#define SPI_DDR   DDRB
#define SPI_PIN   PINB
// Note that the tiny has universal serial interface and the MISO/MOSI pins
// in the pinout refer to the chip being programmed in slave mode. In our 
// mapping we mean using USI in SPI mode so we switch meaning where DO is 
// always an output and equivalent to MOSI in master mode and DI is MISO.
#define SPI_SCK  2
#define SPI_MOSI 1
#define SPI_MISO 0

#define PORTMap(P) \
((P) >= 1 && (P) <= 3 || (P) >= 5 && (P) <= 7 ? PORTB : NOREG)

#define DDRMap(P) \
((P) >= 1 && (P) <= 3 || (P) >= 5 && (P) <= 7 ?  DDRB : NOREG)

#define PINMap(P) \
((P) >= 1 && (P) <= 3 || (P) >= 5 && (P) <= 7 ?  PINB : NOREG)

#define BITMap(P) \
((P) == 1           ?       5 : \
 (P) >= 2 && (P) <= 3 ? (P)+1 : \
 (P) >= 5 && (P) <= 7 ? (P)-5 : NOPIN)

//////////////////////////////////////////////////////////////////////////////
// ATtinyX4: chip pinout.
//////////////////////////////////////////////////////////////////////////////
#elif defined __AVR_ATtiny24__ || \
      defined __AVR_ATtiny44__ || \
      defined __AVR_ATtiny84__

//                    +-\/-+
//              VCC  1|o   |14 GND
//              PB0  2|    |13 PA0 ADC0 AREF
//              PB1  3|    |12 PA1 ADC1 AIN0
//          RST PB3  4|    |11 PA2 ADC2 AIN1
//              PB2  5|    |10 PA3 ADC3 TO
//              PA7  6|    |9  PA4 ADC4 USCK  SCK SCL T1
// SDA MOSI  DI PA6  7|    |8  PA5 ADC5   DO MISO OC1B
//                    +----+

#define SPI_PORT PORTA
#define SPI_DDR   DDRA
#define SPI_PIN   PINA
// Note that the tiny has universal serial interface and the MISO/MOSI pins
// in the pinout refer to the chip being programmed in slave mode. In our 
// mapping we mean using USI in SPI mode so we switch meaning where DO is 
// always an output and equivalent to MOSI in master mode and DI is MISO.
#define SPI_SCK  4
#define SPI_MOSI 5
#define SPI_MISO 6

#define PORTMap(P) \
((P) >= 6 && (P) <= 13 ? PORTA : \
 (P) >= 2 && (P) <=  5 ? PORTB : NOREG)

#define DDRMap(P) \
((P) >= 6 && (P) <= 13 ? DDRA : \
 (P) >= 2 && (P) <=  5 ? DDRB : NOREG)

#define PINMap(P) \
((P) >= 6 && (P) <= 13 ? PINA : \
 (P) >= 2 && (P) <=  5 ? PINB : NOREG)

#define BITMap(P) \
((P) >= 2 && (P) <=  3 ?  (P)-2 : \
 (P) >= 4 && (P) <=  5 ?  7-(P) : \
 (P) >= 6 && (P) <= 13 ? 13-(P) : NOPIN)

#else // Unsupported MCU.
#error "Unsupported mcu mapping"
#endif // Unsupported MCU.

#endif // AvrMap_h
