// Copyright 2009 Ken Shirriff
// Copyright 2017 David Conran

#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <algorithm>
#include "IRrecv.h"
#include "IRsend.h"
#include "IRutils.h"

#define XMP1_FREQ 38
#define XMP1_BIT_MARK 185
#define XMP_ZERO_SPACE 2100
#define XMP_ONE_SPACE 13157
#define XMP_FIXED_PULSE 765
#define XMP_SPACE_MULTI_FACTOR 5.2

// NEC originally added from https://github.com/shirriff/Arduino-IRremote/

// Constants
// Ref:
//  http://www.sbprojects.com/knowledge/ir/nec.php


#if SEND_XMP1
// Send a raw NEC(Renesas) formatted message.
//
// Args:
//   data:   The message to be sent.
//   nbits:  The number of bits of the message to be sent. Typically NEC_BITS.
//   repeat: The number of times the command is to be repeated.
//
// Status: STABLE / Known working.
//
// Ref:
//  http://www.sbprojects.com/knowledge/ir/nec.php
void IRsend::sendXMP1(uint64_t data, uint16_t nbits) {
  enableIROut(38);
    int parts = nbits/4;
    int i =0;
    while(i<parts){
      if( i % 8 == 0 && i != 0 ){
          mark(XMP1_BIT_MARK);
          space(XMP_ONE_SPACE);
      }
      mark(XMP1_BIT_MARK);
      space(round(((float) ((data >> (((parts - i) - 1) * 4)) & 15)) * XMP_SPACE_MULTI_FACTOR) + XMP_FIXED_PULSE);  // Might not be accurate. Will have to check
      i++;
    }
    mark(XMP1_BIT_MARK);
    ledOff();

}

// Calculate the raw NEC data based on address and command.
// Args:
//   address: An address value.
//   command: An 8-bit command value.
// Returns:
//   A raw 32-bit NEC message.
//
// Status: BETA / Expected to work.
//
// Ref:
//  http://www.sbprojects.com/knowledge/ir/nec.php
/* uint32_t IRsend::encodeNEC(uint16_t address, uint16_t command) {
  command &= 0xFF;  // We only want the least significant byte of command.
  // sendNEC() sends MSB first, but protocol says this is LSB first.
  command = reverseBits(command, 8);
  command = (command <<  8) + (command ^ 0xFF);  // Calculate the new command.
  if (address > 0xFF) {  // Is it Extended NEC?
    address = reverseBits(address, 16);
    return ((address << 16) + command);  // Extended.
  } else {
    address = reverseBits(address, 8);
    return (address << 24) + ((address ^ 0xFF) << 16) + command;  // Normal.
  }
} */
#endif


