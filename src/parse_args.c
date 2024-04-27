//
// Created by cendor on 23/04/24.
//

#include <getopt.h>
#include "globals.h"
#include "parse_args.h"

void parse_args(int argc, char *argv[])
{
    int c;
    optind = 1;
    while((c = getopt(argc, argv, ":h:i:f:0:1:2:a:r:s:p:c:M:L:b:F:S:R:P:A:U:")) != 1)
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
                set_interval(optarg);
                break;
            }
            case 'f':
            {

            }
        }
    }
}
