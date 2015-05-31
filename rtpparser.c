#include "rtpparser.h"

#include <stdint.h>
#include <stdio.h>

#define MAXLINES    64

typedef struct {
    uint16_t length;
    uint16_t linenumber; /**< Y */
    uint16_t offset; /**< X */
} LineHeaderInfo;


LineHeaderInfo mLines[MAXLINES];
int            mActualLineCnt=0;



int decode_packet(char* pPacket, int packet_length, char* pOutputBuffer, int width, int height)
{
    unsigned int r_version, r_p, r_x, r_cc, r_m, r_pt,
    r_seq, r_ts;
    /* Tear apart the header in a byte- and bit field-order
    independent fashion. */
    r_version = (pPacket[0] >> 6) & 3;
    r_p = !!(pPacket[0] & 0x20);
    r_x = !!(pPacket[0] & 0x10);
    r_cc = pPacket[0] & 0xF;
    r_m = !!(pPacket[1] & 0x80);
    r_pt = pPacket[1] & 0x7F;
    r_seq = ntohs(*((short *) (pPacket + 2)));
    r_ts = ntohl(*((long *) (pPacket + 4)));

    if (
           r_version == 2 && /* Version ID correct */
           r_pt >= 96 &&
           r_pt <= 128 &&
           /* Padding, if present, is plausible */
           (!r_p || (pPacket[packet_length - 1] < (packet_length - (12 + 4 * r_cc))))
           )
    {
       char *payload;
       int lex, paylen;

       /* Length of fixed header extension, if any */
       lex = r_x ? (ntohs(*((short *) (pPacket + 2 + 12 + 4 * r_cc))) + 1) * 4 : 0;
       payload = pPacket + (12 + 4 * r_cc) + lex; /* Start of payload */
       paylen = packet_length - ((12 + 4 * r_cc) + /* Length of payload */
       lex + (r_p ? pPacket[packet_length - 1] : 0));

       /* payload header rfc4175 */
       uint32_t seq =
               ((uint32_t) ntohs(*((short *) (payload)))) << 16 |
               ((uint32_t) r_seq);

       printf("%du\n", seq);


    }


}
