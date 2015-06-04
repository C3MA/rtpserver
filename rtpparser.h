/* @file rtpparser.h
 * @brief Logic to decode one package
 * @author TObiMa
 * @author Ollo
 *
 * This modules has only logic to decode one RTP package.
 * Only uncompressed RGB values are supported.
 *
 * @defgroup RTPServer
 */

#ifndef RTPPARSER_H
#define RTPPARSER_H

#include <stdint.h>

/** @addtogroup RTPServer */
/*@{*/

#define RGB_SIZE    3   /**< We need three bytes, one for red, one for green and one for blue */

#ifdef __cplusplus
extern "C" {
#endif
/***************** This library is NOOOOOT Thread safe *******************/

/** @fn int decode_packet(uint8_t* pPacket, int packet_length, uint8_t* pOutputBuffer, int width, int height)
 * @brief decodes a RTP packet
 *
 * Decodes the received UDP package, containing the RTP content.
 * Only uncompressed RGB values without Alpha-channel are supported.
 *
 * The output buffer must have been allocated with the following size: RGB_SIZE times width times height.
 * @see RGB_SIZE
 *
 * @param[in] pPacket       The buffer with the content of the received UDP package
 * @param[in] packet_length Length of the received UDP package
 * @param[out] pOutputBuffer Buffer where the received image is stored (as RGB24 value
 * @param[in] width         width of the output buffer (pOutputBuffer)
 * @param[in] height        height of the output buffer (pOutputBuffer)
 * @return ONE on Errors, zero on success
 */
int decode_packet(uint8_t* pPacket, int packet_length, uint8_t* pOutputBuffer, int width, int height);

#ifdef __cplusplus
}
#endif

/*@}*/

#endif // RTPPARSER_H
