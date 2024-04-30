//
// Created by cendor on 23/04/24.
//

#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H

#include <errno.h>
#include <getopt.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "options.h"

int parse_args(int argc, char *argv[], struct options *opts);
void print_help(void);
in_port_t parse_in_port_t(const char *arg);

/*
 * Default protocol is TCP,
 * by default hping3 will send tcp headers to target host's port 0 with a winsize of 64
 * without any tcp flag on.
 *
 * -h help
 * -i interval, wait x micro seconds between each packet, default is 1 second
 * --fast interval is 0.1 second
 * --faster interval is faster than 0.1 second
 * --flood -f send as fast as possible
 *
 * -2 udp, by default hping3 will send udp to target host's port 0.
 *
 * -a fake IP address
 * --rand-source random source address
 *
 * -s source port
 * -p dest port
 * -M Set the TCP sequence number.
 * -F set fin flag
 * -S set syn flag
 * -R set rst tcp flag
 * -P set push flag
 * -A --ack Set ACK tcp flag.
 * -U --urg Set URG tcp flag.
 *
 * -c --count count Stop after sending (and receiving) count response packets.
 * After last packet was send hping3 wait COUNTREACHED_TIMEOUT seconds target host replies.
 * You are able to tune COUNTREACHED_TIMEOUT editing hping3.h
 */

#endif //PARSE_ARGS_H
