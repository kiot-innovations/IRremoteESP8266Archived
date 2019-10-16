// Copyright 2009 Ken Shirriff
// Copyright 2017 David Conran

#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <algorithm>
#include "IRrecv.h"
#include "IRsend.h"
#include "IRutils.h"

//                           N   N  EEEEE   CCCC
//                           NN  N  E      C
//                           N N N  EEE    C
//                           N  NN  E      C
//                           N   N  EEEEE   CCCC

// NEC originally added from https://github.com/shirriff/Arduino-IRremote/

// Constants
// Ref:
//  http://www.sbprojects.com/knowledge/ir/nec.php
#define NEC_TICK                     560U
#define NEC_HDR_MARK_TICKS            16U
#define NEC_HDR_MARK                 (NEC_HDR_MARK_TICKS * NEC_TICK)
#define NEC_HDR_SPACE_TICKS            8U
#define NEC_HDR_SPACE                (NEC_HDR_SPACE_TICKS * NEC_TICK)
#define NEC_BIT_MARK_TICKS             1U
#define NEC_BIT_MARK                 (NEC_BIT_MARK_TICKS * NEC_TICK)
#define NEC_ONE_SPACE_TICKS            3U
#define NEC_ONE_SPACE                (NEC_TICK * NEC_ONE_SPACE_TICKS)
#define NEC_ZERO_SPACE_TICKS           1U
#define NEC_ZERO_SPACE               (NEC_TICK * NEC_ZERO_SPACE_TICKS)
#define NEC_RPT_SPACE_TICKS            4U
#define NEC_RPT_SPACE                (NEC_RPT_SPACE_TICKS * NEC_TICK)
#define NEC_RPT_LENGTH                 4U
#define NEC_MIN_COMMAND_LENGTH_TICKS 193U
#define NEC_MIN_COMMAND_LENGTH       (NEC_MIN_COMMAND_LENGTH_TICKS * NEC_TICK)
#define NEC_MIN_GAP (NEC_MIN_COMMAND_LENGTH - \
    (NEC_HDR_MARK + NEC_HDR_SPACE + NEC_BITS * (NEC_BIT_MARK + NEC_ONE_SPACE) \
     + NEC_BIT_MARK))
#define NEC_MIN_GAP_TICKS (NEC_MIN_COMMAND_LENGTH_TICKS - \
    (NEC_HDR_MARK_TICKS + NEC_HDR_SPACE_TICKS + \
     NEC_BITS * (NEC_BIT_MARK_TICKS + NEC_ONE_SPACE_TICKS) + \
     NEC_BIT_MARK_TICKS))

#if SEND_NECSHORT
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
// TEMPORARY - Right now we are not using repeat. Its just dummy. 
void IRsend::sendNECShort(uint64_t data, uint16_t nbits, uint16_t repeat) {
  sendGeneric(NEC_HDR_MARK, NEC_HDR_SPACE,
              NEC_BIT_MARK, NEC_ONE_SPACE,
              NEC_BIT_MARK, NEC_ZERO_SPACE,
              NEC_BIT_MARK, NEC_MIN_GAP, NEC_MIN_COMMAND_LENGTH,
              data, nbits, 38, true, 0,  // Repeats are handled later.
              33);
  // Optional command repeat sequence.
 /*  if (repeat)
    sendGeneric(NEC_HDR_MARK, NEC_RPT_SPACE,
                0, 0, 0, 0,  // No actual data sent.
                NEC_BIT_MARK, NEC_MIN_GAP, NEC_MIN_COMMAND_LENGTH,
                0, 0,  // No data to be sent.
                38, true, repeat - 1,  // We've already sent a one message.
                33); */
}

#endif


