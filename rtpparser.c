#include "rtpparser.h"

#include <stdio.h>
#include <stddef.h>
#include <arpa/inet.h>
#include <string.h>

#define MAXLINES    64

#define LINEHEADER_SIZE 6

typedef struct {
    uint16_t length;
    uint16_t linenumber; /**< Y */
    uint16_t offset; /**< X */
} LineHeaderInfo;


LineHeaderInfo mLines[MAXLINES];
int            mActualLineCnt=0;
uint32_t       mLastTimestamp=0;



int decode_packet(uint8_t* pPacket, int packet_length, uint8_t* pOutputBuffer, int width, int height)
{
    unsigned int r_version, r_p, r_x, r_cc, r_pt, r_seq;
    uint32_t r_ts;
    /* Tear apart the header in a byte- and bit field-order
    independent fashion. */
    r_version = (pPacket[0] >> 6) & 3;
    r_p = !!(pPacket[0] & 0x20);
    r_x = !!(pPacket[0] & 0x10);
    r_cc = pPacket[0] & 0xF;

    r_pt = pPacket[1] & 0x7F;
    r_seq = (pPacket[2] << 8) | (pPacket[3] & 0xFF);
    r_ts = ntohl(*((long *) (pPacket + 4)));

    if (r_ts < mLastTimestamp) {
        // ignore frames older than the last seen one
        return 1;
    }

    mLastTimestamp = r_ts;

    if (
           r_version == 2 && /* Version ID correct */
           r_pt >= 96 &&
           r_pt <= 128 &&
           /* Padding, if present, is plausible */
           (!r_p || (pPacket[packet_length - 1] < (packet_length - (12 + 4 * r_cc))))
           )
    {
       uint8_t* payload;
       int lex, paylen;

       /* Length of fixed header extension, if any */
       lex = r_x ? (ntohs(*((short *) (pPacket + 2 + 12 + 4 * r_cc))) + 1) * 4 : 0;
       payload = pPacket + (12 + 4 * r_cc) + lex; /* Start of payload */
       paylen = packet_length - ((12 + 4 * r_cc) + /* Length of payload */
       lex + (r_p ? pPacket[packet_length - 1] : 0));

       /* payload header rfc4175 */
       uint32_t seq =
               ((uint32_t) ntohs( (payload[0] << 8) | (payload[1] & 0xFF) ) << 16 |
               ((uint32_t) r_seq));

       printf("%u\n", seq);


       mActualLineCnt = 0;

       int offset;

       for( offset = 2; offset < paylen /* break when we found the end */; offset += LINEHEADER_SIZE)
       {
           mLines[mActualLineCnt].length = ((payload[offset] << 8) | (payload[offset+1] & 0xFF) );
           mLines[mActualLineCnt].linenumber = (((payload[offset+2] << 8) & 0xEF) | (payload[offset+3] & 0xFF) );
           mLines[mActualLineCnt].offset = (((payload[offset+4] << 8) & 0xEF) | (payload[offset+5] & 0xFF) );

           /* Check if there is an end */
           if (!(payload[offset+4] & 0x80))
           {
               break;
           }

           mActualLineCnt++;
       }

       /* Fill the output buffer line by line */
       offset += LINEHEADER_SIZE;
       int fbOffset;
       int lineCnt;
       int fbLen;
       for (lineCnt = 0; (lineCnt < mActualLineCnt) && (offset < paylen); lineCnt++)
       {
           if (mLines[lineCnt].linenumber > height) {
               offset += mLines[lineCnt].length;
               continue;
           }

           fbOffset = mLines[lineCnt].linenumber * width * 3 + 3 * mLines[lineCnt].offset;

           fbLen = mLines[lineCnt].length;

           if ( width * RGB_SIZE  < RGB_SIZE * mLines[lineCnt].offset + mLines[lineCnt].length) {
                fbLen = width * RGB_SIZE - RGB_SIZE * mLines[lineCnt].offset;
           }

           if ( width * height * RGB_SIZE < fbOffset + fbLen) {
               fbLen = width * height * RGB_SIZE - fbOffset;
           }

           if (fbLen < RGB_SIZE) {
               offset += mLines[lineCnt].length;
               continue;
           }

           memmove(pOutputBuffer + fbOffset, payload +offset, fbLen);
           offset += mLines[lineCnt].length;
       }

    }

    return 0;
}
