#include <stdlib.h>
#include "parse_args.h"

int main (int argc, char *argv[])
{
    if(parse_args(argc, argv) == -1)
    {
        return EXIT_FAILURE;
    }
    //parse, fill the options
    //read the options, fill the packet
    //send the packet
    //wait for all to be done, exit

    return EXIT_SUCCESS;

}
