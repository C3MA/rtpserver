#ifndef RTPPARSER_H
#define RTPPARSER_H

#ifdef __cplusplus
extern "C" {
#endif
/***************** This library is NOOOOOT Thread safe *******************/

/**
 * @brief decode_packet
 * @param pPacket
 * @param packet_length
 * @param pOutputBuffer
 * @param width
 * @param height
 * @return ONE on Errors, zero on success
 */
int decode_packet(char* pPacket, int packet_length, char* pOutputBuffer, int width, int height);

#ifdef __cplusplus
}
#endif
#endif // RTPPARSER_H
