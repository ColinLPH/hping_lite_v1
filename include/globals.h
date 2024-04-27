//
// Created by Colin Lam on 2024-04-24.
//

#ifndef HPING_LITE_V1_GLOBALS_H
#define HPING_LITE_V1_GLOBALS_H
#include <stdint.h>
#include <stdio.h>

#define TCPMODE 3
#define UDPMODE 2
#define DEFINTER 1000000 //default interval is 1 second btwn each packet
#define FASTINTER 100

int mode = TCPMODE;
char *src_port = NULL;
char *dst_port = NULL;

char *src_addr = NULL;

int count = 1;
int interval = DEFINTER;


//TCP options
uint32_t tcp_seq_num = 0;
int tcp_syn = 0;
int tcp_fin = 0;
int tcp_rst = 0;
int tcp_psh = 0;
int tcp_ack = 0;
int tcp_urg = 0;



#endif //HPING_LITE_V1_GLOBALS_H
