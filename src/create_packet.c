//
// Created by cendor on 29/04/24.
//

#include "create_packet.h"

uint16_t checksum(char *buf, int len)
{
    uint32_t sum = 0;

    // Sum all 16-bit words
    while (len > 1) {
        sum += *((uint16_t *)buf);
        buf += 2;
        len -= 2;
    }

    // If the length is odd, add the last byte
    if (len == 1) {
        sum += *((uint8_t *)buf);
    }

    // Fold 32-bit sum to 16 bits
    while (sum >> 16) {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }

    // Take the one's complement
    return ~sum;
}