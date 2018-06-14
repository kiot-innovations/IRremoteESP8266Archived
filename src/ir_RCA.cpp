// Copyright 2009 Ken Shirriff
// Copyright 2017 David Conran

#include <algorithm>
#include "IRrecv.h"
#include "IRsend.h"
#include "IRutils.h"

//              SSSS   AAA    MMM    SSSS  U   U  N   N   GGGG
//             S      A   A  M M M  S      U   U  NN  N  G
//              SSS   AAAAA  M M M   SSS   U   U  N N N  G  GG
//                 S  A   A  M   M      S  U   U  N  NN  G   G
//             SSSS   A   A  M   M  SSSS    UUU   N   N   GGG

// Samsung originally added from https://github.com/shirriff/Arduino-IRremote/

// Constants
// Ref:
//   http://elektrolab.wz.cz/katalog/samsung_protocol.pdf

// Updated By arihant daga
#define RCA_FREQ       57
#define RCA_HDR_MARK   4000
#define RCA_HDR_SPACE  4000
#define RCA_BIT_MARK   500
#define RCA_ZERO_SPACE 1000
#define RCA_ONE_SPACE  2000
#define TOPBIT 0x80000000



#if SEND_RCA
// Send a Samsung formatted message.
// Samsung has a separate message to indicate a repeat, like NEC does.
// TODO(crankyoldgit): Confirm that is actually how Samsung sends a repeat.
//                     The refdoc doesn't indicate it is true.
//
// Args:
//   data:   The message to be sent.
//   nbits:  The bit size of the message being sent. typically SAMSUNG_BITS.
//   repeat: The number of times the message is to be repeated.
//
// Status: BETA / Should be working.
//
// Ref: http://elektrolab.wz.cz/katalog/samsung_protocol.pdf
void IRsend::sendRCA(uint64_t data, uint16_t nbits) {
  enableIROut(57);
  mark(RCA_HDR_MARK);
  space(RCA_HDR_SPACE);
    for (int i = 0; i < nbits; i++) {
    if (data & TOPBIT) {
      mark(RCA_BIT_MARK);
      space(RCA_ONE_SPACE);
    } 
    else {
      mark(RCA_BIT_MARK);
      space(RCA_ZERO_SPACE);
    }
    data <<= 1;
  }
  mark(RCA_BIT_MARK);
  ledOff();
}

// Construct a raw Samsung message from the supplied customer(address) &
// command.
//
// Args:
//   customer: The customer code. (aka. Address)
//   command:  The command code.
// Returns:
//   A raw 32-bit Samsung message suitable for sendSAMSUNG().
//
// Status: BETA / Should be working.
/* 
uint32_t IRsend::encodeSAMSUNG(uint8_t customer, uint8_t command) {
  customer = reverseBits(customer, sizeof(customer) * 8);
  command = reverseBits(command, sizeof(command) * 8);
  return((command ^ 0xFF) | (command << 8) |
         (customer << 16) | (customer << 24));
} 
*/
#endif
