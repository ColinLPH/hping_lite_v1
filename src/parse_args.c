//
// Created by cendor on 23/04/24.
//

#include "parse_args.h"

int parse_args(const int argc, char *argv[], struct options *opts)
{
    int c;
    optind = 1;
    while((c = getopt(argc, argv, ":d:i:c:s:p:a:M:2fFSRPAUh")) != 1)
    {
        switch(c)
        {
            case 'h':
            {
                print_help();
                return 1;
            }
            case 'd':
            {
                opts->dst_addr = strdup(optarg);
                break;
            }
            case 'i':
            {
                opts->interval = strtol(optarg, NULL, 10);
                if(errno == EINVAL || errno == ERANGE)
                {
                    printf("interval not valid\n");
                    return -1;
                }
                break;
            }
            case 'f':
            {
                //set interval to 0.1s or 100us
                opts->interval = FASTINTER;
                break;
            }
            case '2':
            {
                //set to udp mode
                opts->mode = UDPMODE;
                break;
            }
            case 'a':
            {
                //fake address
                opts->fake_addr = strdup(optarg);
                break;
            }
            case 's':
            {
                //set source port
                opts->src_port = parse_in_port_t(optarg);
                if(opts->src_port == 0)
                {
                    return -1;
                }
                break;
            }
            case 'p':
            {
                //set dest port
                opts->dst_port = parse_in_port_t(optarg);
                if(opts->dst_port == 0)
                {
                    return -1;
                }
                break;
            }
            case 'c':
            {
                //set count
                opts->count = strtol(optarg, NULL, 10);
                if(errno == EINVAL || errno == ERANGE)
                {
                    printf("count not valid\n");
                    return -1;
                }
                break;
            }
            case 'M':
            {
                //set TCP seq num, default 0
                opts->tcp_seq_num = strtol(optarg, NULL, 10);
                if(errno == EINVAL || errno == ERANGE)
                {
                    printf("seq_num not valid\n");
                    return -1;
                }
                break;

            }
            case 'F':
            {
                //set TCP FIN flag
                opts->tcp_fin = 1;
                break;
            }
            case 'S':
            {
                //set TCP SYN flag
                opts->tcp_syn = 1;
                break;
            }
            case 'R':
            {
                //set TCP RST flag
                opts->tcp_rst = 1;
                break;
            }
            case 'P':
            {
                //set TCP PUSH flag
                opts->tcp_psh = 1;
                break;
            }
            case 'A':
            {
                //set TCP ACK flag
                opts->tcp_ack = 1;
                break;
            }
            case 'U':
            {
                //set TCP URG flag
                opts->tcp_urg = 1;
                break;
            }
            case':':
            {
                printf("Option '%c' requires an argument\n", optopt);
                break;
            }
            case'?':
            {
                printf("Unknown option: %c\n", optopt);
                break;
            }
            default:
            {
                break;
            }
        }
    }
    return 1;
}

void print_help(void)
{
    char msg[500] = "Flags:\n";
    strcat(msg, "-i set interval (seconds), default 1s\n-f send as fast as possible\n");
    strcat(msg, "-2 udp mode, default tcp mode\n-a attach fake IP address\n");
    strcat(msg, "-s set source port\n-p set destination port\n");
    strcat(msg, "-M set the TCP sequence number, default is 0\n-c number of packets to send\n");
    strcat(msg, "-S set the SYN flag\n -R set the RST flag\n");
    strcat(msg, "-P set the PUSH flag\n-A set the ACK flag\n");
    strcat(msg, "-U set the URG flag\n-F set the FIN flag\n");

    printf("%s\n", msg);
}

in_port_t parse_in_port_t(const char *arg)
{
    char *endptr;
    uintmax_t parsed_val;

    parsed_val = strtoumax(arg, &endptr, 10);
    if(errno != 0)
    {
        printf("error parsing\n");
        return 0;
    }
    if(*endptr != '\0')
    {
        printf("invalid characters in port\n");
        return 0;
    }
    if(parsed_val > UINT16_MAX)
    {
        printf("port value outside of 16 bit range\n");
        return 0;
    }
    return parsed_val;
}
