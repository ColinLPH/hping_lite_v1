//
// Created by cendor on 30/04/24.
//

#ifndef OPTIONS_H
#define OPTIONS_H

#define TCPMODE 3
#define UDPMODE 2
#define DEFINTER 1000000 //default interval is 1 second btwn each packet
#define FASTINTER 100
#include <stddef.h>
#include <netinet/in.h>

struct options {
    int mode;
    in_port_t src_port;
    in_port_t dst_port;

    char *dst_addr;
    char *fake_addr;

    int count;
    int interval;

    //TCP options
    uint32_t tcp_seq_num;
    int tcp_syn;
    int tcp_fin;
    int tcp_rst;
    int tcp_psh;
    int tcp_ack;
    int tcp_urg;
};

void init_options(struct options *opts);
void clean_up_opts(struct options *opts);

#endif //OPTIONS_H
