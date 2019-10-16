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
// TEMPORARY - Right now we are not using repeat. Its just dummy. 
void IRsend::sendRCA(uint64_t data, uint16_t nbits, uint16_t repeat) {
  enableIROut(RCA_FREQ);
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

#endif
