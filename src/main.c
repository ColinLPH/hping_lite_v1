
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <threads.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include "create_packet.h"
#include "options.h"
#include "parse_args.h"

void print_globals(struct options *opts);
int open_raw_sock(int mode);

int main (int argc, char *argv[])
{
    int sockfd;
    if(argc == 1)
    {
        printf("-h for help menu\n");
        return EXIT_SUCCESS;
    }
    errno = 0;
    struct options *opts = calloc(1, sizeof *opts);
    if(parse_args(argc, argv, opts) == -1) //parse, fill the options
    {
        clean_up_opts(opts);
        return EXIT_FAILURE;
    }
    print_globals(opts);

    //read the options, fill the packet
    char packet[PKT_LEN];
    if(opts->mode == UDPMODE)
    {
        struct udphdr *udp_header = (struct udphdr *) packet;
        udp_header->source = htons(opts->src_port);
        udp_header->dest = htons(opts->dst_port);
        udp_header->len = htons(sizeof(struct udphdr));
        udp_header->check = checksum(packet, sizeof(packet));
    }
    else
    {
        struct tcphdr *tcp_header = (struct tcphdr *) packet;
        tcp_header->source = htons(opts->src_port);
        tcp_header->dest = htons(opts->dst_port);
        tcp_header->seq = htonl(opts->tcp_seq_num);
        tcp_header->ack_seq = 0;
        tcp_header->doff = 5;
        tcp_header->fin = opts->tcp_fin;
        tcp_header->syn = opts->tcp_syn;
        tcp_header->rst = opts->tcp_rst;
        tcp_header->psh = opts->tcp_psh;
        tcp_header->ack = opts->tcp_ack;
        tcp_header->urg = opts->tcp_urg;
        tcp_header->window = htons(5840);
        tcp_header->urg_ptr = 0;
        tcp_header->check = checksum(packet, sizeof(packet));
    }

    //send the packet
    sockfd = open_raw_sock(opts->mode);
    if(sockfd == -1)
    {
        printf("socket failed\n");
        clean_up_opts(opts);
        return EXIT_FAILURE;
    }

    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(opts->dst_port);
    dest_addr.sin_addr.s_addr = inet_addr(opts->dst_addr);

    //sendto(), check interval, count
    for(int i = 0; i < opts->count; ++i)
    {
        sendto(sockfd, packet, PKT_LEN, 0, (struct sockaddr *) &dest_addr, sizeof(dest_addr));
        if(opts->interval > 0)
        {
            sleep(opts->interval);
        }

    }

    clean_up_opts(opts);
    return EXIT_SUCCESS;

}

void init_options(struct options *opts)
{
    opts->mode = TCPMODE;
    opts->src_port = 0;
    opts->dst_port = 0;

    opts->dst_addr = NULL;
    opts->fake_addr = NULL;

    opts->count = 1;
    opts->interval = DEFINTER;

    //TCP options
    opts->tcp_seq_num = 0;
    opts->tcp_syn = 0;
    opts->tcp_fin = 0;
    opts->tcp_rst = 0;
    opts->tcp_psh = 0;
    opts->tcp_ack = 0;
    opts->tcp_urg = 0;
}

void clean_up_opts(struct options *opts)
{
    if(opts != NULL)
    {
        if(opts->dst_addr != NULL)
        {
            free(opts->dst_addr);
        }
        if(opts->fake_addr != NULL)
        {
            free(opts->fake_addr);
        }
        free(opts);
    }
}

void print_globals(struct options *opts)
{
    if(opts == NULL) return;
    printf("Globals:\n");
    printf("mode(TCP = 3, UDP = 2): %d\n", opts->mode);
    printf("dst_addr: %s\n", opts->dst_addr);
    printf("fake_addr: %s\n", opts->fake_addr);
    printf("src_port: %d\n", opts->src_port);
    printf("dst_port: %d\n", opts->dst_port);
    printf("count: %d\n", opts->count);
    printf("interval: %d\n", opts->interval);

    if(opts->mode == TCPMODE)
    {
        printf("-------TCP OPTIONS-------\n");
        printf("seq_num: %d\n", opts->tcp_seq_num);
        printf("flags S | F | R | P | A | U:\n %d | %d | %d | %d | %d | %d"
            , opts->tcp_syn, opts->tcp_fin, opts->tcp_rst, opts->tcp_psh, opts->tcp_ack, opts->tcp_urg);
    }

}

int open_raw_sock(int mode)
{
    int sock;
    if(mode == UDPMODE)
    {
        sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    }
    else
    {
        sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    }

    return sock;
}

