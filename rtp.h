#ifndef RTP_H
#define RTP_H

#include <stdint.h>


typedef struct {
    unsigned int version:2;  /* protocol version */
    unsigned int p:1;        /* padding flag */
    unsigned int x:1;        /* header extension flag */
    unsigned int cc:4;       /* CSRC count */
    unsigned int m:1;        /* marker bit */
    unsigned int pt:7;       /* payload type */
    uint16_t seq;             /* sequence number */
    uint32_t ts;              /* timestamp */
    uint32_t ssrc;            /* synchronization source */
    uint32_t csrc[1];         /* optional CSRC list */
} __attribute__ ((__packed__)) rtp_hdr_t;

#endif // RTP_H
