//
// Created by cendor on 23/04/24.
//

#include "parse_args.h"

#include <string.h>


int parse_args(int argc, char *argv[])
{
    int c;
    optind = 1;
    while((c = getopt(argc, argv, ":i:c:s:p:a:M:2frFSRPAUh")) != 1)
    {
        switch(c)
        {
            case 'h':
            {
                print_help();
                break;
            }
            case 'i':
            {
                interval = atoi(optarg);
                if(interval == 0)
                {
                    printf("interval not valid\n");
                    return -1;
                }
                break;
            }
            case 'f':
            {
                //set interval to 0.1s or 100us
                interval = FASTINTER;
                break;
            }
            case '2':
            {
                //set to udp mode
                mode = UDPMODE;
            }
            case 'a':
            {
                //fake address
            }
            case 'r':
            {
                //generate random source address
            }
            case 's':
            {
                //set source port
            }
            case 'p':
            {
                //set dest port
            }
            case 'c':
            {
                //set count
                count = atoi(optarg);
                if(count == 0)
                {
                    printf("count not valid\n");
                    return -1;
                }
                break;
            }
            case 'M':
            {
                //set TCP seq num

            }
            case 'F':
            {
                //set TCP FIN flag
                tcp_fin = 1;
            }
            case 'S':
            {
                //set TCP SYN flag
                tcp_syn = 1;
            }
            case 'R':
            {
                //set TCP RST flag
                tcp_rst = 1;
            }
            case 'P':
            {
                //set TCP PUSH flag
                tcp_psh = 1;
            }
            case 'A':
            {
                //set TCP ACK flag
                tcp_ack = 1;
            }
            case 'U':
            {
                //set TCP URG flag
                tcp_urg = 1;
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
}
