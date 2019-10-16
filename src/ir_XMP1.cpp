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
#define XMP_SPACE_MULTI_FACTOR 137.4 //5.2 *26.4

// NEC originally added from https://github.com/shirriff/Arduino-IRremote/

// Constants
// Ref:
//  http://www.sbprojects.com/knowledge/ir/nec.php


#if SEND_XMP1
// TEMPORARY - Right now we are not using repeat. Its just dummy. 
// Also this implementation is wrong. This doesnot fire the right code. 
// RECOMMENDED: DO NOT USE THIS
void IRsend::sendXMP1(uint64_t data, uint16_t nbits, uint16_t repeat) {
    enableIROut(38);
    int parts = nbits/4;
    int i =0;
    while(i<parts){
      if( i % 8 == 0 && i != 0 ){
          mark(XMP1_BIT_MARK);
          space(XMP_ONE_SPACE);
      }
      mark(XMP1_BIT_MARK);
      0x166f442a18060100
       Math.round(((float) ((j >> (((i - i2) - 1) * 4)) & 15)) * DATA_MULTI) + 29
      space(round(((float) ((data >> (((parts - i) - 1) * 4)) & 15)) * XMP_SPACE_MULTI_FACTOR) + XMP_FIXED_PULSE);  // Might not be accurate. Will have to check
      i++;
    }
    mark(XMP1_BIT_MARK);
    ledOff();

}

#endif


