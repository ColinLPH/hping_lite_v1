//
// Created by cendor on 29/04/24.
//

#ifndef CREATE_PACKET_H
#define CREATE_PACKET_H

#include <stdint.h>

#define PKT_LEN 512

uint16_t checksum(char *buf, int len);

#endif //CREATE_PACKET_H
