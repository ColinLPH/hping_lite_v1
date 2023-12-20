#ifndef HPING_LITE_V1_OPTIONS_H
#define HPING_LITE_V1_OPTIONS_H

#include <sys/types.h>

struct hping_options
{
    int argc;
    int reps;               //number of threads to create to send packet; default 1
    int frequency;          //how many times the packet is sent; default 1
    int type;
    int flags;          //which protocol is used as template; no default; required
    in_port_t dest_port;    //port of host to send to; required
    char *dest_ip;          //host to send to; required
    char *spoof_ip;         //icmp smurf atk
    char *msg;
    char **argv;
};

#endif //HPING_LITE_V1_OPTIONS_H
